#include <unistd.h>
#include <iostream>

#include <fmt/core.h>
#include <fmt/ostream.h>

#include "src/callbacks.hpp"
#include "src/vicon_driver.hpp"

#include "src/arduino/libraries/Pose/Pose.hpp"

namespace rexlab {

void usage()
{
    std::cout << "-sp / --serial-port : The name of the serial port to print to(default / dev / ttyACM0)\n"
                 "- b / --baud_rate : Baud rate of the serial port(default 57600)\n"
                 "- a / --ipaddres : IP address on which to publish the ZMQ data(default 192.168.3.134)\n"
                 "- p / --port : Port on which which to publish the ZMQ data(default 5555)\n"
                 "- h / --help : Displays this message\n";
}

void Run(const std::string &port_name, int baud_rate,
         const std::string &ip_addr, int port)
{
    SerialZMQCallback callback(port_name, baud_rate, ip_addr, port);
    while (true)
    {
        Pose<float> pose_float(10000);
        pose_float.position_x = 0.0;
        pose_float.position_y = 0.0;
        pose_float.position_z = 0.0;
        pose_float.quaternion_w = 1.0;
        pose_float.quaternion_x = 0.0;
        pose_float.quaternion_y = 0.0;
        pose_float.quaternion_z = 0.0;
        callback.operator()(pose_float);
    }
}
}  // namespace rexlab

int main(int argc, char *argv[])
{
    std::string port_name = "/dev/ttyACM0";
    int baud_rate = 57600;
    std::string ip_addr = "192.168.3.134";
    int port = 5555;

    std::vector<std::string> args;
    for (int i = 0; i < argc; ++i) {
        args.emplace_back(argv[i]);
    }
    for (auto it = args.begin(); it != args.end(); ++it)
    {
        if (*it == "-sp" || *it == "--port")
        {
            port = stoi(*(++it));
        }
        else if (*it == "-sp" || *it == "--serial_port")
        {
            port_name = *(++it);
        }
        else if (*it == "-b" || *it == "--baud_rate")
        {
            baud_rate = stoi(*(++it));
        }
        else if (*it == "-a" || *it == "--ipaddress")
        {
            ip_addr = *(++it);
        }
        else if (*it == "-h" || *it == "--help")
        {
            rexlab::usage();
        }
        else
        {
            rexlab::usage();
        }
    }

    std::cout << "This is the RExLab Vicon Driver\n";
    rexlab::Run(port_name, baud_rate, ip_addr, port);
    return 0;
}