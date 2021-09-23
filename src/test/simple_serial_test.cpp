#include <unistd.h>

#include <chrono>
#include <iostream>
#include <limits>
#include <fmt/core.h>
#include <fmt/chrono.h>
#include <fmt/ostream.h>

#include "src/arduino/libraries/Pose/Pose.hpp"
// #include "src/vicon_driver.hpp"
// #include "src/callbacks.hpp"
#include "src/utils.hpp"

#include <libserialport.h>

namespace rexlab {

struct MyMsg {
  uint8_t msgid = 11;
  bool is_occluded = false;
  int x = 0;
  int y = 0;
  int z = 0;
  int qx = 0;
  int qy = 0;
  int qz = 0;
  int qw = 1;
  MyMsg& operator++() { 
    ++x;
    return *this;
  }
};


void ReadWriteSerial(const std::string& port_name, int baud_rate, bool write = true) {
  bool read = !write;

  struct sp_port* port;
  fmt::print("Looking for port {}\n", port_name);
  LibSerialCheck(sp_get_port_by_name(port_name.c_str(), &port));

  fmt::print("Port name: {}\n", sp_get_port_name(port));
  fmt::print("Port description: {}\n", sp_get_port_description(port));

  fmt::print("Opening Port.\n");
  enum sp_return result = sp_open(port, SP_MODE_READ_WRITE);
  if (result != SP_OK) {
    fmt::print("Couldn't open serial port\n");
    char* err_msg = sp_last_error_message();
    fmt::print("Got error: {}\n", err_msg);
    sp_free_error_message(err_msg);
  }

  fmt::print("Setting port to baudrate {}\n", baud_rate);
  LibSerialCheck(sp_set_baudrate(port, baud_rate));
  LibSerialCheck(sp_set_bits(port, 8));
  LibSerialCheck(sp_set_parity(port, SP_PARITY_NONE));
  LibSerialCheck(sp_set_stopbits(port, 1));
  LibSerialCheck(sp_set_flowcontrol(port, SP_FLOWCONTROL_NONE));

  // MyMsg data;
  Pose<int32_t> data;
  int len = sizeof(data);
  char* buf = reinterpret_cast<char*>(&data);
  std::chrono::duration<unsigned int, std::milli> timeout_ms(10000);

  std::chrono::duration<double, std::ratio<1>> runtime(5);
  auto t_start = std::chrono::high_resolution_clock::now();
  auto t_elapsed = std::chrono::high_resolution_clock::now() - t_start;
  int count = 0;
  bool has_started = false;
  if (write) {
    runtime *= 1.2;
  }

  int receive_fixes = 0;
  while (t_elapsed < runtime) {
    if (has_started) {
      t_elapsed = std::chrono::high_resolution_clock::now() - t_start;
    }
    if (write) {
      sp_blocking_write(port, buf, len, timeout_ms.count());
      has_started = true;
      ++data.position_x;
      sp_drain(port);
      // fmt::print("Writing to serial: {}\n", data.x);
      // usleep(1000 * 1000 / 120);
    } else {
      sp_blocking_read(port, buf, len, timeout_ms.count());
      int extra_bytes = VerifyRead(buf, len, 91);
      if (extra_bytes) {
        sp_blocking_read(port, buf + len - extra_bytes - 1, extra_bytes, timeout_ms.count());
      }

      if (!has_started) {
        t_start = std::chrono::high_resolution_clock::now();
        timeout_ms = std::chrono::milliseconds(500);
        has_started = true;
      }
    }
    count++;
  }
  fmt::print("Message:\n");
  for (int j = 0; j < len; ++j) {
    fmt::print("  Byte {}: {:#x}\n", j, buf[j]);
  }
  fmt::print("\n");

  fmt::print("Final data value: {}\n", data.position_x);
  auto t_total = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1>>>(
      std::chrono::high_resolution_clock::now() - t_start); 
  double rate = count / t_total.count();
  fmt::print("Average rate: {} Hz\n", rate);
  fmt::print("Message size: {} bytes\n", sizeof(MyMsg));
  if (read) {
    fmt::print("Number of read fixes: {}\n", receive_fixes);
  }
  sp_close(port);
  sp_free_port(port);
}

}  // namespace rexlab


int main (int argc, char* argv[]) {
  bool write = true;
  int port_index = 0;
  if (argc == 2) {
    if (std::string(argv[1]) == "read") {
      write = false;
      port_index = 1; 
    }

  }
  std::vector<std::string> port_list = rexlab::GetPortList();
  // if (port_list[0] == "/dev/ttyACM0") {
  //   port_index += 1;
  // }
  for (const auto& name : port_list) {
    fmt::print("Got Port {}\n", name);
  }
  int baud_rate = 115200;
  rexlab::ReadWriteSerial(port_list[port_index], baud_rate, write);
}