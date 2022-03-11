include(FetchContent)

# Declare all dependencies first
# Allows for us to control shared dependencies
include(getFMT.cmake)
include(getZMQ.cmake)
include(getLibserialport.cmake)

# Setup Vicon
# find_package(ViconSDK REQUIRED)
# add_library(ViconSDK3 INTERFACE)
# target_link_libraries(ViconSDK3
#     INTERFACE
#         ${ViconSDK_LIB}
# )
# target_include_directories(ViconSDK3
#     INTERFACE
#         ${ViconSDK_INCLUDE_DIRS}
# )
# # set_target_properties(ViconSDK3
# #     PROPERTIES
# #         INSTALL_RPATH ${ViconSDK_INCLUDE_DIRS}
# #     BUILD_WITH_INSTALL_RPATH TRUE
# # )
# add_library(ViconSDK::ViconSDK ALIAS ViconSDK3)


# list(APPEND CMAKE_INSTALL_RPATH ${ViconSDK_INCLUDE_DIRS})
# cmake_print_variables(CMAKE_INSTALL_RPATH)

# Setup libserialport
find_package(libserialport REQUIRED)
add_library(libserialport3 INTERFACE)
target_link_libraries(libserialport3
    INTERFACE
        ${libserialport_LIB}
)
target_include_directories(libserialport3
    INTERFACE
        ${libserialport_INCLUDE_DIRS}
)
add_library(libserialport::libserialport ALIAS libserialport3)