# Install script for directory: W:/assimp-5.0.1/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Assimp")
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
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "W:/assimp-5.0.1/build/code/Debug/assimp-vc142-mtd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "W:/assimp-5.0.1/build/code/Release/assimp-vc142-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "W:/assimp-5.0.1/build/code/MinSizeRel/assimp-vc142-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "W:/assimp-5.0.1/build/code/RelWithDebInfo/assimp-vc142-mt.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "W:/assimp-5.0.1/build/code/Debug/assimp-vc142-mtd.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "W:/assimp-5.0.1/build/code/Release/assimp-vc142-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "W:/assimp-5.0.1/build/code/MinSizeRel/assimp-vc142-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "W:/assimp-5.0.1/build/code/RelWithDebInfo/assimp-vc142-mt.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "W:/assimp-5.0.1/code/../include/assimp/anim.h"
    "W:/assimp-5.0.1/code/../include/assimp/aabb.h"
    "W:/assimp-5.0.1/code/../include/assimp/ai_assert.h"
    "W:/assimp-5.0.1/code/../include/assimp/camera.h"
    "W:/assimp-5.0.1/code/../include/assimp/color4.h"
    "W:/assimp-5.0.1/code/../include/assimp/color4.inl"
    "W:/assimp-5.0.1/build/code/../include/assimp/config.h"
    "W:/assimp-5.0.1/code/../include/assimp/defs.h"
    "W:/assimp-5.0.1/code/../include/assimp/Defines.h"
    "W:/assimp-5.0.1/code/../include/assimp/cfileio.h"
    "W:/assimp-5.0.1/code/../include/assimp/light.h"
    "W:/assimp-5.0.1/code/../include/assimp/material.h"
    "W:/assimp-5.0.1/code/../include/assimp/material.inl"
    "W:/assimp-5.0.1/code/../include/assimp/matrix3x3.h"
    "W:/assimp-5.0.1/code/../include/assimp/matrix3x3.inl"
    "W:/assimp-5.0.1/code/../include/assimp/matrix4x4.h"
    "W:/assimp-5.0.1/code/../include/assimp/matrix4x4.inl"
    "W:/assimp-5.0.1/code/../include/assimp/mesh.h"
    "W:/assimp-5.0.1/code/../include/assimp/pbrmaterial.h"
    "W:/assimp-5.0.1/code/../include/assimp/postprocess.h"
    "W:/assimp-5.0.1/code/../include/assimp/quaternion.h"
    "W:/assimp-5.0.1/code/../include/assimp/quaternion.inl"
    "W:/assimp-5.0.1/code/../include/assimp/scene.h"
    "W:/assimp-5.0.1/code/../include/assimp/metadata.h"
    "W:/assimp-5.0.1/code/../include/assimp/texture.h"
    "W:/assimp-5.0.1/code/../include/assimp/types.h"
    "W:/assimp-5.0.1/code/../include/assimp/vector2.h"
    "W:/assimp-5.0.1/code/../include/assimp/vector2.inl"
    "W:/assimp-5.0.1/code/../include/assimp/vector3.h"
    "W:/assimp-5.0.1/code/../include/assimp/vector3.inl"
    "W:/assimp-5.0.1/code/../include/assimp/version.h"
    "W:/assimp-5.0.1/code/../include/assimp/cimport.h"
    "W:/assimp-5.0.1/code/../include/assimp/importerdesc.h"
    "W:/assimp-5.0.1/code/../include/assimp/Importer.hpp"
    "W:/assimp-5.0.1/code/../include/assimp/DefaultLogger.hpp"
    "W:/assimp-5.0.1/code/../include/assimp/ProgressHandler.hpp"
    "W:/assimp-5.0.1/code/../include/assimp/IOStream.hpp"
    "W:/assimp-5.0.1/code/../include/assimp/IOSystem.hpp"
    "W:/assimp-5.0.1/code/../include/assimp/Logger.hpp"
    "W:/assimp-5.0.1/code/../include/assimp/LogStream.hpp"
    "W:/assimp-5.0.1/code/../include/assimp/NullLogger.hpp"
    "W:/assimp-5.0.1/code/../include/assimp/cexport.h"
    "W:/assimp-5.0.1/code/../include/assimp/Exporter.hpp"
    "W:/assimp-5.0.1/code/../include/assimp/DefaultIOStream.h"
    "W:/assimp-5.0.1/code/../include/assimp/DefaultIOSystem.h"
    "W:/assimp-5.0.1/code/../include/assimp/ZipArchiveIOSystem.h"
    "W:/assimp-5.0.1/code/../include/assimp/SceneCombiner.h"
    "W:/assimp-5.0.1/code/../include/assimp/fast_atof.h"
    "W:/assimp-5.0.1/code/../include/assimp/qnan.h"
    "W:/assimp-5.0.1/code/../include/assimp/BaseImporter.h"
    "W:/assimp-5.0.1/code/../include/assimp/Hash.h"
    "W:/assimp-5.0.1/code/../include/assimp/MemoryIOWrapper.h"
    "W:/assimp-5.0.1/code/../include/assimp/ParsingUtils.h"
    "W:/assimp-5.0.1/code/../include/assimp/StreamReader.h"
    "W:/assimp-5.0.1/code/../include/assimp/StreamWriter.h"
    "W:/assimp-5.0.1/code/../include/assimp/StringComparison.h"
    "W:/assimp-5.0.1/code/../include/assimp/StringUtils.h"
    "W:/assimp-5.0.1/code/../include/assimp/SGSpatialSort.h"
    "W:/assimp-5.0.1/code/../include/assimp/GenericProperty.h"
    "W:/assimp-5.0.1/code/../include/assimp/SpatialSort.h"
    "W:/assimp-5.0.1/code/../include/assimp/SkeletonMeshBuilder.h"
    "W:/assimp-5.0.1/code/../include/assimp/SmoothingGroups.h"
    "W:/assimp-5.0.1/code/../include/assimp/SmoothingGroups.inl"
    "W:/assimp-5.0.1/code/../include/assimp/StandardShapes.h"
    "W:/assimp-5.0.1/code/../include/assimp/RemoveComments.h"
    "W:/assimp-5.0.1/code/../include/assimp/Subdivision.h"
    "W:/assimp-5.0.1/code/../include/assimp/Vertex.h"
    "W:/assimp-5.0.1/code/../include/assimp/LineSplitter.h"
    "W:/assimp-5.0.1/code/../include/assimp/TinyFormatter.h"
    "W:/assimp-5.0.1/code/../include/assimp/Profiler.h"
    "W:/assimp-5.0.1/code/../include/assimp/LogAux.h"
    "W:/assimp-5.0.1/code/../include/assimp/Bitmap.h"
    "W:/assimp-5.0.1/code/../include/assimp/XMLTools.h"
    "W:/assimp-5.0.1/code/../include/assimp/IOStreamBuffer.h"
    "W:/assimp-5.0.1/code/../include/assimp/CreateAnimMesh.h"
    "W:/assimp-5.0.1/code/../include/assimp/irrXMLWrapper.h"
    "W:/assimp-5.0.1/code/../include/assimp/BlobIOSystem.h"
    "W:/assimp-5.0.1/code/../include/assimp/MathFunctions.h"
    "W:/assimp-5.0.1/code/../include/assimp/Macros.h"
    "W:/assimp-5.0.1/code/../include/assimp/Exceptional.h"
    "W:/assimp-5.0.1/code/../include/assimp/ByteSwapper.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "W:/assimp-5.0.1/code/../include/assimp/Compiler/pushpack1.h"
    "W:/assimp-5.0.1/code/../include/assimp/Compiler/poppack1.h"
    "W:/assimp-5.0.1/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "W:/assimp-5.0.1/build/code/Debug/assimp-vc142-mtd.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "W:/assimp-5.0.1/build/code/RelWithDebInfo/assimp-vc142-mt.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
endif()

