#include <iostream>
#include <gtest/gtest.h>
#include <limits>
#include <fmt/core.h>

#include "src/pose.hpp"
#include "src/vicon_driver.hpp"

namespace rexlab {

TEST(ViconConnection, Connect) {
  ViconDriver driver;
  ViconDriverOptions opts;
  opts.server_id = "192.168.3.249";
  driver.Initialize(opts);
  fmt::print("Is Connected to Vicon at server address {}? {}\n", 
      opts.server_id, driver.IsConnected());
}

}  // namespace rexlab