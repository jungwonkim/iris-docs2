#include "QueueTask.h"
#include "Platform.h"
#include "Debug.h"

namespace iris {
namespace rt {

QueueTask::QueueTask(Platform* platform) {
  platform_ = platform;
  pthread_mutex_init(&mutex_, nullptr);
}

QueueTask::~QueueTask() {
  pthread_mutex_destroy(&mutex_);
}

bool QueueTask::Dequeue(Task** task) {
  pthread_mutex_lock(&mutex_);
  if (tasks_.empty()) {
    pthread_mutex_unlock(&mutex_);
    return false;
  }
  for (auto I = tasks_.begin(), E = tasks_.end(); I != E; ++I) {
    Task* t = *I;
    if (!t->Dispatchable()) continue;
    if (t->marker() && I != tasks_.begin()) continue;
    *task = t;
    //todo: debug this!
    tasks_.erase(I);
    pthread_mutex_unlock(&mutex_);
    return true;
  }
  pthread_mutex_unlock(&mutex_);
  return false;
}

bool QueueTask::Enqueue(Task* task) {
  pthread_mutex_lock(&mutex_);
  tasks_.push_back(task);
  pthread_mutex_unlock(&mutex_);
  return true;
}

size_t QueueTask::Size() {
  pthread_mutex_lock(&mutex_);
  size_t size = tasks_.size();
  pthread_mutex_unlock(&mutex_);
  return size;
}

bool QueueTask::Empty() {
  pthread_mutex_lock(&mutex_);
  bool empty = tasks_.empty();
  pthread_mutex_unlock(&mutex_);
  return empty;
}

} /* namespace rt */
} /* namespace iris */

