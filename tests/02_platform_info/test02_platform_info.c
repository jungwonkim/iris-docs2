#include "iris_test.h"
#include <iris/iris.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  int i, nplatforms;
  char name[256];

  IRIS_CALL(iris_init(&argc, &argv, 1));

  IRIS_CALL(iris_platform_count(&nplatforms));

  printf("[%s:%d] nplatforms[%d]\n", __FILE__, __LINE__, nplatforms);

  for (i = 0; i < nplatforms; i++) {
    IRIS_CALL(iris_platform_info(i, iris_info_name, name, NULL));
    printf("[%s:%d] platform[%d] name[%s]\n", __FILE__, __LINE__, i, name);
  }

  IRIS_CALL(iris_finalize());
  return 0;
}

