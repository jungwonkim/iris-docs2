.. index:: ! architecture, ! platform model

Hello World
==================

Setting the following environment variables is highly recommended to make life easier.

.. code-block:: bash

  $ export IRIS=<install_path> # install_path would be $HOME/.local
  $ export CPATH=$CPATH:$IRIS/include
  $ export LIBRARY_PATH=$LIBRARY_PATH:$IRIS/lib:$IRIS/lib64
  $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IRIS/lib:$IRIS/lib64
 

The “Hello World” program is the first step towards learning IRIS. This program displays the message “Hello, World!” on the screen.

.. code-block:: bash

  $ cd iris/apps/helloworld
  $ make
  $ ./helloworld
  Hello, World!
  $

helloworld.c: host code written in the :ref:`IRIS C API<c-api>`.

.. code-block:: c

  #include <iris/iris.h>
  #include <stdio.h>

  char* a = "hell";
  char* b = "o, w";
  char* c = "orld";

  char value = '!';
  int  pos   = 12;

  size_t gws = 16;

  char msg[16];

  int main(int argc, char** argv) {
    iris_mem mem;
    iris_task task;
 
    iris_init(&argc, &argv, 1);

    iris_mem_create(gws * sizeof(char), &mem);
    iris_task_create(&task);
    iris_task_h2d(task, mem, 0, 4, a);
    iris_task_h2d(task, mem, 4, 4, b);
    iris_task_h2d(task, mem, 8, 4, c);
    void* params[3] = { mem, &value, &pos };
    int params_info[3] = { iris_w, sizeof(value), sizeof(pos) };
    iris_task_kernel(task, "mykernel", 1, NULL, &gws, NULL, 3, params, params_info);
    iris_task_d2h(task, mem, 0, 16, msg);
    iris_task_submit(task, iris_roundrobin, NULL, 1);

    printf("%s\n", msg);

    iris_task_release(task);
    iris_mem_release(mem);

    iris_finalize();
    return 0;
  }


kernel.cu: CUDA kernel.

.. code-block:: c

  extern "C" __global__ void mykernel(char* mem, char value, int pos) {
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    if (id == pos) mem[id] = value;
    else if (id > pos) mem[id] = 0;
    else if (mem[id] == 'h' || mem[id] == 'w') mem[id] += 'A' - 'a';
  }


