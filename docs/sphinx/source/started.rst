.. index:: ! architecture, ! platform model

Hello World
==================

Setting the following environment variables is highly recommended to make life easier.

.. code-block:: bash

  $ export IRIS=<install_path> # install_path would be $HOME/.local
  $ export CPATH=$CPATH:$IRIS/include
  $ export LIBRARY_PATH=$LIBRARY_PATH:$IRIS/lib:$IRIS/lib64
  $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IRIS/lib:$IRIS/lib64
 

The “Hello World” program is the first step towards learning IRIS. This program displays the message “Hello World” on the screen.

.. code-block:: bash

  $ cd iris/apps/helloworld
  $ make
  $ ./helloworld
  Hello World
  $

Host Code
---------

.. content-tabs::

    .. tab-container:: tab1
        :title: C

        .. literalinclude:: _code/helloworld.c
          :language: c

Kernels
-------

.. content-tabs::

    .. tab-container:: tab1
        :title: CUDA

        .. literalinclude:: _code/kernel.cu
          :language: c

    .. tab-container:: tab2
        :title: HIP

        .. literalinclude:: _code/kernel.hip.cpp
          :language: c

    .. tab-container:: tab3
        :title: OpenMP

        .. literalinclude:: _code/kernel.omp.h
          :language: c

    .. tab-container:: tab4
        :title: Hexagon

        .. literalinclude:: _code/kernel.hexagon.c
          :language: c
