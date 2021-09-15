#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <string>

#include <fmt/core.h>
#include <fmt/ostream.h>

#include "src/pose.hpp"

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

}  // namespace rexlab
