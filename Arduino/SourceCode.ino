#include <ESP8266.h>
#include "DHT.h"

#define DHT11_PIN 7

#include "SoftwareSerial.h"
SoftwareSerial  ConsoleOut(8, 9);

#define SSID  "Name_Wifi"
#define PWD   "PASSWORD"
const int DHTTYPE = DHT11;

DHT dht(DHT11_PIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();

 char *ipAddress, ap[31];

  WiFi.reset(WIFI_RESET_HARD);
  WiFi.begin(9600);
  if (WiFi.join(SSID, PWD) == WIFI_ERR_OK) {
    ipAddress = WiFi.ip(WIFI_MODE_STA);
    ConsoleOut.print(F("\n\rIP address:"));
    ConsoleOut.print(ipAddress);
    ConsoleOut.print(':');
    if (WiFi.isConnect(ap))
      ConsoleOut.println(ap);
    else
      ConsoleOut.println(F("not found"));
  } else
    while (1);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Temperature = ");
  Serial.println(dht.readTemperature());
  Serial.print("Relative Hudmity = ");
  Serial.println(dht.readHumidity());
  delay(2000);
}
