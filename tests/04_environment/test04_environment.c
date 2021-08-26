#include "iris_test.h"

int main(int argc, char** argv) {
  char* color = NULL;
  size_t size;
  IRIS_CALL(iris_env_set("COLOR", "RED"));
  IRIS_CALL(iris_init(&argc, &argv, 1));
  IRIS_CALL(iris_env_get("COLOR", &color, &size));
  IRIS_EQUAL_STR("RED", color);
  IRIS_EQUAL_INT64(4ULL, size);
  IRIS_CALL(iris_finalize());
  return 0;
}

