add_compile_options(-Wall -Wextra -pedantic -Werror)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Include the src/ folder in all targets
# Makes all includes releative to src/ folder
include_directories(
  "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

find_package(libserialport)

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

# add_library(RExVicon::vicon_driver ALIAS rexvicon_driver)
# set_target_properties(rexvicon_driver PROPERTIES
#   OUTPUT_NAME vicon_driver # sets the name of the installed library
#   EXPORT_NAME vicon_driver # sets the name of the imported target
# )

# # Install the library
# install(TARGETS rexvicon_driver
#   EXPORT RExVicon_export # add to the export set
# )

# Main executable
add_executable(rexvicon
  rexvicon_main.cpp
)
target_link_libraries(rexvicon
  PRIVATE
    rexvicon_driver
    fmt::fmt
    libserialport
)

# Main executable
add_executable(simulated_vicon
  simulated_vicon_main.cpp
)
target_link_libraries(simulated_vicon
  PRIVATE
    rexvicon_driver
    fmt::fmt
    libserialport
)