#include <SPI.h>
#include <LoRa.h>

#include "Pose.hpp"
#include "Pose_utils.hpp"

#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3
#define RF95_FREQ 915.0
#define LED_PIN 13

int counter = 0;
int time_start = 0;
int count = 0;

constexpr int MSG_SIZE = sizeof(rexlab::Pose<int16_t>);
rexlab::Pose<int16_t> msg;
rexlab::Pose<float> pose;
uint8_t* buf = reinterpret_cast<uint8_t*>(&msg);


void print_rate() {
  count++;
  if (count == 100) {
    float time_s = (micros() - time_start) / 1e6;
    Serial.print("Average rate: ");
    Serial.println(count / time_s);
    time_start = micros();
    count = 0;
  }
}

void onReceive(int packetSize) {
  if (packetSize) {
    LoRa.readBytes(buf, MSG_SIZE);
    rexlab::ConvertPoseIntToFloat(msg, &pose);
    PrintPose(pose);
    print_rate();
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");
  LoRa.setPins(RFM95_CS, RFM95_RST, RFM95_INT);

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(6);
  LoRa.setSignalBandwidth(500E3);

  time_start = micros();
  
  LoRa.onReceive(onReceive);
  LoRa.receive(MSG_SIZE);

}

void loop() {

}
