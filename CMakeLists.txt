cmake_minimum_required(VERSION 3.17)

project(RExVicon VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MESSAGE_CONTEXT RExVicon)
include(CMakePrintHelpers)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

####################
# Dependencies
####################
add_subdirectory(deps)

####################
# Dependencies
####################
add_subdirectory(ViconSDK)

####################
# Build
####################
add_subdirectory(src)