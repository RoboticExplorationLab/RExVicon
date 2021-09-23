#include <cstdint>

#include <Arduino.h>

namespace rexlab {

// TODO: avoid the duplicate code here and in utils.hpp (need to link Arduino and CMake build)
/**
 * @brief Make sure the message starts with the byte `msg_id`.
 * 
 * If the message does not start with a byte matching `msg_id`, find the byte with
 * `msg_id`, shift the data, and report how many extra bytes need to be read to 
 * complete the message.
 * 
 * TODO: Handle the case when the message ID is not found at all.
 * 
 * @param buf Data buffer
 * @param len Length of data buffer
 * @param msg_id Expected first byte
 * @return int Number of extra bytes to read. If 0, the message is valid.
 */
int VerifyRead(char* buf, int len, uint8_t msg_id);

/**
 * @brief A class for receiving a fixed-size message over serial for Arduinos
 * 
 * This class implements a moderately robust and efficient receive method for receiving
 * serial data over Arduino serial ports. Each message must be a fixed sized and must start
 * with the same byte (a message ID) each time. The message ID is used to make sure the 
 * serial reads start at the correct location, and allows the receiver to automatically
 * compensate if the read results in the first byte not being equal to the expected message
 * ID.
 * 
 * The class also allows for the rate of the receive to be printed to the default serial 
 * port for debugging.
 * 
 * TODO: Allow for a callback to handle the rate information (e.g. saving to a file, 
 * storing in a message to be sent over another serial port, etc.)
 * 
 * # Usage
 * The usage of this class is very simple. This example assumes we've define a type `MsgMsg`
 * that defines the data stored in our message. This is purely for convenience and is not
 * required to use this class, but is recommended since it provides interpretability to 
 * the data being received.
 * 
 * ```cpp
 * // Select the desired Arduino serial port
 * constexpr HardwareSerial& RecievePort = Serial1;
 * 
 * // Set the message ID and allocate the buffer from a pre-defined message struct `MyMsg`
 * MyMsg msg;
 * constexpr uint8_t kMsgID = MyMsg::MsgID();
 * constexpr int kBufLen = sizeof(MyMsg);
 * char* buf = reinterpret_cast<char*>(&msg);
 * 
 * // Initialize the class as a global variable with the serial port and the message ID
 * rexlab::SerialReceiver receiver(ReceivePort, kMsgID);
 * 
 * // Call the Init function in the setup
 * void setup() {
 *   receiver.Init();
 * 
 *   // Optional: enable rate printing
 *   float rate_print_frequency = 1; // Hz
 *   receiver.EnableRatePrinting(rate_print_frequency);
 *  }
 * 
 * // Call the Receive method during the loop
 * bool msg_received = receiver.Receive(buf, BUFLEN);
 * ```
 * 
 * TODO: Handle the case when the message ID is not found at all in the data being read.
 */
template <class SerialPort>
class SerialReceiver {
 public:
  explicit SerialReceiver(SerialPort& serial_port, uint8_t msg_id) 
      : serial_port_(serial_port), msg_id_(msg_id) {}
  void Init() {
    if (enable_rate_print_) {
      time_start_us_ = micros();
    }
  }

  void EnableRatePrinting(float rate_print_frequency) {
    rate_print_period_us_ = static_cast<uint32_t>(1e6 / rate_print_frequency);
    enable_rate_print_ = true;
  }

  bool Receive(char* buf, int len) {
    if (serial_port_.available() >= len) {
      int bytes_received = serial_port_.readBytes(buf, len);
      if (bytes_received) {
        int extra_bytes = VerifyRead(buf, len, msg_id_);
        serial_port_.readBytes(buf + len - extra_bytes - 1, extra_bytes);
        ++receive_count_;
      } else {
        Serial.print("Serial read timed out\n");
      }
      if (enable_rate_print_) {
        uint32_t time_elapsed_us = micros() - time_start_us_;
        if (time_elapsed_us > rate_print_period_us_) {
          float time_s = time_elapsed_us / 1e6;
          float average_rate = receive_count_ / time_s;
          Serial.print("Average rate: ");
          Serial.print(average_rate);
          Serial.print(" Hz\n");
          receive_count_ = 0;
          time_start_us_ = micros();
        }
      }
      return static_cast<bool>(bytes_received);
    }
    return false; 
  }

 private:
  SerialPort& serial_port_;
  uint8_t msg_id_;
  int receive_count_;
  bool enable_rate_print_ = false;
  uint32_t rate_print_period_us_ = 0;
  uint32_t time_start_us_ = 0;
};


}  // namespace rexlab