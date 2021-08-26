#include "Platform.h"
#include "Debug.h"
#include "Utils.h"
#include "Task.h"
#include "Timer.h"
#include <unistd.h>
#include <algorithm>

namespace iris {
namespace rt {

char iris_log_prefix_[256];

Platform::Platform() {
  init_ = false;
  finalize_ = false;
  nplatforms_ = 0;
  ndevs_ = 0;

  timer_ = nullptr;

  pthread_mutex_init(&mutex_, nullptr);
}

Platform::~Platform() {
  if (!init_) return;

  if (timer_) delete timer_;

  pthread_mutex_destroy(&mutex_);
}

int Platform::Init(int* argc, char*** argv, int sync) {
  pthread_mutex_lock(&mutex_);
  if (init_) {
    pthread_mutex_unlock(&mutex_);
    return IRIS_ERR;
  }
  Utils::Logo(true);

  gethostname(iris_log_prefix_, 256);

  timer_ = new Timer();
  timer_->Start(IRIS_TIMER_APP);

  timer_->Start(IRIS_TIMER_PLATFORM);

  EnvironmentInit();

  timer_->Stop(IRIS_TIMER_PLATFORM);

  init_ = true;

  pthread_mutex_unlock(&mutex_);

  return IRIS_SUCCESS;
}

int Platform::Synchronize() {
  return IRIS_SUCCESS;
}

int Platform::EnvironmentInit() {
  EnvironmentSet("ARCHS", "openmp:cuda:hip:levelzero:hexagon:opencl", false);

  EnvironmentSet("KERNEL_CUDA",     "kernel.ptx",         false);
  EnvironmentSet("KERNEL_HEXAGON",  "kernel.hexagon.so",  false);
  EnvironmentSet("KERNEL_HIP",      "kernel.hip",         false);
  EnvironmentSet("KERNEL_OPENMP",   "kernel.openmp.so",   false);
  EnvironmentSet("KERNEL_SPV",      "kernel.spv",         false);

  return IRIS_SUCCESS;
}

int Platform::EnvironmentSet(const char* key, const char* value, bool overwrite) {
  std::string keystr = std::string(key);
  std::string valstr = std::string(value);
  auto I = env_.find(keystr);
  if (I != env_.end()) {
    if (!overwrite) {
      _error("env key[%s] val[%s]", key, value);
      return IRIS_ERR;
    }
    env_.erase(I);
  }
  env_.insert(std::pair<std::string, std::string>(keystr, valstr));
  return IRIS_SUCCESS;
}

int Platform::EnvironmentGet(const char* key, char** value, size_t* vallen) {
  char env_key[128];
  sprintf(env_key, "IRIS_%s", key);
  const char* val = getenv(env_key);
  if (!val) {
    std::string keystr = std::string(key);
    auto I = env_.find(keystr);
    if (I == env_.end()) {
      if (vallen) *vallen = 0;
      return IRIS_ERR;
    }
    val = I->second.c_str();
  }

  if (*value == nullptr) *value = (char*) malloc(strlen(val) + 1);
  strcpy(*value, val);
  if (vallen) *vallen = strlen(val) + 1;
  return IRIS_SUCCESS;
}

int Platform::PlatformCount(int* nplatforms) {
  if (nplatforms) *nplatforms = nplatforms_;
  return IRIS_SUCCESS;
}

int Platform::PlatformInfo(int platform, int param, void* value, size_t* size) {
  if (platform >= nplatforms_) return IRIS_ERR;
  return IRIS_SUCCESS;
}

int Platform::PlatformBuildProgram(int model, char* path) {
  return IRIS_SUCCESS;
}

int Platform::DeviceCount(int* ndevs) {
  if (ndevs) *ndevs = ndevs_;
  return IRIS_SUCCESS;
}

int Platform::DeviceInfo(int device, int param, void* value, size_t* size) {
  if (device >= ndevs_) return IRIS_ERR;
  return IRIS_SUCCESS;
}

int Platform::DeviceSynchronize(int ndevs, int* devices) {
  return IRIS_SUCCESS;
}

int Platform::PolicyRegister(const char* lib, const char* name, void* params) {
  return IRIS_SUCCESS;
}

int Platform::MemCreate(size_t size, iris_mem* struct_mem) {
  return IRIS_SUCCESS;
}

int Platform::MemRelease(iris_mem struct_mem) {
  return IRIS_SUCCESS;
}

int Platform::TaskCreate(const char* name, bool perm, iris_task* struct_task) {
  Task* task = Task::Create(this);
  *struct_task = task->struct_obj();
  return IRIS_SUCCESS;
}

int Platform::TaskDepend(iris_task struct_task, int ntasks, iris_task* struct_tasks) {
  Task* task = struct_task->class_obj;
  for (int i = 0; i < ntasks; i++)
    task->AddDepend(struct_tasks[i]->class_obj);
  return IRIS_SUCCESS;
}

int Platform::TaskH2D(iris_task struct_task, iris_mem struct_mem, size_t off, size_t size, void* host) {
  return IRIS_SUCCESS;
}

int Platform::TaskD2H(iris_task struct_task, iris_mem struct_mem, size_t off, size_t size, void* host) {
  return IRIS_SUCCESS;
}

int Platform::TaskH2DFull(iris_task struct_task, iris_mem struct_mem, void* host) {
  return IRIS_SUCCESS;
}

int Platform::TaskD2HFull(iris_task struct_task, iris_mem struct_mem, void* host) {
  return IRIS_SUCCESS;
}

int Platform::TaskSubmit(iris_task struct_task, int policy, const char* opt, int sync) {
  return IRIS_SUCCESS;
}

int Platform::TaskWait(iris_task struct_task) {
  return IRIS_SUCCESS;
}

int Platform::TaskWaitAll(int ntasks, iris_task* struct_tasks) {
  return IRIS_SUCCESS;
}

int Platform::TaskRelease(iris_task struct_task) {
  Task* task = struct_task->class_obj;
  task->Release();
  return IRIS_SUCCESS;
}

int Platform::TimerNow(double* time) {
  *time = timer_->Now();
  return IRIS_SUCCESS;
}

Platform* Platform::singleton_ = nullptr;
std::once_flag Platform::flag_singleton_;
std::once_flag Platform::flag_finalize_;

Platform* Platform::GetPlatform() {
  std::call_once(flag_singleton_, []() { singleton_ = new Platform(); });
  return singleton_;
}

int Platform::Finalize() {
  pthread_mutex_lock(&mutex_);
  if (finalize_) {
    pthread_mutex_unlock(&mutex_);
    return IRIS_ERR;
  }
  int err = Synchronize();
  time_app_ = timer_->Stop(IRIS_TIMER_APP);
  time_init_ = timer_->Total(IRIS_TIMER_PLATFORM);
  _info("total execution time:[%lf] sec. initialize:[%lf] sec. t-i:[%lf] sec", time_app_, time_init_, time_app_ - time_init_);
  finalize_ = true;
  pthread_mutex_unlock(&mutex_);
  return err;
}

} /* namespace rt */
} /* namespace iris */

