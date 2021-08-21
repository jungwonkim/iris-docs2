.. IRIS documentation master file, created by
   sphinx-quickstart on Mon Aug 16 11:06:12 2021.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

IRIS
================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:

*****************************************
Building and Installing IRIS
*****************************************

.. code-block:: bash

		$ git clone https://github.com/jungwonkim/iris.git
		$ cd iris
		$ mkdir build
		$ cd build
		$ cmake .. -DCMAKE_INSTALL_PREFIX=<install_dir> -DUSE_PYTHON=ON -DUSE_FORTRAN=ON
		$ make install

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
