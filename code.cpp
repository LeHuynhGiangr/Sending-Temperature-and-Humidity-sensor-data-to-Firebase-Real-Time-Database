#include <ESP8266WiFi.h>


#define Name_Wifi "CTY VT LE HUYNH"
#define Pass_Wifi "12011999"

/*
 * author: Le Huynh Giang
 */
void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600); //9600 bps
	connectWifi();
}

void loop() {
	// put your main code here, to run repeatedly:

}

//connecting to wifi
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
