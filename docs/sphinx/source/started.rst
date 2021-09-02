.. index:: ! architecture, ! platform model

Hello World
==================

Setting the following environment variables is highly recommended to make life easier.

.. code-block:: bash

  $ export IRIS=<install_path> # install_path would be $HOME/.local
  $ export CPATH=$CPATH:$IRIS/include
  $ export LIBRARY_PATH=$LIBRARY_PATH:$IRIS/lib:$IRIS/lib64
  $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IRIS/lib:$IRIS/lib64
 

The “Hello World” program is the first step towards learning IRIS. All one needs to do is display the message “Hello World” on the screen. 

.. code-block:: bash

  $ cd iris
  $ cd apps/helloworld
  $ make
  $ ./helloworld
  Hello World!
  $

