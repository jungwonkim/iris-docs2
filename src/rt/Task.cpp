#include "Task.h"
#include "Debug.h"
#include "Command.h"
#include "Device.h"

namespace iris {
namespace rt {

Task::Task(Platform* platform, int type) {
  platform_ = platform;
  type_ = type;
  ncmds_ = 0;
  dev_ = nullptr;
  depends_ = nullptr;
  depends_max_ = IRIS_MAX_NCMDS;
  ndepends_ = 0;
  status_ = IRIS_NONE;

  pthread_mutex_init(&mutex_complete_, nullptr);
  pthread_cond_init(&cond_complete_, nullptr);
}

Task::~Task() {
  for (int i = 0; i < ncmds_; i++) delete cmds_[i];
  for (int i = 0; i < ndepends_; i++) depends_[i]->Release();
  if (depends_) delete depends_;

  pthread_mutex_destroy(&mutex_complete_);
  pthread_cond_destroy(&cond_complete_);
}

bool Task::AddCommand(Command* cmd) {
  if (ncmds_ == IRIS_MAX_NCMDS - 1) {
    _error("ncmds[%d]", ncmds_);
    return false;
  }
  cmds_[ncmds_++] = cmd;
  return true;
}

bool Task::Dispatchable() {
  for (int i = 0; i < ndepends_; i++) {
    if (depends_[i]->status() != IRIS_COMPLETE) return false;
  }
  return true;
}

void Task::Complete() {
  pthread_mutex_lock(&mutex_complete_);
  status_ = IRIS_COMPLETE;
  pthread_cond_broadcast(&cond_complete_);
  pthread_mutex_unlock(&mutex_complete_);
}

void Task::Wait() {
  pthread_mutex_lock(&mutex_complete_);
  if (status_ != IRIS_COMPLETE)
    pthread_cond_wait(&cond_complete_, &mutex_complete_);
  pthread_mutex_unlock(&mutex_complete_);
}

void Task::AddDepend(Task* task) {
  if (depends_ == nullptr) depends_ = new Task*[depends_max_];
  for (int i = 0; i < ndepends_; i++) if (task == depends_[i]) return;
  if (ndepends_ == depends_max_ - 1) {
    Task** old = depends_;
    depends_max_ *= 2;
    depends_ = new Task*[depends_max_];
    memcpy(depends_, old, ndepends_ * sizeof(Task*));
    delete* old;
  } 
  depends_[ndepends_++] = task;
  task->Retain();
}

void Task::Submit(int brs_policy, const char* opt, int sync) {
  status_ = IRIS_SUBMITTED;
  Retain();
}

Task* Task::Create(Platform* platform) {
  return new Task(platform);
}

} /* namespace rt */
} /* namespace iris */

