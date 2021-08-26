#ifndef IRIS_TESTS_00_COMMON_IRIS_TEST_H
#define IRIS_TESTS_00_COMMON_IRIS_TEST_H

#include <iris/iris.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define IRIS_CALL(call) do {                                          \
  int err = call;                                                     \
  if (err != IRIS_SUCCESS) {                                          \
    printf("[%s:%d] IRIS_ERR[%d]\n", __FILE__, __LINE__, err);        \
    exit(EXIT_FAILURE);                                               \
  }                                                                   \
} while (0)

#define IRIS_PRINT(fmt, ...) do {                                     \
  printf("[%s:%d] " fmt "\n", __FILE__, __LINE__, __VA_ARGS__);       \
  } while (0)

#define IRIS_EQUAL_INT32(e, i) do {                                   \
  if (e != i) {                                                       \
    printf("[%s:%d] exp[%d] in[%d]\n", __FILE__, __LINE__, exp, in);  \
    exit(EXIT_FAILURE);                                               \
  }                                                                   \
} while (0)

#define IRIS_EQUAL_INT64(e, i) do {                                   \
  if (e != i) {                                                       \
    printf("[%s:%d] exp[%ld] in[%ld]\n", __FILE__, __LINE__, e, i);   \
    exit(EXIT_FAILURE);                                               \
  }                                                                   \
} while (0)

#define IRIS_EQUAL_STR(e, i) do {                                     \
  if (strcmp(e, i) != 0) {                                            \
    printf("[%s:%d] exp[%s] in[%s]\n", __FILE__, __LINE__, e, i);     \
    exit(EXIT_FAILURE);                                               \
  }                                                                   \
} while (0)

#endif /* IRIS_TESTS_00_COMMON_IRIS_TEST_H */

