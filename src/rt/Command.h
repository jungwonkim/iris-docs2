#ifndef IRIS_SRC_RT_COMMAND_H
#define IRIS_SRC_RT_COMMAND_H

#include <iris/iris.h>

#define IRIS_CMD_NOP            0x1000
#define IRIS_CMD_INIT           0x1001
#define IRIS_CMD_KERNEL         0x1002
#define IRIS_CMD_MALLOC         0x1003
#define IRIS_CMD_H2D            0x1004
#define IRIS_CMD_D2H            0x1005

namespace iris {
namespace rt {

class Mem;
class Task;
class Platform;

class Command {
public:
  Command(Task* task, int type);
  ~Command();

  int type() const { return type_; }

  bool type_init() { return type_ == IRIS_CMD_INIT; }
  bool type_h2d() { return type_ == IRIS_CMD_H2D; }
  bool type_d2h() { return type_ == IRIS_CMD_D2H; }
  bool type_kernel() { return type_ == IRIS_CMD_KERNEL; }

  Mem* mem() { return mem_; }
  Task* task() { return task_; }

private:
  int type_;
  size_t size_;
  void* host_;
  int dim_;
  size_t off_[3];
  size_t gws_[3];
  size_t lws_[3];
  Mem* mem_;
  Task* task_;
  Platform* platform_;

public:
  static Command* Create(Task* task, int type);
  static Command* CreateInit(Task* task);
  static Command* CreateMalloc(Task* task, Mem* mem);
  static Command* CreateH2D(Task* task, Mem* mem, size_t off, size_t size, void* host);
  static Command* CreateD2H(Task* task, Mem* mem, size_t off, size_t size, void* host);
  static void Release(Command* cmd);
};

} /* namespace rt */
} /* namespace iris */

#endif /* IRIS_SRC_RT_COMMAND_H */

