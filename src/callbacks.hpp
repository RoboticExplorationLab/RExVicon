#pragma once

#include <fmt/core.h>
#include <fmt/ostream.h>

#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <zmq.hpp>

#include "src/pose.hpp"
#include "src/utils.hpp"

namespace rexlab {

class SerialCallback {
 public:
  SerialCallback(const std::string& port_name, int baudrate);
  void Open();
  bool IsOpen() { return serial_port_.is_open(); }
  void Close();
  bool WriteBytes(const char* data, size_t size);

  template <class T>
  void operator()(const Pose<T>& pose) {
    WriteBytes(pose.GetData(), pose.NumBytes());
  }

 private:
  std::string port_name_;
  int baud_rate_;
  boost::asio::io_service io_;
  boost::asio::serial_port serial_port_;
  size_t bytes_transferred_;
};

class PrintCallback {
 public:
  PrintCallback() = default;
  PrintCallback(FILE* io) : io_(io) {}
  PrintCallback(const std::string& filename) : is_file_(true) {
    io_ = fopen(filename.c_str(), "w");
  }

  ~PrintCallback() {
    if (is_file_) {
      fclose(io_);
    }
  }

  template <class T>
  void operator()(const Pose<T>& pose) {
    fmt::print(io_, "{}\n", pose);
  }

 private:
  FILE* io_ = stdout;
  bool is_file_ = false;
};

class ZMQCallback {
 public:

  template <class... Args>
  ZMQCallback(Args... args)
      : addr_(args...), ctx_(), socket_(ctx_, zmq::socket_type::pub) {
    try {
      socket_.bind(addr_.ToString());
      fmt::print("Publisher successfully bound to {}\n", addr_.ToString());
    } catch(const zmq::error_t& e) {
      fmt::print("Error binding publisher to port {}\n", port_name_);
      throw(e);
    }
  }

  void WriteBytes(const char* data, size_t size);

  template <class T>
  void operator()(const Pose<T>& pose) {
    WriteBytes(pose.GetData(), pose.NumBytes());
  }

 private:
  TcpAddress addr_;
  std::string port_name_;
  zmq::context_t ctx_;
  zmq::socket_t socket_;
};

class SerialZMQCallback {
 public:
 private:
  ZMQCallback zmq_;
  SerialCallback ser_;
};

}  // namespace rexlab
