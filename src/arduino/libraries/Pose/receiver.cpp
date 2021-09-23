#include "receiver.hpp"

namespace rexlab {

int VerifyRead(char* buf, int len, uint8_t msg_id) {
  // Search for start of the message
  int start_index;
  uint8_t byte;
  for (start_index = 0; start_index < len; ++start_index) {
    byte  = buf[start_index];
    if (byte == msg_id) {
      break;
    }
  }

  if (start_index > 0) {
    // How many bytes of the message did we receive?
    int received_length = len - start_index;  

    // Shift the data over to the start of the buffer
    for (int i = 0; i < received_length; ++i) {
      buf[i] = buf[i + start_index];
    }
  }
  return start_index;
}
  
}  // namespace rexlab
