include(FindPackageHandleStandardArgs)

set(SDK_DIR ${PROJECT_SOURCE_DIR}/ViconSDK)

# Get the system-specific sub-directory for the SDK ie Mac of Linux
set(SYS_SDK_DIR)
if(APPLE)
    set(SYS_SDK_DIR "${SDK_DIR}/Mac64/")
elseif (UNIX)
    set(SYS_SDK_DIR "${SDK_DIR}/Linux64/")
endif()

# Find the path to DataStreamClient.h
find_path(SDK_INCLUDE_DIRS
    NAMES DataStreamClient.h
    PATHS ${SYS_SDK_DIR}
    NO_DEFAULT_PATH
    REQUIRED
)
MESSAGE(STATUS "ViconSDK Include path: ${SDK_INCLUDE_DIRS}")

# Find the path to libViconDataStreamSDK_CPP.dylib
find_library(SDK_LIB
    NAMES ViconDataStreamSDK_CPP
    PATHS ${SYS_SDK_DIR}
    NO_DEFAULT_PATH
    REQUIRED
)

MESSAGE( STATUS "ViconSDK libraries: ${SDK_LIB}")

set(ViconSDK_LIBRARIES ViconSDK)
set(ViconSDK_ROOT_DIR ${SDK_INCLUDE_DIRS})
set(ViconSDK_INCLUDE_DIRS ${SDK_INCLUDE_DIRS})
set(ViconSDK_LIB ${SDK_LIB})
set(ViconSDK_FOUND TRUE)


# # Base directory of Vicon SDK
# set(ViconSDK_DIR ${PROJECT_SOURCE_DIR}/ViconSDK)

# # Get the system-specific sub-directory for the SDK ie Mac of Linux
# set(SYS_ViconSDK_DIR)
# if(APPLE)
#     set(SYS_ViconSDK_DIR "${ViconSDK_DIR}/Mac64/")
# elseif (UNIX)
#     set(SYS_ViconSDK_DIR "${ViconSDK_DIR}/Linux64/")
# endif()

# find_path(ViconSDK_INCLUDE_DIRS
#     NAMES DataStreamClient.h
#     PATHS ${SYS_ViconSDK_DIR}
#     REQUIRED
# )
# MESSAGE( STATUS "ViconSDK Include path: ${ViconSDK_INCLUDE_DIRS}")
# find_library(ViconSDK_LIBRARIES
#     NAMES ViconDataStreamSDK_CPP
#     PATHS ${SYS_ViconSDK_DIR}
#     REQUIRED
# )
# MESSAGE( STATUS "ViconSDK libraries: ${ViconSDK_LIBRARIES}")


# add_library(ViconSDK INTERFACE)
# set_target_properties(ViconSDK PROPERTIES
#     IMPORTED_LOCATION
#        ${ViconSDK_LIBRARIES}
# )
# target_include_directories(ViconSDK
#     INTERFACE
#         ${ViconSDK_INCLUDE_DIRS}
# )
# add_library(ViconSDK::ViconSDK ALIAS ViconSDK)

# # Find the SDK header
# find_file(ViconSDK_HEADER DataStreamClient.h
#     PATHS ${SYS_ViconSDK_DIR}
#     NO_DEFAULT_PATH
#     REQUIRED
# )
# cmake_print_variables(ViconSDK_HEADER)

# # Find the ViconSDK Library
# find_library(ViconSDK_LIB NAMES ViconDataStreamSDK_CPP
#     PATHS ${SYS_ViconSDK_DIR}
#     NO_DEFAULT_PATH
#     REQUIRED
# )
# get_filename_component(ViconSDK_INCLUDE_DIRS ${ViconSDK_HEADER} DIRECTORY)
# cmake_print_variables(ViconSDK_LIB)
# cmake_print_variables(ViconSDK_INCLUDE_DIRS)

# find_package(ViconSDK
#     PATHS ${SYS_ViconSDK_DIR}
#     NO_DEFAULT_PATH
#     REQUIRED
# )
# cmake_print_variables(ViconSDK_LIB)

# add_library(ViconSDK SHARED IMPORTED GLOBAL)
# target_include_directories(ViconSDK
#     INTERFACE
#         ${ViconSDK_INCLUDE_DIRS}
# )
# set_target_properties(ViconSDK PROPERTIES
#     IMPORTED_LOCATION
#        ${ViconSDK_LIB}
# )
# cmake_print_variables(ViconSDK_LIB)