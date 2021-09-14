add_library(vicon_driver
  vicon_driver.hpp
  vicon_driver.cpp

  pose.hpp
  pose.cpp
)
target_link_libraries(vicon_driver
  PRIVATE
  ViconSDK::ViconSDK
)

add_library(pose
  pose.hpp
  pose.cpp
)

add_subdirectory(test)