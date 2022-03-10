cmake_minimum_required(VERSION 3.17)

project(RExVicon VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MESSAGE_CONTEXT RExVicon)
include(CMakePrintHelpers)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

####################
# Build
####################
# include(getZMQ)
# include(getFMT)
# include(getViconSDK)
# include(getLibserialport)
add_subdirectory(deps)

####################
# Build
####################
add_subdirectory(src)