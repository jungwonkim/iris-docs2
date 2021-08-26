#include "Worker.h"
#include "Debug.h"
#include "Device.h"
#include "Platform.h"
#include "QueueReady.h"
#include "Scheduler.h"
#include "Task.h"
#include "Timer.h"

namespace iris {
namespace rt {

Worker::Worker(Device* dev, Platform* platform) {
  dev_ = dev;
  platform_ = platform;
//  dev_->set_worker(this);
  scheduler_ = platform_->scheduler();
  queue_ = new QueueReady(128);
  busy_ = false;
}

Worker::~Worker() {
  delete queue_;
}

void Worker::TaskComplete(Task* task) {
  if (scheduler_) scheduler_->Invoke();
  Invoke();
}

void Worker::Enqueue(Task* task) {
  while (!queue_->Enqueue(task)) { }
  Invoke();
}

void Worker::Execute(Task* task) {
  if (task->marker()) {
    dev_->Synchronize(); //todo?
    task->Complete();
    return;
  }
  busy_ = true;
  dev_->Execute(task);
  busy_ = false;
}

void Worker::Run() {
  while (true) {
    Sleep();
    if (!running_) break;
    Task* task = nullptr;
    while (queue_->Dequeue(&task)) Execute(task);
  }
}

unsigned long Worker::ntasks() {
  return queue_->Size() + (busy_ ? 1 : 0);
}

} /* namespace rt */
} /* namespace iris */

