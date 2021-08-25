#ifndef IRIS_SRC_RT_PLATFORM_H
#define IRIS_SRC_RT_PLATFORM_H

#include <iris/iris.h>
#include <pthread.h>
#include <stddef.h>
#include <set>
#include <map>
#include <mutex>
#include <string>
#include "Config.h"
#include "Structs.h"

namespace iris {
namespace rt {

class Device;
class Timer;

class Platform {
private:
  Platform();
  ~Platform();

public:
  int Init(int* argc, char*** argv, int sync);
  int Finalize();
  int Synchronize();

  int EnvironmentInit();
  int EnvironmentSet(const char* key, const char* value, bool overwrite);
  int EnvironmentGet(const char* key, char** value, size_t* vallen);

  int PlatformCount(int* nplatforms);
  int PlatformInfo(int platform, int param, void* value, size_t* size);
  int PlatformBuildProgram(int model, char* path);

  int DeviceCount(int* ndevs);
  int DeviceInfo(int device, int param, void* value, size_t* size);
  int DeviceSynchronize(int ndevs, int* devices);

  int PolicyRegister(const char* lib, const char* name, void* params);

  int MemCreate(size_t size, iris_mem* brs_mem);
  int MemRelease(iris_mem brs_mem);

  int TaskCreate(const char* name, bool perm, iris_task* brs_task);
  int TaskDepend(iris_task brs_task, int ntasks, iris_task* brs_tasks);
  int TaskH2D(iris_task brs_task, iris_mem brs_mem, size_t off, size_t size, void* host);
  int TaskD2H(iris_task brs_task, iris_mem brs_mem, size_t off, size_t size, void* host);
  int TaskH2DFull(iris_task brs_task, iris_mem brs_mem, void* host);
  int TaskD2HFull(iris_task brs_task, iris_mem brs_mem, void* host);
  int TaskSubmit(iris_task brs_task, int brs_policy, const char* opt, int wait);
  int TaskWait(iris_task brs_task);
  int TaskWaitAll(int ntasks, iris_task* brs_tasks);
  int TaskRelease(iris_task brs_task);

  int TimerNow(double* time);

  int ndevs() { return ndevs_; }
  Device** devs() { return devs_; }
  Device* dev(int devno) { return devs_[devno]; }

private:

public:
  static Platform* GetPlatform();

private:
  bool init_;
  bool finalize_;

  char platforms_[IRIS_MAX_NPLATFORMS][64];
  int nplatforms_;
  Device* devs_[IRIS_MAX_NDEVS];
  int ndevs_;

  pthread_mutex_t mutex_;

  Timer* timer_;

  double time_app_;
  double time_init_;

private:
  static Platform* singleton_;
  static std::once_flag flag_singleton_;
  static std::once_flag flag_finalize_;
};

} /* namespace rt */
} /* namespace iris */

#endif /* IRIS_SRC_RT_PLATFORM_H */

