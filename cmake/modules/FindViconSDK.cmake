set(projPrefix ViconSDK)

list(APPEND CMAKE_MESSAGE_CONTEXT FindViconSDK)

# Get the system-specific sub-directory for the SDK
set(SDK_SYSDIR)
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(SDK_SYSDIR, "Linux64" FILEPATH)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Mac")
    set(SDK_SYSDIR, "Mac64" FILEPATH)
endif()

# Find the SDK header
find_file(SDK_HEADER DataStreamClient.h
    PATHS ${PROJECT_SOURCE_DIR}/ViconSDK/Linux64 ${PROJECT_SOURCE_DIR}/ViconSDK
    NO_DEFAULT_PATH
)
find_file(SDK_HEADER DataStreamClient.h)

# Find the SDK Library
find_library(SDK_LIB ViconDataStreamSDK_CPP
    PATHS ${PROJECT_SOURCE_DIR}/ViconSDK/Linux64 ${PROJECT_SOURCE_DIR}/ViconSDK
    NO_DEFAULT_PATH
)
find_library(SDK_LIB ViconDataStreamSDK_CPP)
cmake_print_variables(SDK_LIB)

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
    set(ViconSDK_ROOT_DIR SDK_INCLUDE_DIR)
    set(ViconSDK_INCLUDE_DIRS ${SDK_INCLUDE_DIR})
    set(ViconSDK_LIB ${SDK_LIB})
    set(ViconSDK_FOUND TRUE)
endif()


list(POP_BACK CMAKE_MESSAGE_CONTEXT FindViconSDK)