cmake_minimum_required(VERSION 2.8)

project(IRIS)
include(GNUInstallDirs)

set(IRIS_VERSION_MAJOR 1)
set(IRIS_VERSION_MINOR 0)
set(IRIS_VERSION_PATCH 0)

set(IRIS_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(IRIS_INC_DIR ${PROJECT_SOURCE_DIR}/include)
set(IRIS_BIN_DIR ${PROJECT_BINARY_DIR}/src)

option(USE_PYTHON       "Enable support for Python"     OFF)
option(USE_FORTRAN      "Enable support for Fortran 90" OFF)

ENABLE_TESTING()
include(CTest)

set(CTEST_PROJECT_NAME "IRIS")
set(CTEST_NIGHTLY_START_TIME "01:00:00 UTC")

set(CTEST_DROP_METHOD "https")
set(CTEST_DROP_SITE "my.cdash.org")
set(CTEST_DROP_LOCATION "/submit.php?project=IRIS")
set(CTEST_DROP_SITE_CDASH TRUE)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(tests)

