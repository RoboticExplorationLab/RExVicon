add_compile_options(-Wall -Wextra -pedantic -Werror)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Include the src/ folder in all targets
# Makes all includes releative to src/ folder
include_directories(
  "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

find_package(PkgConfig)
pkg_check_modules(LIBSP libserialport)
add_library(libserialport INTERFACE)
target_link_libraries(libserialport
  INTERFACE
  ${LIBSP_LINK_LIBRARIES}
)
target_include_directories(libserialport
  INTERFACE
  ${LIBSP_INCLUDE_DIRS}
)


get_target_property(CPPZMQ_INCLUDE_DIR cppzmq INTERFACE_INCLUDE_DIRECTORIES)
cmake_print_variables(CPPZMQ_INCLUDE_DIR)
get_target_property(ZMQ_INCLUDE_DIR libzmq INTERFACE_INCLUDE_DIRECTORIES)
cmake_print_variables(ZMQ_INCLUDE_DIR)

add_library(rexvicon_driver
  vicon_driver.hpp
  vicon_driver.cpp

  arduino/libraries/Pose/Pose.hpp

  callbacks.hpp
  callbacks.cpp

  utils.hpp
  utils.cpp
)


target_link_libraries(rexvicon_driver
  PUBLIC
  cppzmq
  ViconSDK::ViconSDK

  PRIVATE
  fmt::fmt
  libserialport
)

add_library(RExVicon::vicon_driver ALIAS rexvicon_driver)
set_target_properties(rexvicon_driver PROPERTIES
  OUTPUT_NAME vicon_driver # sets the name of the installed library
  EXPORT_NAME vicon_driver # sets the name of the imported target
)

# Install the library
install(TARGETS rexvicon_driver 
  EXPORT RExVicon_export # add to the export set
)

# Main executable
add_executable(rexvicon
  main.cpp
)
target_link_libraries(rexvicon
  PRIVATE
  rexvicon_driver
  fmt::fmt
)

# Add tests
if (${OPTION_PREFIX}_BUILD_TESTS)
  add_subdirectory(test)
endif()