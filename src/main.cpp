#include <unistd.h>
#include <iostream>

#include <fmt/core.h>
#include <fmt/ostream.h>

#include "src/callbacks.hpp"
#include "src/vicon_driver.hpp"

namespace rexlab {

const std::string kViconServerAddress = "192.168.3.249";

bool IsConnectedToVicon(const std::string& subject_name, bool wait_to_connect = false) {
  ViconDriver driver;
  ViconDriverOptions opts;
  opts.wait_to_connect = wait_to_connect;
  opts.server_id = kViconServerAddress;
  driver.Initialize(opts);

  if (driver.IsConnected()) {
    Pose<float> pose;
    try {
      pose = driver.TestSubject(subject_name);
      fmt::print("Got pose:\n{}\n", pose);
      Pose<int32_t> msg = ConvertPoseFloatToInt<int32_t>(pose);
      fmt::print("Vicon Msg:\n{}\n", msg);
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
  std::string port_name = "/dev/ttyAMC0";
  int baud_rate = 57600;
  std::string ip_addr = "192.168.3.134"; 
  int port = 5555; 
  std::string subject = "rex1";
  bool wait_to_connect = false;

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
    if (*it == "-w" || *it == "--wait") {
		  wait_to_connect = true;	
    }
  }

  std::cout << "This is the RExLab Vicon Driver\n";
  rexlab::IsConnectedToVicon(subject, wait_to_connect);
  rexlab::Run(port_name, baud_rate, ip_addr, port, subject);
  return 0;
}
