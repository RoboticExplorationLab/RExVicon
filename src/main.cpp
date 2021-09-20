#include <fmt/core.h>
#include <fmt/ostream.h>

#include <iostream>

#include "src/callbacks.hpp"
#include "src/vicon_driver.hpp"

namespace rexlab {

bool IsConnectedToVicon() {
  ViconDriver driver;
  ViconDriverOptions opts;
  opts.server_id = "192.168.3.249";
  driver.Initialize(opts);

  std::string subject_name = "rex1";
  if (driver.IsConnected()) {
    Pose<float> pose;
    try {
      pose = driver.TestSubject(subject_name);
      fmt::print("Got pose:\n{}\n", pose);
    } catch (std::runtime_error& e) {
      fmt::print("FAIL: Failed to get the pose for subject {}\n", subject_name);
      return false;
    }
  } else {
    fmt::print("FAIL: Vicon is not connected\n");
    return false;
  }

  return true;
}

void Run(const std::string& port_name, int baud_rate,
         const std::string& ip_addr, int port,
         const std::string& subject_name) {
  ViconDriver driver;
  ViconDriverOptions opts;
  opts.server_id = "192.168.3.249";
  driver.Initialize(opts);

  SerialZMQCallback callback(port_name, baud_rate, ip_addr, port);
  driver.AddCallback(subject_name, std::ref(callback));

  driver.RunLoop();
}

}  // namespace rexlab

int main() {
  std::cout << "This is the RExLab Vicon Driver\n";
  rexlab::IsConnectedToVicon();
  return 0;
}