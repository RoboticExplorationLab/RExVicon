#include "src/utils.hpp"

#include <fmt/core.h>
#include <fmt/chrono.h>
#include <libserialport.h>

namespace rexlab {

void RatePrinter::Init() {
  time_start_ = std::chrono::high_resolution_clock::now();
  count_ = 0;
}

void RatePrinter::Enable() { is_enabled_ = true; }
void RatePrinter::Disable() { is_enabled_ = false; }
bool RatePrinter::IsEnabled() { return is_enabled_; } 
void RatePrinter::SetFrequency(float frequency) { 
  period_ = std::chrono::duration<double, std::ratio<1>>(1.0 / frequency);
}
void RatePrinter::Print() {
  if (IsEnabled()) {
    std::chrono::duration<double, std::ratio<1>> t_elapsed = std::chrono::high_resolution_clock::now() - time_start_;
    if (t_elapsed > period_) {
      double average_rate = count_ / t_elapsed.count();
      fmt::print("Average rate: {} Hz\n", average_rate);
      count_ = 0;
      time_start_ = std::chrono::high_resolution_clock::now();
    }
    ++count_;
  }
}
 
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

int VerifyRead(char* buf, int len, uint8_t msg_id) {
  int start_index;
  uint8_t byte;
  for (start_index = 0; start_index < len; ++start_index) {
    byte = buf[start_index];
    if (byte == msg_id) {
      break;
    }
  }
  if (start_index > 0) {
    fmt::print("Not at begining of message, Trying to fix.\n");
    int received_length = len - start_index;

    // Shift the data over to the start of the buffer
    for (int i = 0; i < received_length; ++i) {
      buf[i] = buf[i + start_index];
    }
  }
  return start_index;
}
 
} // namespace rexlab
