# Install script for directory: C:/Users/Paul/Downloads/bullet-2.82-r2704/bullet-2.82-r2704/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/BULLET_PHYSICS")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/btBulletCollisionCommon.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/btBulletDynamicsCommon.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/Bullet-C-Api.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "C:/Program Files (x86)/BULLET_PHYSICS/include/bullet" TYPE FILE FILES
    "C:/Users/Paul/Downloads/bullet-2.82-r2704/bullet-2.82-r2704/src/btBulletCollisionCommon.h"
    "C:/Users/Paul/Downloads/bullet-2.82-r2704/bullet-2.82-r2704/src/btBulletDynamicsCommon.h"
    "C:/Users/Paul/Downloads/bullet-2.82-r2704/bullet-2.82-r2704/src/Bullet-C-Api.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/vmInclude.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath" TYPE FILE FILES "C:/Users/Paul/Downloads/bullet-2.82-r2704/bullet-2.82-r2704/src/vectormath/vmInclude.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/scalar/boolInVec.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/scalar/floatInVec.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/scalar/mat_aos.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/scalar/quat_aos.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/scalar/vec_aos.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/scalar/vectormath_aos.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/scalar" TYPE FILE FILES
    "C:/Users/Paul/Downloads/bullet-2.82-r2704/bullet-2.82-r2704/src/vectormath/scalar/boolInVec.h"
    "C:/Users/Paul/Downloads/bullet-2.82-r2704/bullet-2.82-r2704/src/vectormath/scalar/floatInVec.h"
    "C:/Users/Paul/Downloads/bullet-2.82-r2704/bullet-2.82-r2704/src/vectormath/scalar/mat_aos.h"
    "C:/Users/Paul/Downloads/bullet-2.82-r2704/bullet-2.82-r2704/src/vectormath/scalar/quat_aos.h"
    "C:/Users/Paul/Downloads/bullet-2.82-r2704/bullet-2.82-r2704/src/vectormath/scalar/vec_aos.h"
    "C:/Users/Paul/Downloads/bullet-2.82-r2704/bullet-2.82-r2704/src/vectormath/scalar/vectormath_aos.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/sse/boolInVec.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/sse/floatInVec.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/sse/mat_aos.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/sse/quat_aos.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/sse/vec_aos.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/sse/vecidx_aos.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/sse/vectormath_aos.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/sse" TYPE FILE FILES
    "C:/Users/Paul/Downloads/bullet-2.82-r2704/bullet-2.82-r2704/src/vectormath/sse/boolInVec.h"
    "C:/Users/Paul/Downloads/bullet-2.82-r2704/bullet-2.82-r2704/src/vectormath/sse/floatInVec.h"
    "C:/Users/Paul/Downloads/bullet-2.82-r2704/bullet-2.82-r2704/src/vectormath/sse/mat_aos.h"
    "C:/Users/Paul/Downloads/bullet-2.82-r2704/bullet-2.82-r2704/src/vectormath/sse/quat_aos.h"
    "C:/Users/Paul/Downloads/bullet-2.82-r2704/bullet-2.82-r2704/src/vectormath/sse/vec_aos.h"
    "C:/Users/Paul/Downloads/bullet-2.82-r2704/bullet-2.82-r2704/src/vectormath/sse/vecidx_aos.h"
    "C:/Users/Paul/Downloads/bullet-2.82-r2704/bullet-2.82-r2704/src/vectormath/sse/vectormath_aos.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/Paul/Documents/BigOnion/BulletPhysics/src/BulletSoftBody/cmake_install.cmake")
  include("C:/Users/Paul/Documents/BigOnion/BulletPhysics/src/BulletCollision/cmake_install.cmake")
  include("C:/Users/Paul/Documents/BigOnion/BulletPhysics/src/BulletDynamics/cmake_install.cmake")
  include("C:/Users/Paul/Documents/BigOnion/BulletPhysics/src/LinearMath/cmake_install.cmake")
  include("C:/Users/Paul/Documents/BigOnion/BulletPhysics/src/MiniCL/cmake_install.cmake")
  include("C:/Users/Paul/Documents/BigOnion/BulletPhysics/src/BulletMultiThreaded/cmake_install.cmake")

endif()

