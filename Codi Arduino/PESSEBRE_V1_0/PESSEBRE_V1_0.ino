const int sortida_1 = 22;
const int sortida_2 = 23;
const int sortida_3 = 24;
const int sortida_4 = 25;
const int sortida_5 = 26;
const int sortida_6 = 27;
const int sortida_7 = 28;
const int sortida_8 = 29;
const int sortida_9 = 30;
const int sortida_10 = 31;
const int sortida_11 = 32;
const int sortida_12 = 33;
const int sortida_13 = 34;
const int sortida_14 = 35;
const int sortida_15 = 36;
const int sortida_16 = 37;
#include <Wire.h>
#include <RTClib.h>
RTC_DS1307 RTC;

char val;
void setup(){
  RTC.begin();
RTC.adjust(DateTime(__DATE__,__TIME__));

  Serial.begin(9600);
pinMode(sortida_1,OUTPUT);
pinMode(sortida_2,OUTPUT);
pinMode(sortida_3,OUTPUT);
pinMode(sortida_4,OUTPUT);
pinMode(sortida_5,OUTPUT);
pinMode(sortida_6,OUTPUT);
pinMode(sortida_7,OUTPUT);
pinMode(sortida_8,OUTPUT);
pinMode(sortida_9,OUTPUT);
pinMode(sortida_10,OUTPUT);
pinMode(sortida_11,OUTPUT);
pinMode(sortida_12,OUTPUT);
pinMode(sortida_13,OUTPUT);
pinMode(sortida_14,OUTPUT);
pinMode(sortida_15,OUTPUT);
pinMode(sortida_16,OUTPUT);
}

void loop(){
DateTime now = RTC.now();
 
  ho = (now.hour());
  mi = (now.minute());
  
  if ((ho == 21) && (mi == 12)) {
  digitalWrite(sortida_1,HIGH);
  }
  if ((ho == 21) && (mi == 11)) {
  digitalWrite(sortida_1,LOW);
  }
if( Serial.available() >0 ) {
    val = Serial.read();
    Serial.println(val); 
}
//Relay is on
  if( val == '1' ) {
    digitalWrite(sortida_13,LOW); }
  else if( val == '2' ) {
    digitalWrite(sortida_14,LOW); }
  else if( val == '3' ) {
    digitalWrite(sortida_15,LOW); }
  else if( val == '4' ) {
    digitalWrite(sortida_16,LOW); }
  //relay all on
  else if( val == '9' ) {
    digitalWrite(sortida_13,LOW);
    digitalWrite(sortida_14,LOW);
    digitalWrite(sortida_15,LOW);
    digitalWrite(sortida_16,LOW);
 }
 //relay is off
  else if( val == 'A' ) {
    digitalWrite(sortida_13,HIGH); }
  else if( val == 'B' ) {
    digitalWrite(sortida_14,HIGH); }
  else if( val == 'C' ) {
    digitalWrite(sortida_15,HIGH); }
  else if( val == 'D' ) {
    digitalWrite(sortida_16,HIGH); }
  //relay all off  
  else if( val == 'I' ) {
    digitalWrite(sortida_13,HIGH);
    digitalWrite(sortida_14,HIGH);
    digitalWrite(sortida_15,HIGH);
    digitalWrite(sortida_16,HIGH);
 }
 
}


