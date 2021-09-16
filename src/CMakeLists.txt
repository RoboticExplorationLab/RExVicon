add_compile_options(-Wall -Wextra -pedantic -Werror)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Include the src/ folder in all targets
# Makes all includes releative to src/ folder
include_directories(
  "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

get_target_property(CPPZMQ_INCLUDE_DIR cppzmq INTERFACE_INCLUDE_DIRECTORIES)
cmake_print_variables(CPPZMQ_INCLUDE_DIR)
get_target_property(ZMQ_INCLUDE_DIR libzmq INTERFACE_INCLUDE_DIRECTORIES)
cmake_print_variables(ZMQ_INCLUDE_DIR)

add_library(rexvicon_driver
  vicon_driver.hpp
  vicon_driver.cpp

  pose.hpp
  pose.cpp

  callbacks.hpp
  callbacks.cpp

  utils.hpp
  utils.cpp
)


target_link_libraries(rexvicon_driver
  PUBLIC
  cppzmq

  PRIVATE
  ViconSDK::ViconSDK
  fmt::fmt
)

add_library(RExVicon::vicon_driver ALIAS rexvicon_driver)
set_target_properties(rexvicon_driver PROPERTIES
  OUTPUT_NAME vicon_driver # sets the name of the installed library
  EXPORT_NAME vicon_driver # sets the name of the imported target
)
target_include_directories(rexvicon_driver
  PUBLIC
  ${Boost_INLCUDE_DIRS}
)

# Install the library
install(TARGETS rexvicon_driver 
  EXPORT RExVicon_export # add to the export set
)


# Add tests
add_subdirectory(test)