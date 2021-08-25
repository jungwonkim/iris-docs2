#ifndef IRIS_INCLUDE_IRIS_IRIS_RUNTIME_H
#define IRIS_INCLUDE_IRIS_IRIS_RUNTIME_H

#include <iris/iris_errno.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define IRIS_MAX_NPLATFORMS     32
#define IRIS_MAX_NDEVS          (1 << 5) - 1

#define iris_default            (1 << 5)

#define iris_cpu                (1 << 6)
#define iris_gpu                (1 << 7)
#define iris_fpga               (1 << 8)
#define iris_dsp                (1 << 9)

#define iris_cuda               (1 << 10)
#define iris_hexagon            (1 << 11)
#define iris_hip                (1 << 12)
#define iris_levelzero          (1 << 13)
#define iris_opencl             (1 << 14)
#define iris_openmp             (1 << 15)

#define iris_roundrobin         (1 << 16)
#define iris_locality           (1 << 17)
#define iris_random             (1 << 18)
#define iris_custom             (1 << 25)

#define iris_r                  (1 << 0)
#define iris_w                  (1 << 1)
#define iris_rw                 (iris_r | iris_w)

#define iris_int8               (1 << 0)
#define iris_int16              (1 << 1)
#define iris_int32              (1 << 2)
#define iris_int64              (1 << 3)
#define iris_float              (1 << 4)
#define iris_double             (1 << 5)

#define iris_platform           0x1001
#define iris_vendor             0x1002
#define iris_name               0x1003
#define iris_type               0x1004

typedef struct _iris_task*      iris_task;
typedef struct _iris_mem*       iris_mem;

extern int iris_init(int* argc, char*** argv, int sync);
extern int iris_finalize();
extern int iris_synchronize();

extern int iris_env_set(const char* key, const char* value);
extern int iris_env_get(const char* key, char** value, size_t* vallen);

extern int iris_platform_count(int* nplatforms);
extern int iris_platform_info(int platform, int param, void* value, size_t* size);
extern int iris_platform_build_program(int model, char* path);

extern int iris_device_count(int* ndevs);
extern int iris_device_info(int device, int param, void* value, size_t* size);
extern int iris_device_synchronize(int ndevs, int* devices);

extern int iris_register_policy(const char* lib, const char* name, void* params);

extern int iris_mem_create(size_t size, iris_mem* mem);
extern int iris_mem_release(iris_mem mem);

extern int iris_task_create(iris_task* task);
extern int iris_task_depend(iris_task task, int ntasks, iris_task* tasks);
extern int iris_task_h2d(iris_task task, iris_mem mem, size_t off, size_t size, void* host);
extern int iris_task_d2h(iris_task task, iris_mem mem, size_t off, size_t size, void* host);
extern int iris_task_h2d_full(iris_task task, iris_mem mem, void* host);
extern int iris_task_d2h_full(iris_task task, iris_mem mem, void* host);
extern int iris_task_submit(iris_task task, int device, const char* opt, int sync);
extern int iris_task_wait(iris_task task);
extern int iris_task_wait_all(int ntasks, iris_task* tasks);
extern int iris_task_release(iris_task task);

extern int iris_timer_now(double* time);

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* IRIS_INCLUDE_IRIS_IRIS_RUNTIME_H */

