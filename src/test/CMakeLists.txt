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
  )
  gtest_discover_tests(${test_name})
endfunction()

rexvicon_test(pose_test)
rexvicon_test(callbacks_test)
rexvicon_test(vicon_connection_test)
rexvicon_test(zmq_pub_test)