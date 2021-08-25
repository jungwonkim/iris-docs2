#include "iris_assert.h"
#include <iris/iris.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  IRIS_CALL(iris_init(&argc, &argv, 1));

  iris_task task0;
  IRIS_CALL(iris_task_create(&task0));
  IRIS_CALL(iris_task_submit(task0, iris_cpu, NULL, 0));

  iris_task task1;
  iris_task task1_dep[] = { task0 };
  IRIS_CALL(iris_task_create(&task1));
  IRIS_CALL(iris_task_depend(task1, 1, task1_dep));
  IRIS_CALL(iris_task_submit(task1, iris_cpu, NULL, 0));

  IRIS_CALL(iris_finalize());

  return 0;
}
