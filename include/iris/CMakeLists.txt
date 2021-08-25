install(FILES
  iris.h
  iris_errno.h
  iris_runtime.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/iris)

install(FILES
  CL/cl.h
  CL/cl_platform.h
  CL/cl_version.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/iris/CL)

install(FILES
  cuda/cuda.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/iris/cuda)

install(FILES
  hexagon/rpcmem.h
  hexagon/AEEStdDef.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/iris/hexagon)

install(FILES
  hip/hip_runtime.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/iris/hip)

install(FILES
  level_zero/ze_api.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/iris/level_zero)

