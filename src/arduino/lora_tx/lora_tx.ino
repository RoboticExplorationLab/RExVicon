#include <cstdint>

#include <SPI.h>
#include <RH_RF95.h>

#include "Pose.hpp"
#include "receiver.hpp"

#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3
#define RF95_FREQ 915.0
#define LED_PIN 13
#define RATE_PRINT_FREQ 1  // Hz
#define ComputerPort Serial

// Store Pose message
rexlab::Pose<float> pose_msg;
char* buf = reinterpret_cast<char*>(&pose_msg);
constexpr int POSE_LEN = sizeof(rexlab::Pose<float>);

// Pose receiver class
rexlab::SerialReceiver<Serial_> receiver(ComputerPort, rexlab::Pose<float>::MsgID());

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

int t_start;

void setup() {
  // Set up serial receive from computer
  receiver.Init();
  receiver.EnableRatePrinting(RATE_PRINT_FREQ);
  
  ComputerPort.begin(115200);
  while (!ComputerPort) {
    delay(1);
  }
  delay(100);
  
  // Set up pins
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  // Reset LoRa
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    Serial.println("Uncomment '#define SERIAL_DEBUG' in RH_RF95.cpp for detailed debug info");
    while (1);
  }
  Serial.println("LoRa radio init OK!");

  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
  
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);

  rf95.setModeTx();
//  rf95.setPreambleLength(2);

  RH_RF95::ModemConfig modem_config = {0x92, 0x64, 0x00};
  rf95.setModemRegisters(&modem_config);

  t_start = micros();
}

int16_t packetnum = 0;  // packet counter, we increment per xmission

void loop() {
  // Receive pose message from computer
//  bool msg_received = receiver.Receive(buf, POSE_LEN);
  bool msg_received = true;
  if (msg_received) {
      digitalWrite(LED_PIN, HIGH);
      uint8_t buf2[36];
//      rf95.send(buf2, 36);
      packetnum++;
      pose_msg.position_x = packetnum;
      rf95.send((uint8_t*)pose_msg.GetData(), pose_msg.NumBytes());
      rf95.waitPacketSent();
//      digitalWrite(LED_PIN, LOW);
  }
  if (packetnum == 100) {
    float t_elapsed_s = (micros() - t_start) / 1e6;
    t_start = micros();
    Serial.print("Average rate: ");
    Serial.println(packetnum / t_elapsed_s);
    packetnum = 0;
  }
//
//  delay(1000); // Wait 1 second between transmits, could also 'sleep' here!
//  Serial.println("Transmitting..."); // Send a message to rf95_server
//  
//  char radiopacket[20] = "Hello World #      ";
//  itoa(packetnum++, radiopacket+13, 10);
//  Serial.print("Sending "); Serial.println(radiopacket);
//  radiopacket[19] = 0;
//  
//  Serial.println("Sending...");
//  delay(10);
//  digitalWrite(LED_PIN, HIGH);
//  rf95.send((uint8_t *)radiopacket, 20);
//
//  Serial.println("Waiting for packet to complete..."); 
//  delay(10);
//  rf95.waitPacketSent();
//  digitalWrite(LED_PIN, LOW);
}
