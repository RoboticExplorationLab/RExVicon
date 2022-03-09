set(projPrefix ViconSDK)

set(SERIALPORT_PREFIX ${PROJECT_BINARY_DIR}/_deps/libserialport)
set(SERIALPORT_DIR ${SERIALPORT_PREFIX}/src/libserialport-download)

# Get the system-specific sub-directory for the SDK ie Mac of Linux
set(SYS_SDK_DIR)
if(APPLE)
    set(SYS_SDK_DIR "${SDK_DIR}/Mac64/")
elseif (UNIX)
    set(SYS_SDK_DIR "${SDK_DIR}/Linux64/")
endif()

# Find the SDK header
find_file(SDK_HEADER DataStreamClient.h
    PATHS ${SYS_SDK_DIR}
    NO_DEFAULT_PATH
    # REQUIRED
)
find_file(SDK_HEADER DataStreamClient.h)

# Find the SDK Library
find_library(SDK_LIB NAMES ViconDataStreamSDK_CPP
    PATHS ${SYS_SDK_DIR}
    NO_DEFAULT_PATH
    REQUIRED
)

if ((${SDK_LIB} STREQUAL SDK_LIB-NOTFOUND} OR ${SDK_HEADER} STREQUAL SDK_HEADER-NOTFOUND))
    if (NOT ViconSDK_FIND_QUIETLY)
        message(STATUS "The Vicon DataStream SDK header and library files were not found")
        message(STATUS "Extract the downloaded SDK files for your platform into the `ViconSDK` directory.")
        if(ViconSDK_FIND_REQUIRED)
            message(FATAL_ERROR "The Vicon SDK not found, but was required.")
        endif()
    endif()
    set(ViconSDK_FOUND FALSE)
else()
    # Export the library w/ include path
    get_filename_component(SDK_INCLUDE_DIR ${SDK_HEADER} DIRECTORY)

    set(ViconSDK_LIBRARIES ViconSDK::ViconSDK)
    set(ViconSDK_ROOT_DIR ${SDK_INCLUDE_DIR})
    set(ViconSDK_INCLUDE_DIRS ${SDK_INCLUDE_DIR})
    set(ViconSDK_LIB ${SDK_LIB})
    set(ViconSDK_FOUND TRUE)
endif()

