#include "Scheduler.h"
#include "Debug.h"
#include "Device.h"
#include "Platform.h"
#include "QueueTask.h"
#include "Task.h"
#include "Worker.h"

namespace iris {
namespace rt {

Scheduler::Scheduler(Platform* platform) {
  platform_ = platform;
  devs_ = platform_->devs();
  ndevs_ = platform_->ndevs();
  workers_ = platform_->workers();

  pthread_mutex_init(&mutex_, nullptr);
}

Scheduler::~Scheduler() {
  pthread_mutex_destroy(&mutex_);
}

void Scheduler::Enqueue(Task* task) {
  while (!queue_->Enqueue(task)) { }
  Invoke();
}

void Scheduler::Run() {
  while (true) {
    Sleep();
    if (!running_) break;
    Task* task = nullptr;
    while (queue_->Dequeue(&task)) Submit(task);
  }
}

void Scheduler::Submit(Task* task) {
  if (!ndevs_) {
    if (!task->marker()) _error("%s", "no device");
    task->Complete();
    return;
  }
  if (task->marker()) {
    std::vector<Task*>* subtasks = task->subtasks();
    for (auto I = subtasks->begin(), E = subtasks->end(); I != E; ++I) {
      Task* subtask = *I;
      int dev = subtask->devno();
      workers_[dev]->Enqueue(subtask);
    }
    return;
  }
  Dispatch(task);
}

void Scheduler::Dispatch(Task* task) {
}

} /* namespace rt */
} /* namespace iris */

