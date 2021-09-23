#include <iostream>
#include <gtest/gtest.h>
#include <limits>
#include <fmt/core.h>

#include "src/arduino/libraries/Pose/Pose.hpp"
#include "src/vicon_driver.hpp"
#include "src/callbacks.hpp"

namespace rexlab {

// TEST(ZMQPubTest, PrintTest) {
//   ViconDriver driver;
//   ViconDriverOptions opts;
//   opts.server_id = "192.168.3.249";
//   driver.Initialize(opts);
//   fmt::print("Is Connected to Vicon at server address {}? {}\n", 
//       opts.server_id, driver.IsConnected());

//   PrintCallback print_callback;
//   driver.AddCallback("rex1", std::ref(print_callback));
//   driver.RunLoop();
// }

TEST(ZMQPubTest, PubTest) {
  ViconDriver driver;
  ViconDriverOptions opts;
  opts.server_id = "192.168.3.249";
  driver.Initialize(opts);
  fmt::print("Is Connected to Vicon at server address {}? {}\n", 
      opts.server_id, driver.IsConnected());

  SerialCallback serial_callback("/dev/ttyUSB0", 57600);
  driver.AddCallback("rex1", std::ref(serial_callback));
  Pose<float> pose;
  pose.position_x = 10.0;
  serial_callback(pose);
  driver.RunLoop();

}

}  // namespace rexlab