cmake_minimum_required(VERSION 3.17)

project(RExVicon VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -pedantic -Werror)

list(APPEND CMAKE_MESSAGE_CONTEXT RExVicon)
include(CMakePrintHelpers)
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

####################
# Options 
####################
set(OPTION_PREFIX "REXVICON")
option(${OPTION_PREFIX}_BUILD_TESTS "Build test suite for package ${CMAKE_PROJECT_NAME}" ON)

enable_testing()
include(GoogleTest)
include(CTest)

####################
# Dependencies 
####################
add_subdirectory(deps)
find_package(ViconSDK REQUIRED)

####################
# Build
####################
add_subdirectory(src)