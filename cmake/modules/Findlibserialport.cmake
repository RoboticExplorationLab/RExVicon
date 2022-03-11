set(SERIAL_SRC_DIR ${PROJECT_BINARY_DIR}/_deps/libserialport-src)

# Find the path to DataStreamClient.h
find_path(SERIAL_INCLUDE_DIRS
    NAMES libserialport.h
    PATHS ${SERIAL_SRC_DIR}
    NO_DEFAULT_PATH
    REQUIRED
)
MESSAGE(STATUS "libserialport Include path: ${SERIAL_INCLUDE_DIRS}")

# Find the path to libViconDataStreamSDK_CPP.dylib
find_library(SERIAL_LIB
    NAMES serialport
    PATHS "${SERIAL_SRC_DIR}/.libs"
    NO_DEFAULT_PATH
    REQUIRED
)
MESSAGE( STATUS "libserialport libraries: ${SERIAL_LIB}")

# Set all neccessary variables
set(libserialport_LIBRARIES libserialport)
set(libserialport_ROOT_DIR ${SERIAL_INCLUDE_DIRS})
set(libserialport_INCLUDE_DIRS ${SERIAL_INCLUDE_DIRS})
set(libserialport_LIB ${SERIAL_LIB})
set(libserialport_FOUND TRUE)