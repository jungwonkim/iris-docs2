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

#define iris_info_platform      0x1001
#define iris_info_vendor        0x1002
#define iris_info_name          0x1003
#define iris_info_type          0x1004

typedef struct _iris_mem*       iris_mem;
typedef struct _iris_task*      iris_task;

/**
 * Initializes the IRIS execution environment.
 * @param argc pointer to the number of arguments
 * @param argv argument array
 * @param sync 0: non-blocking, 1: blocking
 * @return All IRIS functions return an error value. IRIS_SUCCESS, IRIS_ERR
 */
extern int iris_init(int* argc, char*** argv, int sync);

/**
 * Terminates the IRIS execution environment.
 */
extern int iris_finalize();

/**
 * Waits for all the submitted tasks to complete.
 */
extern int iris_synchronize();

/**
 * Sets an IRIS environment variable.
 * @param key key string
 * @param value value to be stored into key
 */
extern int iris_env_set(const char* key, const char* value);

/**
 * Gets an IRIS environment variable.
 * @param key key string
 * @param value pointer to the value to be retrieved
 * @param vallen size in bytes of value
 */
extern int iris_env_get(const char* key, char** value, size_t* vallen);

/**
 * Returns the number of platforms.
 * @param nplatforms pointer to the number of platform
 */
extern int iris_platform_count(int* nplatforms);

/**
 * Returns the platform information.
 * @param platform platform number
 * @param param information type
 * @param value information value
 * @param size size in bytes of value
 */
extern int iris_platform_info(int platform, int param, void* value, size_t* size);

/**
 * Builds a probram containing kernels
 * @param model target model
 * @param path file path
 */
extern int iris_platform_build_program(int model, char* path);

/**
 * Returns the number of devices.
 * @param ndevs pointer to the number of devices
 */
extern int iris_device_count(int* ndevs);

/**
 * Returns the device information.
 * @param device device number
 * @param param information type
 * @param value information value
 * @param size size in bytes of value
 */
extern int iris_device_info(int device, int param, void* value, size_t* size);

/**
 * Waits for all the submitted tasks in a device to complete.
 * @param ndevs number of devices
 * @param devices device array
 */
extern int iris_device_synchronize(int ndevs, int* devices);

/**
 * Registers a new device selector
 * @param lib shared library path
 * @param name selector name
 * @param params parameter to the selector init function
 */
extern int iris_register_policy(const char* lib, const char* name, void* params);

/**
 * Creates a new memory object
 * @param size size in bytes
 * @param mem pointer of the new memory object
 */
extern int iris_mem_create(size_t size, iris_mem* mem);

/**
 * Releases a memory object.
 * @param mem memory object
 */
extern int iris_mem_release(iris_mem mem);

/**
 * Creates a new task.
 * @param task pointer of the new task
 */
extern int iris_task_create(iris_task* task);

/**
 * Adds a dependency to a task.
 * @param task source task
 * @param ntasks number of tasks
 * @param tasks target tasks array
 */
extern int iris_task_depend(iris_task task, int ntasks, iris_task* tasks);

/**
 * Adds a H2D command to the target task.
 * @param task target task
 * @param mem target memory object
 * @param off offset in bytes
 * @param size size in bytes
 * @param host source host address
 */
extern int iris_task_h2d(iris_task task, iris_mem mem, size_t off, size_t size, void* host);

/**
 * Adds a D2H command to the target task.
 * @param task target task
 * @param mem source memory object
 * @param off offset in bytes
 * @param size size in bytes
 * @param host target host address
 */
extern int iris_task_d2h(iris_task task, iris_mem mem, size_t off, size_t size, void* host);

/**
 * Adds a H2D command with the size of the target memory to the target task.
 * @param task target task
 * @param mem target memory object
 * @param host source host address
 */
extern int iris_task_h2d_full(iris_task task, iris_mem mem, void* host);

/**
 * Adds a D2H command with the size of the source memory to the target task.
 * @param task target task
 * @param mem source memory object
 * @param host target host address
 */
extern int iris_task_d2h_full(iris_task task, iris_mem mem, void* host);

/**
 * Launch a kernel
 * @param task target task
 * @param kernel kernel name
 * @param dim dimension
 * @param off global workitem space offsets
 * @param gws global workitem space
 * @param lws local workitem space
 * @param nparams number of kernel parameters
 * @param params kernel parameters
 * @param params_info kernel parameters information
 */
extern int iris_task_kernel(iris_task task, const char* kernel, int dim, size_t* off, size_t* gws, size_t* lws, int nparams, void** params, int* params_info);

/**
 * Submits a task.
 * @param task target task
 * @param device device_selector
 * @param opt option string
 * @param sync 0: non-blocking, 1: blocking
 */
extern int iris_task_submit(iris_task task, int device, const char* opt, int sync);

/**
 * Waits for the task to complete.
 * @param task target task
 */
extern int iris_task_wait(iris_task task);

/**
 * Waits for all the tasks to complete.
 * @param ntasks number of tasks
 * @param tasks target tasks array
 */
extern int iris_task_wait_all(int ntasks, iris_task* tasks);

/**
 * Releases a target.
 * @param task target task
 */
extern int iris_task_release(iris_task task);

/**
 * Returns current time in seconds.
 * @param time pointer of time
 */
extern int iris_timer_now(double* time);

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* IRIS_INCLUDE_IRIS_IRIS_RUNTIME_H */

