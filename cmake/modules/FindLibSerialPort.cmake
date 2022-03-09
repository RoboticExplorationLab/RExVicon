# set(libserialport_files ${PROJECT_BINARY_DIR}/_deps/libserialport/src)

# # Find the SDK header
# find_file(SERIALPORT_HEADER libserialport.h
#     PATHS "${SERIALPORT_PREFIX}/libserial-download/"
#     NO_DEFAULT_PATH
#     REQUIRED
# )
# cmake_print_variables(SERIALPORT_HEADER)

# # Find the SDK Library
# find_library(SERIALPORT_LIB NAMES serialport
#     PATHS "${SERIALPORT_PREFIX}/libserialport-build/.libs"
#     NO_DEFAULT_PATH
#     REQUIRED
# )
# cmake_print_variables(SERIALPORT_LIB)

# # Export the library w/ include path
# get_filename_component(SERIALPORT_INCLUDE_DIR ${SERIALPORT_HEADER} DIRECTORY)
# cmake_print_variables(SERIALPORT_INCLUDE_DIR)

# set(serialport_LIBRARIES libserialport)
# set(serialport_ROOT_DIR ${SERIALPORT_INCLUDE_DIR})
# set(serialport_INCLUDE_DIRS ${SERIALPORT_INCLUDE_DIR})
# set(serialport_LIB ${SERIALPORT_LIB})
# set(serialport_FOUND TRUE)

include(ExternalProject)

# Find `make`
find_program(MAKE_EXECUTABLE NAMES make)
set(SERIALPORT_PREFIX ${PROJECT_BINARY_DIR}/_deps/libserialport)
set(SERIALPORT_DIR ${SERIALPORT_PREFIX}/src/libserialport-download)

# Download and build libserial port
externalproject_add(libserialport-download
    PREFIX "${SERIALPORT_PREFIX}"
    GIT_REPOSITORY "https://github.com/sigrokproject/libserialport"
    CONFIGURE_COMMAND ${SERIALPORT_DIR}/autogen.sh && ${SERIALPORT_DIR}/configure
    BUILD_COMMAND ${MAKE_EXECUTABLE}
    INSTALL_COMMAND "" # Dont want sys wide install
    UPDATE_COMMAND "" # don't rebuild every time
)

externalproject_get_property(libserialport-download INSTALL_DIR)
cmake_print_variables(INSTALL_DIR)

add_library(libserialport SHARED IMPORTED GLOBAL)
add_dependencies(libserialport libserialport-download)
target_include_directories(libserialport
    INTERFACE
        ${SERIALPORT_DIR}
)

# # Set location of downloaded serialport libary
externalproject_get_property(libserialport-download INSTALL_DIR)
if (APPLE)
    set_target_properties(libserialport PROPERTIES
        IMPORTED_LOCATION ${INSTALL_DIR}/src/libserialport-download-build/.libs/libserialport.dylib
    )
elseif (UNIX)
    set_target_properties(libserialport PROPERTIES
        IMPORTED_LOCATION ${INSTALL_DIR}/src/libserialport-download-build/.libs/libserialport.so
    )
endif()

get_target_property(TEST libserialport IMPORTED_LOCATION)
if(EXISTS ${TEST})
    message("FOUND LIBSERIALPORT LIBRARY")
else()
    message("FAILED TO FIND LIBSERIALPORT LIBRARY")
endif()