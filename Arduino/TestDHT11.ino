#include "DHT.h"
#define DHT11_PIN 7

const int DHTTYPE = DHT11;

DHT dht(DHT11_PIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.print("Temperature = ");
  Serial.println(t);
  Serial.print("Relative Hudmity = ");
  Serial.println(h);
  delay(2000);
}
