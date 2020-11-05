#include <Servo.h>
// include the library
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
SoftwareSerial espSerial(0, 1); //Tx, Rx of nodemcu
String str;
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7; //rs = 9 , 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Servo myservo;
bool opened = 0;
int led = 0;
int length_bin = 20;  // in cm
int fill_percent = 0;
int pos = 0;
int trig_open=2; // ultrasonic to open the lid
int echo_open=3;
int trig_fill=11; // ultrasonic for fill status of bin
int echo_fill=12;
float duration_open;
float distance_open;
float duration_fill;
float distance_fill;

void setup() {
lcd.begin(16, 2);
Serial.begin(115200);
espSerial.begin(115200);
myservo.attach(13); // pin servo = 13 in arduino

pinMode(trig_open, OUTPUT);
pinMode(echo_open, INPUT);
pinMode(led, OUTPUT);
pinMode(trig_fill, OUTPUT);
pinMode(echo_fill, INPUT);
 delay(2000);
}

void loop(){
  ultra_open();
  ultra_fill(); 
  fill_percent = ((length_bin - distance_fill)/length_bin)*100;
  
  if(fill_percent < 90){
    digitalWrite(led, HIGH); //green led glows.
  if(distance_open < 20){ //20cm-> can set accordingly how close the person need to be to dustbin to open-close the lid.
  //  myservo.write(100); 
//delay(5000);// can chance the amount of angle the lid opens, can change accordingly. between(0 to 180).
    if(opened == 1){
      myservo.write(150);
      }else{
    lid_open();
//myservo.write(120);
delay(3000);}
  }
  else{
  //myservo.write(0); 
  if(opened == 0){
    myservo.write(0);

}else{
lid_close();
  }
  }
  
  // to display on serial monitor
  Serial.print("Bin ");
  Serial.print(fill_percent);
  Serial.println("% Fill.");

// display on lcd
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(String("#1- "));
  lcd.setCursor(0, 1);
  lcd.print(fill_percent);}
//  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
   else{
    //myservo.write(0);
    digitalWrite(led, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
  lcd.print(String("#1- "));
  lcd.setCursor(0, 1);
  lcd.print(String("DustBin is Full."));
    }
 // lcd.print(millis() / 1000);
 str =String("coming from arduino: ")+String(fill_percent);
espSerial.println(str);
delay(1000);
}

void ultra_open(){
          // Clears the trigPin
digitalWrite(trig_open, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trig_open, HIGH);
delayMicroseconds(10);
digitalWrite(trig_open, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration_open = pulseIn(echo_open, HIGH);
// Calculating the distance
distance_open= duration_open*0.034/2;
// Prints the distance on the Serial Monitor

Serial.print("Distance to dustbin(distance_open): ");
Serial.println(distance_open);

}

void ultra_fill(){
          // Clears the trigPin
digitalWrite(trig_fill, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trig_fill, HIGH);
delayMicroseconds(10);
digitalWrite(trig_fill, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration_fill = pulseIn(echo_fill, HIGH);
// Calculating the distance
distance_fill= duration_fill*0.034/2;
// Prints the distance on the Serial Monitor

Serial.print("Distance to fill(distance_fill): ");
Serial.println(distance_fill);

}

void lid_open(){
  //to open lid
  
   for (pos = 0; pos <= 150; pos += 1) { // goes from 0 degrees to 180 degrees
  
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
    }                      // waits 15ms for the servo to reach the position
   
 opened =1;
}

void lid_close(){
 //to close lid

  for (pos = 150; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
 opened = 0;
}
