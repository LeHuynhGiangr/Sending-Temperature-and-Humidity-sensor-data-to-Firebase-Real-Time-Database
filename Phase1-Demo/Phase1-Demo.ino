#include <ESP8266WiFi.h>                                                    // esp8266 library
#include <FirebaseArduino.h>
//#include "FirebaseESP8266.h"                                               // firebase library
#include <DHT.h>

//NTP base on UDP, UDP is connectionless Internet protocol
#include <WiFiUdp.h>

//library timestamp
#include <NTPClient.h>

#define FIREBASE_HOST "finalproject1-f2c29.firebaseio.com"                          // the project name address from firebase id
#define FIREBASE_AUTH "sy0ghotP4FpaakCXTKYxU9adCzQqBuPCcjdirzyT"            // the secret key generated from firebase

//#define FIREBASE_HOST "cloud-329c7.firebaseio.com"                          // the project name address from firebase id
//#define FIREBASE_AUTH "K5YK2ZAvk93DmcQ2QSPMAiKhqOKcXIuyssN266AH"            // the secret key generated from firebase

#define NTPServerName "time.google.com"

#define WIFI_SSID "BaoAnh2.4G"                                             // input your home or public wifi name 
#define WIFI_PASSWORD "18051999"                                    //password of wifi ssid
 
#define DHTPIN D4                                                           // what digital pin we're connected to
#define DHTTYPE DHT22                                                       // select dht type as DHT 11 or DHT22




DHT dht(DHTPIN, DHTTYPE);

WiFiUDP udp;       //an instance of udp
NTPClient timeClient(udp, "time.google.com");

String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
                                                 

void setup() {
  Serial.begin(9600);
  delay(1000);                
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase

  Serial.println("Successfully connected to Firebase");

  timeClient.begin();

  //set time difference (seconds)
  timeClient.setTimeOffset(3600*7);//Time at VN is GMT +7 hour
  
  dht.begin();                                                               //Start reading dht sensor
}

void loop() { 
  float h = dht.readHumidity();                                              // Reading temperature or humidity takes about 250 milliseconds!
  float t = dht.readTemperature();                                           // Read temperature as Celsius (the default)
    
  if (isnan(h) || isnan(t)) {                                                // Check if any reads failed and exit early (to try again).
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  //get humidity and temperature
  String fireHumid = String(h) + String("%");   //convert integer humidity to string humidity 
  String fireTemp = String(t) + String("Â°C");  //convert integer temperature to string temperature

  //Get datetime
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  String formattedTime = timeClient.getFormattedTime(); 
  struct tm *ptm = gmtime ((time_t *)&epochTime);//Get a time structure
  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon+1; 
  int currentYear = ptm->tm_year+1900;  
  String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
  
  //Print complete datetime:
  String timeStamp= currentDate + "" + formattedTime;  //********************
  
  String pathTemp =String("/Temperature/")+timeStamp;  //*********************
  String pathHumidity =String("/Humidity/")+timeStamp;  //*********************
   
  Firebase.set(pathTemp, h);
  Firebase.set(pathTemp, h);
  
  delay(4000); 
}
