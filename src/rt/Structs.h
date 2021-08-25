#ifndef IRIS_SRC_RT_STRUCTS_H
#define IRIS_SRC_RT_STRUCTS_H

namespace iris {
namespace rt {
class Kernel;
class Mem;
class Task;
} /* namespace rt */
} /* namespace iris */

struct _iris_kernel {
  iris::rt::Kernel* class_obj;
};

struct _iris_mem {
  iris::rt::Mem* class_obj;
};

struct _iris_task {
  iris::rt::Task* class_obj;
};

#endif /* IRIS_SRC_RT_STRUCTS_H */

