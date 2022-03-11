# include(FindPackageHandleStandardArgs)

# set(SDK_DIR ${PROJECT_SOURCE_DIR}/ViconSDK)

# # Get the system-specific sub-directory for the SDK ie Mac of Linux
# set(SYS_SDK_DIR)
# if(APPLE)
#     set(SYS_SDK_DIR "${SDK_DIR}/Mac64/")
# elseif (UNIX)
#     set(SYS_SDK_DIR "${SDK_DIR}/Linux64/")
# endif()

# # Find the path to DataStreamClient.h
# find_path(SDK_INCLUDE_DIRS
#     NAMES DataStreamClient.h
#     PATHS ${SYS_SDK_DIR}
#     NO_DEFAULT_PATH
#     REQUIRED
# )
# MESSAGE(STATUS "ViconSDK Include path: ${SDK_INCLUDE_DIRS}")

# # Find the path to libViconDataStreamSDK_CPP.dylib
# find_library(SDK_LIB
#     NAMES ViconDataStreamSDK_CPP
#     PATHS ${SYS_SDK_DIR}
#     NO_DEFAULT_PATH
#     REQUIRED
# )
# MESSAGE( STATUS "ViconSDK libraries: ${SDK_LIB}")

# # Set all neccessary variables
# set(ViconSDK_LIBRARIES ViconSDK::ViconSDK)
# set(ViconSDK_ROOT_DIR ${SDK_INCLUDE_DIRS})
# set(ViconSDK_INCLUDE_DIRS ${SDK_INCLUDE_DIRS})
# set(ViconSDK_LIB ${SDK_LIB})
# set(ViconSDK_FOUND TRUE)