#include <SPI.h>
#include <LoRa.h>

#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3
#define RF95_FREQ 915.0
#define LED_PIN 13
#define MSG_SIZE 20

int counter = 0;
int time_start = 0;
int count = 0;
uint8_t buf[MSG_SIZE];

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
    // received a packet
//    Serial.print("Received packet '");

    // read packet
//    while (LoRa.available()) {
//      Serial.print((char)LoRa.read());
//    }
    LoRa.readBytes(buf, MSG_SIZE);
//    for (int i = 0; i < 7; ++i) {
//      Serial.print(buf[i]);
//    }

    // print RSSI of packet
//    Serial.print("' with RSSI ");
//    Serial.println(LoRa.packetRssi());
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
  LoRa.receive(7);

}

void example_original() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}

void loop() {

}
