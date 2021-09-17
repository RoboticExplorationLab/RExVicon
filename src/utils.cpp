#include "src/utils.hpp"

#include <fmt/core.h>
#include <libserialport.h>

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

std::vector<std::string> GetPortList() {
  std::vector<std::string> ports;

  struct sp_port** port_list;
  enum sp_return result = sp_list_ports(&port_list);
  if (result != SP_OK) {
    fmt::print("Couldn't get the list of ports\n");
  }

  int i;
  for (i = 0; port_list[i] != NULL; i++) {
    struct sp_port* port = port_list[i];
    ports.emplace_back(sp_get_port_name(port));
  }
  return ports;
}

/* Helper function for error handling. */
bool LibSerialCheck(enum sp_return result) {
  char* err_msg;
  switch (result)
  {
  case SP_ERR_ARG:
    throw(LibSerialPortError("Error: Invalid argument."));
    break;

  case SP_ERR_FAIL:
    err_msg = sp_last_error_message();
    throw(LibSerialPortError("Error: Failed: " + std::string(err_msg)));
    sp_free_error_message(err_msg);
    break;

  case SP_ERR_SUPP:
    throw(LibSerialPortError("Error: Not Supported."));
    break;

  case SP_ERR_MEM:
    throw(LibSerialPortError("Error: Couldn't allocate memory."));
    break;

  case SP_OK:
  default:
    return true;
  }
}
 
} // namespace rexlab
