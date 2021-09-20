#include <fmt/core.h>
#include <fmt/ostream.h>

#include <iostream>

#include "src/callbacks.hpp"
#include "src/vicon_driver.hpp"

namespace rexlab {

const std::string kViconServerAddress = "192.168.3.249";

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

int main(int argc, char* argv[]) {
  std::string port_name = "/dev/ttyUSB0";
  int baud_rate = 57600;
  std::string ip_addr = "127.0.0.1"; 
  int port = rexlab::TcpAddress::kAnyPort;
  std::string subject = "rex1";

  std::vector<std::string> args;
  for (int i = 0; i < argc; ++i) {
    args.emplace_back(argv[i]);
  }
  for (auto it = args.begin(); it != args.end(); ++it) {
    if (*it == "-p" || *it == "--port") {
      port = stoi(*(++it));
    }
    if (*it == "-sp" || *it == "--serial_port") {
      port_name = *(++it);
    }
    if (*it == "-b" || *it == "--baud_rate") {
      baud_rate = stoi(*(++it));
    }
    if (*it == "-a" || *it == "--ipaddress") {
      ip_addr = *(++it);
    }
    if (*it == "-t" || *it == "--subject") {
      subject = *(++it);
    }
  }

  std::cout << "This is the RExLab Vicon Driver\n";
  rexlab::IsConnectedToVicon();
  rexlab::Run(port_name, baud_rate, ip_addr, port, subject);
  return 0;
}