#pragma once

#include <string>
#include <stdexcept>
#include <vector>

#include <libserialport.h>

namespace rexlab {

std::string MakeTcpAddress(const std::string& addr);

class TcpAddress {
public:
  TcpAddress();
  TcpAddress(std::string addr_, int port);
  TcpAddress(std::string addr_);
  TcpAddress(TcpAddress&& other);
  std::string ToString();
  static constexpr int kAnyPort = -1; 

 private:
  std::string addr_;
  int port_ = kAnyPort;
};

std::vector<std::string> GetPortList();

class LibSerialPortError : public std::runtime_error {
 public:
  LibSerialPortError(std::string arg) : std::runtime_error(std::move(arg)) {}
};

bool LibSerialCheck(enum sp_return result);

} // namespace rexlab
