#include "receiver.hpp"

struct ViconMsg {
  static constexpr uint8_t MsgID() { return 11; }
  uint8_t msgid = MsgID();
  bool is_occluded = false;
  uint16_t position_scale = 10000;
  int position_x;
  int position_y;
  int position_z;
  int quaternion_w;
  int quaternion_x;
  int quaterioon_y;
  int quaternion_z;
};

// Global Parameters
float rate_print_frequency = 1.0;  // frequency at which to print the averaged rate
constexpr HardwareSerial& HolybroRadio = Serial5;

// Global Variables
constexpr int BUFLEN = sizeof(ViconMsg);
ViconMsg msg;
char* buf = reinterpret_cast<char*>(&msg);
int x_prev = -1;
rexlab::SerialReceiver receiver(HolybroRadio, ViconMsg::MsgID());

// Setup
void setup() {
  receiver.Init();
  receiver.EnableRatePrinting(rate_print_frequency);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  HolybroRadio.begin(57600);
  if (!HolybroRadio) {;}
}

// the loop function runs over and over again forever
void loop() {
  bool msg_received = receiver.Receive(buf, BUFLEN);
  if (msg_received) {
    if (msg.position_x - x_prev > 1) {
      Serial.print("Dropped message!!!\n");
    }
    x_prev = msg.position_x;
  }
}
