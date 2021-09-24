#include <SPI.h>
#include <LoRa.h>

#include "Pose.hpp"
#include "receiver.hpp"

using Pose = rexlab::Pose<int16_t>;

#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3
#define RF95_FREQ 915.0
#define LED_PIN 13
#define MSG_SIZE 24

/**
 * @brief Prints a message at a given rate
 * 
 * # Usage
 * Initialize the printer as a global variable (one for each rate-limited message you want to send).
 * Call the `print` or `println` methods as you would. Note that right now you can't string multiple
 * print statements back-to-back.
 */
class PrintAtRate {
  public:
    PrintAtRate(float rate) 
        : delay_ms_(static_cast<int>(1000.0 / rate)), 
          timestamp_last_print_ms_(-delay_ms_) {}  
    void print(const std::string& msg) {
      int time_since_last_print_ms = millis() - timestamp_last_print_ms_;
      if (time_since_last_print_ms > delay_ms_) {
        Serial.print(msg.c_str());
        timestamp_last_print_ms_ = millis();
      }
    }
    void println(const std::string& msg) {
      int time_since_last_print_ms = millis() - timestamp_last_print_ms_;
      if (time_since_last_print_ms > delay_ms_) {
        Serial.println(msg.c_str());
        timestamp_last_print_ms_ = millis();
      }
    }
    
  private:
    int delay_ms_;
    int timestamp_last_print_ms_;  
};


// Global variables
bool has_sent = false;
int time_start = 0;
int count = 0;
char buf[MSG_SIZE];
bool is_stale = true;
int seconds_to_stale = 5;
int timestamp_last_receive_ms = 2 * seconds_to_stale * 1000; // starts as stale

// Initialize objects
PrintAtRate stale_printer(1.0);
PrintAtRate sending_printer(1.0 / 10.0);  // print a status every 10 seconds
rexlab::SerialReceiver<Serial_> receiver(Serial, Pose::MsgID());

/**
 * @brief Prints the rate at which this method is called
 */
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
  while (!Serial) { delay(10); }

  LoRa.setPins(RFM95_CS, RFM95_RST, RFM95_INT);

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  } 
  LoRa.setSpreadingFactor(6);
  LoRa.setSignalBandwidth(500E3);

  time_start = micros();
  digitalWrite(LED_PIN, LOW);
}

/**
 * Send the data over the LoRa radio
 */
void send_buf() {
  LoRa.beginPacket(true);
  LoRa.write((uint8_t*)buf, MSG_SIZE);
  LoRa.endPacket();
}

void loop() {
  // Receive data from the serial port
  bool did_receive = receiver.Receive(buf, MSG_SIZE);
  if (did_receive) {
    // Relay the data over LoRa radio
    send_buf();

    // Status bookkeeping
    sending_printer.println("LoRa is sending data");
    if (is_stale) {
      Serial.println("LoRa radio has started transmissions");
      is_stale = false;
    }
    timestamp_last_receive_ms = millis();
  } else {
    // Check if the process is stale (hasn't received data for a while)
    int time_since_last_receive_ms = millis() - timestamp_last_receive_ms;
    if (is_stale) {
      stale_printer.println("LoRa process is stale.");
    } else {
      if (time_since_last_receive_ms > seconds_to_stale * 1000) {
        is_stale = true;
      }
    }
  }
}
