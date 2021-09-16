#include "src/utils.hpp"

namespace rexlab {


std::string MakeTcpAddress(const std::string& addr) {
  std::string tcp_addr;
  if (addr.rfind("tcp://") == 0) {
    tcp_addr = addr;
  } else {
    tcp_addr = "tcp://" + addr;
  }
  return tcp_addr;
}

TcpAddress::TcpAddress() : addr_(MakeTcpAddress("localhost")) {}
TcpAddress::TcpAddress(std::string addr) : addr_(MakeTcpAddress(std::move(addr))) {}
TcpAddress::TcpAddress(std::string addr, int port) 
    : addr_(MakeTcpAddress(addr)), port_(std::move(port)) {}
TcpAddress::TcpAddress(TcpAddress&& other) : addr_(other.addr_), port_(other.port_) {}

std::string TcpAddress::ToString() {
  std::string port_string;
  if (port_ == kAnyPort) {
    port_string = ":*";
  } else {
    port_string = ":" + std::to_string(port_);
  }
  return addr_ + port_string;
}

} // namespace rexlab
