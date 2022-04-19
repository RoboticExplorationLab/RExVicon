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
    RatePrinter rate_printer;
    rate_printer.Enable();
    rate_printer.Init();

    int i = 0;
    while (true)
    {
        i++;
        rexlab::Pose<float> pose;
        pose.position_x = 0.15;
        pose.position_y = 0.15;
        pose.position_z = 0.05;
        pose.quaternion_w = 1.0;
        pose.quaternion_x = 0.0;
        pose.quaternion_y = 0.0;
        pose.quaternion_z = 0.0;

        callback.operator()<float>(pose);
        rate_printer.Print();
    }
}
}  // namespace rexlab

int main(int argc, char *argv[])
{
    std::string port_name = "/dev/tty.usbmodem14201";
    int baud_rate = 57600;
    std::string ip_addr = "127.0.0.1";
    int port = 5555;

    std::vector<std::string> args;
    for (int i = 0; i < argc; ++i) {
        args.emplace_back(argv[i]);
    }
    for (auto it = args.begin(); it != args.end(); ++it)
    {
        if (*it == "-p" || *it == "--port")
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
            return -1;
        }
    }

    std::cout << "This is the RExLab Vicon Driver\n";
    rexlab::Run(port_name, baud_rate, ip_addr, port);
    return 0;
}