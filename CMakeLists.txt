cmake_minimum_required(VERSION 3.17)

project(RExVicon VERSION 0.1 LANGUAGES C CXX)
list(APPEND CMAKE_MESSAGE_CONTEXT RExVicon)

add_subdirectory(ViconSDK)

include(CMakePrintHelpers)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

find_package(ViconSDK REQUIRED)
cmake_print_variables(ViconSDK_FOUND)

add_executable(main
    main.cpp
)
target_link_libraries(main
    PRIVATE
    ViconSDK::ViconSDK
)