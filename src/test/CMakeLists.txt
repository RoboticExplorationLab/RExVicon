function(rexvicon_test test_name)
  add_executable(${test_name}
    ${test_name}.cpp
  )
  target_link_libraries(${test_name}
    PRIVATE
    gtest_main
    fmt::fmt
    RExVicon::vicon_driver
  )
  gtest_discover_tests(${test_name})
endfunction()

rexvicon_test(pose_test)
rexvicon_test(callbacks_test)

# add_executable(pose_test
#   pose_test.cpp
# )
# target_link_libraries(pose_test
#   PRIVATE
#   gtest_main
#   fmt::fmt
#   RExVicon::vicon_driver
# )
