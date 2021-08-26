option(BUILD_SHARED_LIBS "Build shared libs" ON)

include_directories(${IRIS_INC_DIR})
include_directories(${IRIS_BIN_DIR}/rt)

configure_file(Config.h.in Config.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable")
if (CMAKE_VERSION VERSION_LESS "3.1")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
  set(CMAKE_CXX_STANDARD 11)
endif()

set(IRIS_RUNTIME_SOURCES
  CAPI.cpp
  Command.cpp
  Device.cpp
  Kernel.cpp
  Mem.cpp
  Platform.cpp
  QueueReady.cpp
  QueueTask.cpp
  Releasable.cpp
  Task.cpp
  Thread.cpp
  Timer.cpp
  Utils.cpp
  Worker.cpp
  )

set(IRIS_RUNTIME_HEADERS
  Platform.h
  Timer.h
  Utils.h
  )

add_library(iris ${IRIS_RUNTIME_SOURCES})

install(TARGETS iris DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
  ${IRIS_RUNTIME_HEADERS}
  ${IRIS_BIN_DIR}/rt/Config.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/iris/rt)

