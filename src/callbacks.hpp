#pragma once


#include <chrono>
#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <fmt/core.h>
#include <fmt/ostream.h>
#include <libserialport.h>
#include <zmq.hpp>

#include "src/arduino/teensy_receiver/pose.hpp" 
#include "src/utils.hpp"

namespace rexlab {

class SerialCallback {
 public:
  SerialCallback(const std::string& port_name, int baudrate);
  bool Open();
  bool IsOpen() { return is_open_; }
  void Close();
  bool WriteBytes(const char* data, size_t size);
  void SetTimeout(int time_ms);

  template <class Duration>
  void SetTimeout(Duration time) {
    timeout_ = time;
  }


  template <class T>
  void operator()(const Pose<T>& pose) {
    WriteBytes(pose.GetData(), pose.NumBytes());
  }

 private:
  std::string port_name_;
  int baud_rate_;
  struct sp_port* port_;
  bool is_open_ = false;
  std::chrono::milliseconds timeout_;
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

  template <class... Args>
  SerialZMQCallback(const std::string& port_name, int baudrate, Args... args) 
      : zmq_(std::forward<Args>(args)...), ser_(port_name, baudrate) {}

  template <class T>
  void operator()(const Pose<T>& pose) {
    zmq_(pose);
    ser_(pose);
  }

 private:
  ZMQCallback zmq_;
  SerialCallback ser_;
};

}  // namespace rexlab
