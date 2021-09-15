#include "src/callbacks.hpp"
#include <zmq.hpp>

namespace rexlab {

SerialCallback::SerialCallback(const std::string &port_name, int baud_rate)
    : port_name_(port_name),
      baud_rate_(baud_rate),
      io_(),
      serial_port_(io_) {}

void SerialCallback::Open() {
  serial_port_.open(port_name_);
  serial_port_.set_option(boost::asio::serial_port_base::baud_rate(baud_rate_));
}

void SerialCallback::Close() {
  if (IsOpen()) {
    serial_port_.close();
  }
}

bool SerialCallback::WriteBytes(const char* data, size_t size) {
  if (IsOpen()) {
    serial_port_.write_some(boost::asio::buffer(data, size));
    return true;
  }
  return false;
}

}  // namespace rexlab
