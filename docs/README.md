# Documentation for IRIS

This user guide is hosted in readthedocs: https://iris-programminig.readthedocs.io

## Installation

```bash
$ git clone https://github.com/ornl/iris.git
$ cd iris
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_INSTALL_PREFIX=<install_dir> -DUSE_PYTHON=ON -DUSE_FORTRAN=ON
$ make install
```
