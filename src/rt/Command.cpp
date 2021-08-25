#include "Command.h"
#include "Debug.h"
#include "Platform.h"
#include "Task.h"

namespace iris {
namespace rt {

Command::Command(Task* task, int type) {
  task_ = task;
  type_ = type;
  platform_ = task->platform();
}

Command::~Command() {
}

Command* Command::Create(Task* task, int type) {
  return new Command(task, type);
}

Command* Command::CreateInit(Task* task) {
  return Create(task, IRIS_CMD_INIT);
}

Command* Command::CreateMalloc(Task* task, Mem* mem) {
  Command* cmd = Create(task, IRIS_CMD_MALLOC);
  cmd->mem_ = mem;
  return cmd;
}

Command* Command::CreateH2D(Task* task, Mem* mem, size_t off, size_t size, void* host) {
  Command* cmd = Create(task, IRIS_CMD_H2D);
  cmd->mem_ = mem;
  cmd->off_[0] = off;
  cmd->size_ = size;
  cmd->host_ = host;
  return cmd;
}

Command* Command::CreateD2H(Task* task, Mem* mem, size_t off, size_t size, void* host) {
  Command* cmd = Create(task, IRIS_CMD_D2H);
  cmd->mem_ = mem;
  cmd->off_[0] = off;
  cmd->size_ = size;
  cmd->host_ = host;
  return cmd;
}

void Command::Release(Command* cmd) {
  delete cmd;
}

} /* namespace rt */
} /* namespace iris */

