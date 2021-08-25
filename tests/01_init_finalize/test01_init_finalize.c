#include "iris_test.h"
#include <iris/iris.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  IRIS_CALL(iris_init(&argc, &argv, 1));
  IRIS_CALL(iris_finalize());
  return 0;
}

