#include "Mem.h"
#include "Debug.h"
#include "Platform.h"
#include "Device.h"
#include <stdlib.h>

namespace iris {
namespace rt {

Mem::Mem(size_t size, Platform* platform) {
  size_ = size;
  platform_ = platform;
  ndevs_ = platform->ndevs();
  for (int i = 0; i < ndevs_; i++) {
    archs_[i] = nullptr;
    archs_dev_[i] = platform->device(i);
  }
  pthread_mutex_init(&mutex_, nullptr);
}

Mem::~Mem() {
  for (int i = 0; i < ndevs_; i++) {
    if (archs_[i]) archs_dev_[i]->MemFree(archs_[i]);
  }
  pthread_mutex_destroy(&mutex_);
}

void* Mem::arch(Device* dev) {
  int devno = dev->devno();
  if (archs_[devno] == nullptr) dev->MemAlloc(archs_ + devno, size_);
  return archs_[devno];
}

} /* namespace rt */
} /* namespace iris */

