add_compile_options(-Wall -Wextra -pedantic -Werror)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Include the src/ folder in all targets
# Makes all includes releative to src/ folder
include_directories(
  "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

find_package(ViconSDK REQUIRED)
add_library(ViconSDK3 INTERFACE)
target_link_libraries(ViconSDK3
  INTERFACE
  ${ViconSDK_LIB}
)
target_include_directories(ViconSDK3
  INTERFACE
  ${ViconSDK_INCLUDE_DIRS}
)
add_library(ViconSDK::ViconSDK ALIAS ViconSDK3)

# cmake_print_variables(CMAKE_INSTALL_INCLUDEDIR)
# cmake_print_variables(CMAKE_SOURCE_DIR)
# cmake_print_variables(CMAKE_CURRENT_BINARY_DIR)

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
    # ViconSDK
    ViconSDK::ViconSDK

  PRIVATE
    fmt
    libserialport
)

# Rexvicon executable
add_executable(rexvicon
  rexvicon_main.cpp
)
target_link_libraries(rexvicon
  PRIVATE
    rexvicon_driver
    fmt
    libserialport
)

# Simulated vicon executable
add_executable(simulated_vicon
  simulated_vicon_main.cpp
)
target_link_libraries(simulated_vicon
  PRIVATE
    rexvicon_driver
    fmt
    libserialport
)