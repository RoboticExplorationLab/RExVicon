#pragma once

#include <string>

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


} // namespace rexlab
