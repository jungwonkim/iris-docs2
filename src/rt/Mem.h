#ifndef IRIS_SRC_RT_MEM_H
#define IRIS_SRC_RT_MEM_H

#include "Config.h"
#include "Releasable.h"
#include <pthread.h>
#include <set>

namespace iris {
namespace rt {

class Platform;
class Device;

class Mem: public Releasable<struct _iris_mem, Mem> {
public:
  Mem(size_t size, Platform* platform);
  virtual ~Mem();

  size_t size() { return size_; }

  void** archs() { return archs_; }
  void* arch(Device* dev);

private:
  size_t size_;
  Platform* platform_;
  int ndevs_;
  void* archs_[IRIS_MAX_NDEVS];
  Device* archs_dev_[IRIS_MAX_NDEVS];

  pthread_mutex_t mutex_;
};

} /* namespace rt */
} /* namespace iris */

#endif /* IRIS_SRC_RT_MEM_H */

