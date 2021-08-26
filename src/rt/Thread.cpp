#include "Thread.h"
#include "Debug.h"

namespace iris {
namespace rt {

Thread::Thread() {
  thread_ = (pthread_t) nullptr;
  running_ = false;
  sem_init(&sem_, 0, 0);
}

Thread::~Thread() {
  Stop();
  sem_destroy(&sem_);
}

void Thread::Start() {
  if (thread_) return;
  running_ = true;
  pthread_create(&thread_, nullptr, &Thread::ThreadFunc, this);
}

void Thread::Stop() {
  if (!thread_) return;
  running_ = false;
  Invoke();
  pthread_join(thread_, nullptr);
  thread_ = (pthread_t) nullptr;
}

void Thread::Sleep() {
  sem_wait(&sem_);
}

void Thread::Invoke() {
  sem_post(&sem_);
}

void* Thread::ThreadFunc(void* argp) {
  ((Thread*) argp)->Run();
  return nullptr;
}

} /* namespace rt */
} /* namespace iris */

