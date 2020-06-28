#include "DHT.h"
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define DHT11_PIN 7

#define FIREBASE_HOST "your-project.firebaseio.com"                          // the project name address from firebase id
#define FIREBASE_AUTH "Uejx9ROxxxxxxxxxxxxxxxxxxxxxxxxfQDDkhN"            // the secret key generated from firebase

#define Name_Wifi ""
#define Pass_Wifi ""

const int DHTTYPE = DHT11;
//Declare the Firebase Data object in the global scope
FirebaseData firebaseData;

DHT dht(DHT11_PIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  connectWifi();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase
  dht.begin();
}

void loop() {
  showTempHumid();
}

void showTempHumid() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  String fireHumid = String(h) + String("%");
  String fireTemp = String(t) + String("Â°C");         

  if (Firebase.setString(firebaseData, "/DHT11/Temperature", fireTemp)) {
     Serial.print("Temperature = ");
     Serial.println(t);
  }
  else {
    Serial.println("Error writing temperature firebase server.");
  }

  if (Firebase.setString(firebaseData, "/DHT11/Humidity", fireHumid)){
    Serial.print("Relative Hudmity = ");
    Serial.println(h);
  }
  else {
     Serial.println("Error writing humidity firebase server.");
  }
  
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
