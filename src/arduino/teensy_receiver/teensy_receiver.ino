#include "receiver.hpp"
#include "pose.hpp"

#include "limits"

using ViconMsg = rexlab::Pose<int32_t>;
using Pose = rexlab::Pose<float>;

// Global Parameters
float rate_print_frequency = 1.0;  // frequency at which to print the averaged rate
constexpr HardwareSerial& HolybroRadio = Serial5;

// Global Variables
constexpr int BUFLEN = sizeof(ViconMsg);
ViconMsg msg;
Pose pose;
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
int count = 0;
void loop() {
  bool msg_received = receiver.Receive(buf, BUFLEN);
  pose = rexlab::ConvertPoseIntToFloat<float>(msg);
  int Tmax = std::numeric_limits<int32_t>::max();
//  Serial.print((float)msg.position_z / (float)Tmax);
  if (count == 10) {
    Serial.print(pose.position_z);
    Serial.print("\n");
    count = 0;
  }
  ++count;
}
