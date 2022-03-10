include(FetchContent)

FetchContent_Declare(libserial
    GIT_REPOSITORY "https://github.com/sigrokproject/libserialport"
    CONFIGURE_COMMAND ${SERIALPORT_DIR}/autogen.sh && ${SERIALPORT_DIR}/configure
    BUILD_COMMAND ${MAKE_EXECUTABLE}
    INSTALL_COMMAND "" # Dont want sys wide install
    UPDATE_COMMAND "" # don't rebuild every time
)
cmake_print_variables(libzmq_POPULATED)

# include(ExternalProject)

# # Find `make`
# find_program(MAKE_EXECUTABLE NAMES make)
# set(SERIALPORT_PREFIX ${PROJECT_BINARY_DIR}/_deps/libserialport)
# set(SERIALPORT_DIR ${SERIALPORT_PREFIX}/src/libserialport-download)

# # Download and build libserial port
# externalproject_add(libserialport-download
#     PREFIX "${SERIALPORT_PREFIX}"
#     GIT_REPOSITORY "https://github.com/sigrokproject/libserialport"
#     CONFIGURE_COMMAND ${SERIALPORT_DIR}/autogen.sh && ${SERIALPORT_DIR}/configure
#     BUILD_COMMAND ${MAKE_EXECUTABLE}
#     INSTALL_COMMAND "" # Dont want sys wide install
#     UPDATE_COMMAND "" # don't rebuild every time
# )

# if(NOT ${libserialport-download_FOUND})
#     #rerun cmake in initial build
#     #will update cmakecache/project files on first build
#     #so you may have to reload project after first build
#     add_custom_target(Rescan ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} DEPENDS BeaEngine)
# else()
#     #Rescan becomes a dummy target after first build
#     #this prevents cmake from rebuilding cache/projects on subsequent builds
#     add_custom_target(Rescan)
# endif()



# add_library(libserialport SHARED IMPORTED GLOBAL)
# add_dependencies(libserialport libserialport-download)
# target_include_directories(libserialport
#     INTERFACE
#         ${SERIALPORT_DIR}
# )

# # # Set location of downloaded serialport libary
# externalproject_get_property(libserialport-download INSTALL_DIR)
# if (APPLE)
#     set_target_properties(libserialport PROPERTIES
#         IMPORTED_LOCATION ${INSTALL_DIR}/src/libserialport-download-build/.libs/libserialport.dylib
#     )
# elseif (UNIX)
#     set_target_properties(libserialport PROPERTIES
#         IMPORTED_LOCATION ${INSTALL_DIR}/src/libserialport-download-build/.libs/libserialport.so
#     )
# endif()