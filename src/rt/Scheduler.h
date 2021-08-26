#ifndef IRIS_SRC_RT_SCHEDULER_H
#define IRIS_SRC_RT_SCHEDULER_H

#include "Thread.h"
#include <pthread.h>

namespace iris {
namespace rt {

class Device;
class Task;
class Timer;
class Platform;
class Queue;
class Worker;

class Scheduler : public Thread {
public:
  Scheduler(Platform* platform);
  virtual ~Scheduler();

  void Enqueue(Task* task);

  Platform* platform() { return platform_; }
  Device** devices() { return devs_; }
  Worker** workers() { return workers_; }
  Worker* worker(int i) { return workers_[i]; }
  int ndevs() { return ndevs_; }
  int nworkers() { return ndevs_; }

private:
  void Submit(Task* task);
  void Dispatch(Task* task);
  virtual void Run();

private:
  Queue* queue_;
  Platform* platform_;

  Device** devs_;
  Worker** workers_;
  int ndevs_;
  pthread_mutex_t mutex_;
};

} /* namespace rt */
} /* namespace iris */

#endif /* IRIS_SRC_RT_SCHEDULER_H */

