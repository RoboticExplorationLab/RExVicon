#include "src/callbacks.hpp"
#include <zmq.hpp>

#include "src/utils.hpp"

namespace rexlab {

SerialCallback::SerialCallback(const std::string &port_name, int baud_rate)
    : port_name_(port_name),
      baud_rate_(baud_rate) {}

bool SerialCallback::Open() {
  struct sp_port* port;
  std::string port_name = port_name_;
  int baud_rate = baud_rate_;
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

  try {
    port_ = port;
    is_open_ = true;
    return true;
  } catch(const LibSerialPortError& e) {
    fmt::print("Error Calling libserialport\n");
    char* err_msg = sp_last_error_message();
    fmt::print("Got error: {}\n", err_msg);
    sp_free_error_message(err_msg);
}
  return false;
}

void SerialCallback::Close() {
  if (IsOpen()) {
    sp_close(port_);
    sp_free_port(port_);
    is_open_ = false;
  }
}

void SerialCallback::SetTimeout(int time_ms) {
  timeout_ = std::chrono::milliseconds(time_ms);
}

bool SerialCallback::WriteBytes(const char* data, size_t size) {
  // fmt::print("Writing to serial...\n");
  if (IsOpen()) {
    sp_blocking_write(port_, data, size, timeout_.count());
    return true;
  } else {
    fmt::print("WARNING: Trying to write to a close port!\n");
  }
  return false;
}

void ZMQCallback::WriteBytes(const char* data, size_t size) {
  // fmt::print("Sending ZMQ message...\n");
  socket_.send(zmq::message_t(data, size), zmq::send_flags::none);
}


}  // namespace rexlab
