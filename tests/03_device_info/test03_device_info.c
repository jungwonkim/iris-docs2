#include "iris_test.h"

int main(int argc, char** argv) {
  int i, ndevs;
  char name[256];

  IRIS_CALL(iris_init(&argc, &argv, 1));

  IRIS_CALL(iris_device_count(&ndevs));

  printf("[%s:%d] ndevs[%d]\n", __FILE__, __LINE__, ndevs);

  for (i = 0; i < ndevs; i++) {
    IRIS_CALL(iris_device_info(i, iris_info_name, name, NULL));
    printf("[%s:%d] device[%d] name[%s]\n", __FILE__, __LINE__, i, name);
  }

  IRIS_CALL(iris_finalize());
  return 0;
}

