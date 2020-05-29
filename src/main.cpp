#include <TTN_esp32.h>
#include "heltec.h"
#include "config.h"
#include "main.h"

TTN_esp32 ttn;

void loop() {
  // Read voltage and add as uint8 to transmission
  float voltage = readVoltage();
  uint8_t payload = (uint8_t)(int)(voltage * 10);

  if (ENABLE_SEND) {
    sendVoltage(payload);
  } else {
    // Sending is disabled, display value and give a moment to read
    Heltec.display->drawString(0, 22, "Current Voltage: " + String((float)payload / 10) + "V");
    Heltec.display->display();
    delay(1000);
  }

  if (voltage >= BATTERY_LOAD_VOLTAGE || DISABLE_SLEEP) {
    // We're getting power from the charger, no need to deep sleep.
    // Just wait for a moment to do the next measurement which will
    // allow us to receive a measurement shortly after car shuts down.
    delay(CHARGE_SLEEP_MS);
  } else {
    // We're running on battery and should preserve as much power
    // as possible, so we power down and ask in a few minutes again.
    esp_sleep_enable_timer_wakeup(BATTERY_SLEEP_US);
    esp_deep_sleep_start();
  }
}

float readVoltage() {
  Serial.println("Reading voltage...");

  int rawSum = 0;
  for (int i = 0; i < MEAS_COUNT; i++) {
    rawSum += analogRead(PIN_VOLTAGE_READ);
    delay(MEAS_WAIT_MS);
  }

  float raw = rawSum / float(MEAS_COUNT);
  float vout = raw * 3.3 / 4094.0;
  float value = vout / (7500.0 / (30000.0 + 7500.0)) + CORRECT_DIFF;

  Serial.printf("Voltage read: %.1f %.2f\r\n", raw, value);
  return value;
}

void sendVoltage(uint8_t payload) {
  // Make sure any pending transactions are handled first
  ttn.waitForPendingTransactions();

  Heltec.display->clear();
  // Transmit voltage and display it until deep-sleep
  if (ttn.sendBytes(&payload, sizeof(payload))) {
    Heltec.display->drawString(0, 22, "Current Voltage: " + String((float)payload / 10) + "V");
  }
  Heltec.display->display();

  // Make sure our transactions is handled before going to sleep
  ttn.waitForPendingTransactions();
}

void setup() {
  Heltec.begin(true /* DisplayEnable */, false /* LoRaEnable */, true /* SerialEnable */, false /* PABOOST */, BAND /* long BAND */);

  analogReadResolution(12);

  // Initialize display for usage
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->clear();

  // Join TTN and reset counters
  Serial.println("Starting TTN");
  ttn.begin();
  ttn.join(devEui, appEui, appKey);

  // Wait for join to be completed
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "Joining TTN:");
  Heltec.display->display();
  int x = 60;
  while (!ttn.isJoined()) {
    Heltec.display->drawString(x, 0, ".");
    Heltec.display->display();
    delay(250);
    x++;
  }
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "TTN Connection online...");
  Heltec.display->display();

  // Add connection info
  Serial.println("Setup done");
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "TTN Connection online...");
}
