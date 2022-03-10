include(FetchContent)

# Declare all dependencies first
# Allows for us to control shared dependencies


# find_package(ViconSDK REQUIRED)
# add_library(ViconSDK3 INTERFACE)
# target_link_libraries(ViconSDK3
#   INTERFACE
#   ${ViconSDK_LIB}
# )
# target_include_directories(ViconSDK3
#   INTERFACE
#   ${ViconSDK_LOCATION}
#   ${ViconSDK_INCLUDE_DIRS}
# )
# add_library(ViconSDK::ViconSDK ALIAS ViconSDK3)

include(getFMT.cmake)
include(getZMQ.cmake)
include(getLibserialport.cmake)
