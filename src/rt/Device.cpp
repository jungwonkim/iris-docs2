#include "Device.h"
#include "Debug.h"
#include "Platform.h"
#include "Utils.h"

namespace iris {
namespace rt {

Device::Device(int devno, int platform) {
  devno_ = devno;
  platform_ = platform;
  busy_ = false;
  enable_ = false;
  memset(vendor_, 0, sizeof(vendor_));
  memset(name_, 0, sizeof(name_));
  memset(version_, 0, sizeof(version_));
}

Device::~Device() {
}

int Device::Execute(Task* task) {
  return IRIS_SUCCESS;
}

int Device::ExecuteInit(Command* cmd) {
  return IRIS_SUCCESS;
}

int Device::ExecuteKernel(Command* cmd) {
  return IRIS_SUCCESS;
}

int Device::ExecuteMalloc(Command* cmd) {
  return IRIS_SUCCESS;
}

int Device::ExecuteH2D(Command* cmd) {
  return IRIS_SUCCESS;
}

int Device::ExecuteD2H(Command* cmd) {
  return IRIS_SUCCESS;
}

int Device::ExecuteReleaseMem(Command* cmd) {
  return IRIS_SUCCESS;
}

} /* namespace rt */
} /* namespace iris */

