add_executable(pose_test
  pose_test.cpp
)
target_link_libraries(pose_test
  PRIVATE
  vicon_driver
)