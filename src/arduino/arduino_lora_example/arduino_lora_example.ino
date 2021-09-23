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

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");
  LoRa.setPins(RFM95_CS, RFM95_RST, RFM95_INT);

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  } 
  LoRa.setSpreadingFactor(6);
  LoRa.setSignalBandwidth(500E3);
//  LoRa.setTxPower(20, PA_OUTPUT_PA_BOOST_PIN);
//  LoRa.enableCrc();
//  LoRa.setPreambleLength(6);

  for (int i = 0; i < MSG_SIZE; ++i) {
    buf[i] = i;
  }

  time_start = micros();
}

void example_original() {
//  Serial.print("Sending packet: ");
//  Serial.println(counter);

  // send packet
  LoRa.beginPacket(true);
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;
  if (counter > 9) {
    counter = 0;
  }
  delay(1);
}

void send_buf() {
  LoRa.beginPacket(true);
  LoRa.write(buf, MSG_SIZE);
  LoRa.endPacket();
}


void loop() {
//  example_original();
  send_buf();
//  Serial.print("Sending packet: ");
//  Serial.println(counter);

  // send packet
//  LoRa.beginPacket();


//  LoRa.beginPacket(true);
//  LoRa.write(buf, 30);
//  LoRa.print(counter);
//  LoRa.endPacket();
  
  print_rate();

  
}
