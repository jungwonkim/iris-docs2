#ifndef IRIS_SRC_RT_TASK_H
#define IRIS_SRC_RT_TASK_H

#include "Releasable.h"
#include "Platform.h"
#include <pthread.h>
#include <vector>

#define IRIS_COMPLETE       0x0
#define IRIS_RUNNING        0x1
#define IRIS_SUBMITTED      0x2
#define IRIS_QUEUED         0x3
#define IRIS_NONE           0x4

#define IRIS_MAX_NCMDS      64
#define IRIS_MAX_NDEPENDS   64

namespace iris {
namespace rt {

class Command;
class Device;

class Task: public Releasable<struct _iris_task, Task> {
public:
  Task(Platform* platform);
  virtual ~Task();

  bool AddCommand(Command* cmd);

  void AddDepend(Task* task);

  void Submit(int brs_policy, const char* opt, int sync);

  bool Dispatchable();
  void Complete();
  void Wait();

  Platform* platform() { return platform_; }
  int status() const { return status_; }

private:
  Platform* platform_;

  int ncmds_;
  Command* cmds_[64];
  Device* dev_;

  Task** depends_;
  int depends_max_;
  int ndepends_;

  int status_;

  pthread_mutex_t mutex_complete_;
  pthread_cond_t cond_complete_;

public:
  static Task* Create(Platform* platform);
};

} /* namespace rt */
} /* namespace iris */

#endif /* IRIS_SRC_RT_TASK_H */

