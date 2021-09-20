#include "src/callbacks.hpp"
#include <zmq.hpp>

#include "src/utils.hpp"

namespace rexlab {

SerialCallback::SerialCallback(const std::string &port_name, int baud_rate)
    : port_name_(port_name),
      baud_rate_(baud_rate) {}

bool SerialCallback::Open() {
  try {
    LibSerialCheck(sp_get_port_by_name(port_name_.c_str(), &port_));
    LibSerialCheck(sp_open(port_, SP_MODE_READ_WRITE));
    fmt::print("Connected to port {}\n", port_name_);
    fmt::print("            Name: {}\n", sp_get_port_name(port_));
    fmt::print("     Description: {}\n", sp_get_port_description(port_));
    return true;
  } catch(const LibSerialPortError& e) {
    fmt::print("Error Calling libserialport\n");
    fmt::print("Got error: ", e.what());
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
  fmt::print("Writing to serial...\n");
  if (IsOpen()) {
    sp_blocking_write(port_, data, size, timeout_.count());
    return true;
  }
  return false;
}

void ZMQCallback::WriteBytes(const char* data, size_t size) {
  fmt::print("Sending ZMQ message...\n");
  socket_.send(zmq::message_t(data, size), zmq::send_flags::none);
}


}  // namespace rexlab
