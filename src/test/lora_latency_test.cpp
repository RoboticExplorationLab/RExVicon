#include <unistd.h>

#include <chrono>
#include <string>

#include <fmt/core.h>
#include <fmt/chrono.h>
#include <fmt/ostream.h>
#include <libserialport.h>

#include "src/arduino/libraries/Pose/Pose.hpp"
#include "src/utils.hpp"

namespace rexlab {

using SerialPort = struct sp_port*;

void setup_port(const SerialPort& port, int baud_rate) {
  enum sp_return result = sp_open(port, SP_MODE_READ_WRITE);
  if (result != SP_OK) {
    fmt::print("Couldn't open serial port\n");
    char* err_msg = sp_last_error_message();
    fmt::print("Got error: {}\n", err_msg);
    sp_free_error_message(err_msg);
  }

  LibSerialCheck(sp_set_baudrate(port, baud_rate));
  LibSerialCheck(sp_set_bits(port, 8));
  LibSerialCheck(sp_set_parity(port, SP_PARITY_NONE));
  LibSerialCheck(sp_set_stopbits(port, 1));
  LibSerialCheck(sp_set_flowcontrol(port, SP_FLOWCONTROL_NONE));

}

void MeasureLatency(const std::string& portname_tx, const std::string& portname_rx,
                    int baud_rate) {
  SerialPort port_tx;
  SerialPort port_rx;

  LibSerialCheck(sp_get_port_by_name(portname_tx.c_str(), &port_tx));
  LibSerialCheck(sp_get_port_by_name(portname_rx.c_str(), &port_rx));

  setup_port(port_tx, baud_rate);
  setup_port(port_rx, baud_rate);
  fmt::print("Tx and Rx are both set up.\n");

  // Set up timeout and timing info
  std::chrono::duration<unsigned int, std::milli> timeout_ms(1000);

  // Set up data buffers
  Pose<int16_t> pose_tx;
  Pose<int16_t> pose_rx;
  constexpr int kMsgLength = sizeof(Pose<int16_t>);
  uint8_t* buf_tx = reinterpret_cast<uint8_t*>(&pose_tx);
  uint8_t* buf_rx = reinterpret_cast<uint8_t*>(&pose_rx);
  (void) buf_rx;
  fmt::print("Sending packets of size {}\n", kMsgLength);

  fmt::print("Sending 1 packet to receiver...\n");
  sp_blocking_write(port_rx, buf_rx, kMsgLength, timeout_ms.count());
  sp_drain(port_rx);

  for (int i = 0; i < 100; ++i) {
    fmt::print("Iter {}, Sending data...\n", i);
    sp_blocking_write(port_tx, buf_tx, kMsgLength, timeout_ms.count());
    sp_drain(port_tx);
  }
  fmt::print("Reading data\n");
  int num_bytes = sp_input_waiting(port_rx);
  char inputbuf[2000];
  fmt::print("Number of bytes waiting: {}\n", num_bytes);
  fmt::print("Got x value of {}\n", pose_rx.position_x);
  sp_blocking_read(port_rx, inputbuf, num_bytes, timeout_ms.count());
  fmt::print("Got message: {}\n", inputbuf);
  fmt::print("Closing ports...");
  sp_close(port_tx);
  sp_close(port_rx);
  sp_free_port(port_tx);
  sp_free_port(port_rx);
  fmt::print(" Ports closed!\n");
}

}  // namespace rexlab


int main () {
  std::string portname_tx = "/dev/ttyACM0";
  std::string portname_rx = "/dev/ttyACM1";
  int baud_rate = 57600;
  rexlab::MeasureLatency(portname_tx, portname_rx, baud_rate);
  return 0;
}