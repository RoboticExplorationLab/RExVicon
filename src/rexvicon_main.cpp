#include <unistd.h>
#include <iostream>

#include <fmt/core.h>
#include <fmt/ostream.h>

#include "src/callbacks.hpp"
#include "src/vicon_driver.hpp"

namespace rexlab {

void usage()
{
    std::cout << "- v / --vicon_ip : IP address of Vicon server\n"
                 "-sp / --serial-port : The name of the serial port to print to(default / dev / ttyACM0)\n"
                 "- b / --baud_rate : Baud rate of the serial port(default 57600)\n"
                 "- a / --ipaddres : IP address on which to publish the ZMQ data(default 192.168.3.134)\n"
                 "- p / --port : Port on which which to publish the ZMQ data(default 5555)\n"
                 "- t / --subject : Name of the Vicon object to publish(default rex1)\n"
                 "- w / --wait : Wait indefinitely to connect to the vicon, recommended if running on startup(default false).";
}

bool IsConnectedToVicon(const std::string &vicon_ip_addr,
                        const std::string &subject_name,
                        bool wait_to_connect = false)
{
  ViconDriver driver;
  ViconDriverOptions opts;
  opts.wait_to_connect = wait_to_connect;
  opts.server_id = vicon_ip_addr;
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

void Run(const std::string &vicon_ip_addr,
         const std::string &port_name, int baud_rate,
         const std::string &ip_addr, int port,
         const std::string &subject_name)
{
  ViconDriver driver;
  ViconDriverOptions opts;
  opts.server_id = vicon_ip_addr;
  driver.Initialize(opts);

  SerialZMQCallback callback(port_name, baud_rate, ip_addr, port);
  driver.AddCallback(subject_name, std::ref(callback));

  driver.RunLoop();
}

}  // namespace rexlab

int main(int argc, char* argv[]) {
  std::string vicon_ip_addr = "192.168.3.137";
  std::string port_name = "/dev/ttyACM0";
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
    if (*it == "-v" || *it == "--vicon_port") {
      ip_addr = stoi(*(++it));
    }
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
  rexlab::IsConnectedToVicon(vicon_ip_addr, subject, wait_to_connect);
  rexlab::Run(vicon_ip_addr, port_name, baud_rate, ip_addr, port, subject);
  return 0;
}