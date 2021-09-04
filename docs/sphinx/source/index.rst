.. iris documentation master file, created by
   sphinx-quickstart on Wed Sep  1 15:23:33 2021.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

IRIS
================================

IRIS is a unified framework across multiple programming platforms. IRIS enables programmers to write portable programs across diverse heterogeneous architectures from edge to exascale. An IRIS application can exploit multiple programming platforms including CUDA, Hexagon, HIP, Level Zero, OpenCL, and OpenMP at the same time.


IRIS provides task-based programming and execution models. A task is portable across all the available programming platforms and can be run on any accelerator in the system.


.. figure:: _images/overview.png
   :width: 100%
   :align: center


.. toctree::
   :maxdepth: 2
   :caption: Contents:



Contents
==================

:ref:`Keyword Index <genindex>`

.. toctree::
   :maxdepth: 2
   :caption: Installation

   installation.rst

.. toctree::
   :maxdepth: 2
   :caption: Getting Started

   started.rst

.. toctree::
   :maxdepth: 2
   :caption: IRIS API Specification

   api.rst

.. toctree::
   :maxdepth: 2
   :caption: IRIS Architecture

   architecture.rst

.. toctree::
   :maxdepth: 2
   :caption: Miscellaneous

   misc.rst
