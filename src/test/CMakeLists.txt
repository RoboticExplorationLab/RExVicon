find_package(PkgConfig)
pkg_check_modules(LIBSP libserialport)
cmake_print_variables(LIBSP_VERSION)
cmake_print_variables(LIBSP_LIBRARIES)
cmake_print_variables(LIBSP_LINK_LIBRARIES)
cmake_print_variables(LIBSP_LIBRARY_DIRS)

function(rexvicon_test test_name)
  add_executable(${test_name}
    ${test_name}.cpp
  )
  target_link_libraries(${test_name}
    PRIVATE
    gtest_main
    fmt::fmt
    RExVicon::vicon_driver
    ViconSDK::ViconSDK
    libserialport
  )
  gtest_discover_tests(${test_name})
endfunction()


rexvicon_test(pose_test)
rexvicon_test(callbacks_test)
rexvicon_test(vicon_connection_test)
# rexvicon_test(zmq_pub_test)
# rexvicon_test(serial_write_test)
# rexvicon_test(simple_serial_test)

add_executable(simple_serial_test
  # port_config.c
  simple_serial_test.cpp
)
target_link_libraries(simple_serial_test
  PRIVATE
  fmt::fmt
  RExVicon::vicon_driver
  ViconSDK::ViconSDK
  libserialport
)