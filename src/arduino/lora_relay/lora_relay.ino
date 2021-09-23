#include <SPI.h>
#include <LoRa.h>

#include "Pose.hpp"
#include "receiver.hpp"

#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3
#define RF95_FREQ 915.0
#define LED_PIN 13
#define MSG_SIZE 24

int counter = 0;
int time_start = 0;
int count = 0;
char buf[MSG_SIZE];

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

void setup() {
  pinMode(LED_PIN, OUTPUT);
  
  Serial.begin(57600);
  while (!Serial);

  Serial.println("LoRa Sender");
  LoRa.setPins(RFM95_CS, RFM95_RST, RFM95_INT);

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  } 
  LoRa.setSpreadingFactor(6);
  LoRa.setSignalBandwidth(500E3);


  for (int i = 0; i < MSG_SIZE; ++i) {
    buf[i] = i;
  }

  time_start = micros();
  digitalWrite(LED_PIN, LOW);
}

void send_buf() {
  LoRa.beginPacket(true);
  LoRa.write((uint8_t*)buf, MSG_SIZE);
  LoRa.endPacket();
}

void loop() {
  if (Serial.available() >= MSG_SIZE) {
    digitalWrite(LED_PIN, HIGH);
    Serial.readBytes(buf, MSG_SIZE); 
    send_buf();
  }
//  send_buf();
//  print_rate();
}
