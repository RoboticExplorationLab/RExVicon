set(libserialport_files ${PROJECT_BINARY_DIR}/_deps/libserialport/src)

# Find the SDK header
find_file(SERIALPORT_HEADER libserialport.h
    PATHS "${SERIALPORT_PREFIX}/libserial-download/"
    REQUIRED
)
cmake_print_variables(SERIALPORT_HEADER)

# Find the SDK Library
find_library(SERIALPORT_LIB NAMES libserialport.a serialport
    PATHS "${SERIALPORT_PREFIX}/libserialport-build/.libs"
    REQUIRED
)
cmake_print_variables(SERIALPORT_LIB)

# Export the library w/ include path
get_filename_component(SERIALPORT_INCLUDE_DIR ${SERIALPORT_HEADER} DIRECTORY)
set(libserialport_LIBRARIES libserialport)
set(libserialport_ROOT_DIR ${SERIALPORT_INCLUDE_DIR})
set(libserialport_INCLUDE_DIRS ${SERIALPORT_INCLUDE_DIR})
set(libserialport_LIB ${SERIALPORT_LIB})
set(libserialport_FOUND TRUE)