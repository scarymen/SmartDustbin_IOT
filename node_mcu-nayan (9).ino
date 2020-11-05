#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#define BLYNK_PRINT Serial
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "****************************";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "*************";
char pass[] = "*************";

SimpleTimer timer;
String fillper;
void sendSensor(){

  Blynk.virtualWrite(V5, fillper);
  //Blynk.virtualWrite(V6, t);

  // SETUP the ALARM Trigger and Send EMAIL 
  // and PUSH Notification

  if(fillper > 90){
    Blynk.email("nayan@gmail.com", "ESP8266 Alert", "Bin over 90 %");
    Blynk.notify("ESP8266 Alert - Bin over 90 %");
  }
}

void setup() {
// Open serial communications and wait for port to open:
Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
 timer.setInterval(2500L, sendSensor);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
}
void loop() { // run over and over
if (Serial.available()) {
   fillper = String(Serial.read());
   
//Serial.write(Serial.read());
}
if(fillper > 90){
 Blynk.run();
 }
 //sendSensor();
  timer.run();
}
