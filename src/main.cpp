#include <Arduino.h>
#include <SoftwareSerial.h>
#include <BluetoothSerial.h>

static const int RXPin PROGMEM = 16, TXPin = 17;//geek dongl 43,44 tx,rx // esp32wroom 16,17
static const uint32_t GPSBaud PROGMEM = 9600;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
String device_name PROGMEM = "ESP32-BT-Slave";//bluetooth devicename
// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled!
#endif
// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available.
#endif
BluetoothSerial SerialBT;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ss.begin(GPSBaud);
  SerialBT.begin(device_name);
}

void loop() {
  if (ss.available()) {
  SerialBT.write(ss.read());
  Serial.write(ss.read());
  }
  delay(5);  // give CPU some idle time
  if (SerialBT.available()) {
    ss.write(SerialBT.read());
    Serial.write(SerialBT.read());
  }
}
// put function definitions here:
