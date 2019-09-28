# Install script for directory: D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/bullet" TYPE FILE FILES
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientC_API.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientSharedMemory_C_API.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientSharedMemory2_C_API.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsDirectC_API.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientUDP_C_API.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientTCP_C_API.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/SharedMemoryInProcessPhysicsC_API.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/SharedMemoryPublic.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/b3RobotSimulatorClientAPI_NoGUI.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/b3RobotSimulatorClientAPI_NoDirect.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/bullet_robotics" TYPE FILE FILES
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/Common2dCanvasInterface.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonCallbacks.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonCameraInterface.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonExampleInterface.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonFileIOInterface.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonGraphicsAppInterface.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonGUIHelperInterface.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonMultiBodyBase.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonParameterInterface.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonRenderInterface.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonRigidBodyBase.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonWindowInterface.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/OpenGLWindow/SimpleCamera.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/TinyRenderer/geometry.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/TinyRenderer/model.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/TinyRenderer/tgaimage.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/TinyRenderer/our_gl.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/TinyRenderer/TinyRenderer.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/plugins/collisionFilterPlugin/collisionFilterPlugin.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/plugins/pdControlPlugin/pdControlPlugin.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/b3RobotSimulatorClientAPI_NoGUI.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/b3RobotSimulatorClientAPI_NoDirect.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/IKTrajectoryHelper.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/plugins/tinyRendererPlugin/tinyRendererPlugin.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/plugins/tinyRendererPlugin/TinyRendererVisualShapeConverter.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/InProcessMemory.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsServer.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClient.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsServerSharedMemory.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsDirect.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsDirectC_API.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsServerCommandProcessor.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/b3PluginManager.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientSharedMemory.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientSharedMemory_C_API.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientC_API.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/SharedMemoryPublic.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/Win32SharedMemory.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PosixSharedMemory.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Utils/b3ResourcePath.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Utils/RobotLoggingUtil.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Utils/b3Clock.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Utils/b3ResourcePath.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Utils/ChromeTraceUtil.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Utils/b3ERPCFMHelper.hpp"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Utils/b3ReferenceFrameHelper.hpp"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/tinyxml2/tinyxml2.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/stb_image/stb_image.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/BussIK/Jacobian.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/BussIK/LinearR2.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/BussIK/LinearR3.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/BussIK/LinearR4.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/BussIK/MatrixRmn.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/BussIK/Node.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/BussIK/Tree.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/BussIK/VectorRn.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportColladaDemo/LoadMeshFromCollada.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportObjDemo/LoadMeshFromObj.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportObjDemo/Wavefront2GLInstanceGraphicsShape.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportMJCFDemo/BulletMJCFImporter.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportURDFDemo/BulletUrdfImporter.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportURDFDemo/MyMultiBodyCreator.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportURDFDemo/URDF2Bullet.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportURDFDemo/UrdfParser.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportURDFDemo/urdfStringSplit.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportURDFDemo/URDFImporterInterface.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportURDFDemo/URDFJointTypes.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportURDFDemo/SDFAudioTypes.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportURDFDemo/UrdfRenderingInterface.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportURDFDemo/MultiBodyCreationInterface.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportMeshUtility/b3ImportMeshUtility.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/MultiThreading/b3PosixThreadSupport.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/MultiThreading/b3Win32ThreadSupport.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/MultiThreading/b3ThreadSupportInterface.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientUDP.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientUDP_C_API.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/enet/include/enet/win32.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/enet/include/enet/unix.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/enet/include/enet/callbacks.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/enet/include/enet/list.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/enet/include/enet/protocol.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientTCP.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientTCP_C_API.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/clsocket/src/SimpleSocket.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/clsocket/src/ActiveSocket.h"
    "D:/Documents/BigOnion/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/clsocket/src/PassiveSocket.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Documents/BigOnion/bullet/lib/Debug/BulletRobotics_Debug.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Documents/BigOnion/bullet/lib/Release/BulletRobotics.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Documents/BigOnion/bullet/lib/MinSizeRel/BulletRobotics_MinsizeRel.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Documents/BigOnion/bullet/lib/RelWithDebInfo/BulletRobotics_RelWithDebugInfo.lib")
  endif()
endif()

