#include "DHT.h"
#define DHT11_PIN 7

#include <ESP8266WiFi.h>

#define Name_Wifi ""
#define Pass_Wifi ""

const int DHTTYPE = DHT11;

DHT dht(DHT11_PIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  connectWifi();
  dht.begin();
}

void loop() {
  showTempHumid();
}

void showTempHumid() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.print("Temperature = ");
  Serial.println(t);
  Serial.print("Relative Hudmity = ");
  Serial.println(h);
  delay(2000);
}

void connectWifi() {
  Serial.println("wait until wifi connected");
  WiFi.begin(Name_Wifi, Pass_Wifi);//connection to Wifi is initiailized
  while (WiFi.status() != WL_CONNECTED) {//try to connect untill success
    delay(500);
    Serial.print(".");
  }
  //some info
  Serial.println("");
  Serial.print("Successfully connected to wifi ,");
  Serial.println(WiFi.localIP());
}
