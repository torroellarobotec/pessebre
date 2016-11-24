//PESSEBRE V1.1 BY BBJ SOLUTIONS & ROBOT-EC
//reles 230Vac
const int rele1 = 9;
const int rele2 = 8;
const int rele3 = 7;
const int rele4 = 6;
const int rele5 = 5;
const int rele6 = 4;
const int rele7 = 3;
const int rele8 = 2;
//reles 12Vdc
const int rele9 = 39;
const int rele10 = 41;
const int rele11= 43;
const int rele12 = 45;
const int rele13 = 47;
const int rele14 = 49;
//reles lliures de potencial
const int rele15 = 51;
const int rele16 = 53;

//sensor de presencia
const int sensor_moviment = 13;
int mi,ho,se;
char val;
//declarar llibreries wire, rtc i i2c
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;

void setup(){
Serial.begin(9600);
//RTC llegir hora rellotge pc i sincronitzarla al rtc
 Wire.begin();
    RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
////////////////////////
//reles230Vac
pinMode(rele1,OUTPUT);
pinMode(rele2,OUTPUT);
pinMode(rele3,OUTPUT);
pinMode(rele4,OUTPUT);
pinMode(rele5,OUTPUT);
pinMode(rele6,OUTPUT);
pinMode(rele7,OUTPUT);
pinMode(rele8,OUTPUT);
//reles12Vac
pinMode(rele9,OUTPUT);
pinMode(rele10,OUTPUT);
pinMode(rele11,OUTPUT);
pinMode(rele12,OUTPUT);
pinMode(rele13,OUTPUT);
pinMode(rele14,OUTPUT);
//reles lliures de potencia
pinMode(rele15,OUTPUT);
pinMode(rele16,OUTPUT);
//mode funcionament
mi=0;
ho=0;
se=0;
//sensor de presencia
pinMode(sensor_moviment,INPUT);
/*
digitalWrite(rele1,HIGH);//Bomba moli + Gir Moli +Led Moli
digitalWrite(rele2,HIGH);//Moli canto cova
digitalWrite(rele3,HIGH);//Boira
digitalWrite(rele4,HIGH);//Llum llac
digitalWrite(rele5,HIGH);//relé que no clava (NU)
digitalWrite(rele6,HIGH);//On/Off Màquina de fum
digitalWrite(rele7,HIGH);//Infern + bomba de recirculació riu + foc + llamp + 3 bombetes vermelles
digitalWrite(rele8,HIGH);//Cel
digitalWrite(rele9,HIGH);//Dimmer
digitalWrite(rele10,HIGH);//Polsador contacte Màquina de fum
digitalWrite(rele11,HIGH);//Naixement + sol + lluna
digitalWrite(rele12,HIGH);//poble 3
digitalWrite(rele13,HIGH);//masia + castell banderes
digitalWrite(rele14,HIGH);//poble 4 + sta caterina
digitalWrite(rele15,HIGH);//poble 2 + creu + castell
digitalWrite(rele16,HIGH);//poble 1
*/
}

void loop(){
//inici sequencia rtc
rtc();
bt();


 DateTime now = RTC.now(); 
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println(); 
    delay(1000);


 //proves dimmer
//  delay(2000);
  //digitalWrite(rele9,HIGH);
  //delay(1000);
  //digitalWrite(rele9,LOW);
}

void rtc(){
   DateTime now = RTC.now(); 
  se = (now.minute());
  mi = (now.minute());
  ho = (now.hour());
 if (ho == 10 || ho == 11 || ho == 12 ||  ho == 13 ||  ho == 14  || ho == 17  || ho == 18 ||  ho == 19 ||  ho == 20){
  //horari del pesebre, josep k vos que hi faci, no em va quedar clar
  //activar rele maquina fum infern
  }
  if (mi == 0){//Es fa de dia
  digitalWrite(rele1,LOW);//Bomba moli + Gir Moli +Led Moli
  digitalWrite(rele2,LOW);//Moli canto cova
  digitalWrite(rele3,LOW);//Boira
  digitalWrite(rele4,HIGH);//Llum llac
  digitalWrite(rele6,LOW);//On/Off Màquina de fum
  digitalWrite(rele7,HIGH);//Infern + bomba de recirculació riu + foc + llamp + 3 bombetes vermelles
  digitalWrite(rele8,LOW);//Cel
  digitalWrite(rele9,LOW);//Dimmer
  digitalWrite(rele10,LOW);//Polsador contacte Màquina de fum
  digitalWrite(rele11,HIGH);//Naixement + sol + lluna
  digitalWrite(rele12,LOW);//poble 3
  digitalWrite(rele13,LOW);//masia + castell banderes
  digitalWrite(rele14,LOW);//poble 4 + sta caterina
  digitalWrite(rele15,LOW);//poble 2 + creu + castell
  digitalWrite(rele16,LOW);//poble 1}
  }
  if (mi == 1){//On cel
  digitalWrite(rele8,HIGH);//Cel 
  }
  if (mi == 2){
  digitalWrite(rele3,HIGH);//Boira
  }
  if (mi == 3){
  //NO ES FA RES
  }  
  if (mi == 4){
  digitalWrite(rele2,HIGH);//Moli canto cova
  }
  if (mi == 5){
  //NO ES FA RES
  }
  if (mi == 6){
  digitalWrite(rele2,LOW);//Moli canto cova
  }
  if (mi == 7){
  digitalWrite(rele3,LOW);//Boira
  }  
  if (mi == 8){
  //NO ES FA RES
  }
  if (mi == 9){
  digitalWrite(rele1,HIGH);//Bomba moli + Gir Moli +Led Moli  
  }
  if (mi == 10){
  //NO ES FA RES
  }  
  if (mi == 11){
  digitalWrite(rele1,LOW);//Bomba moli + Gir Moli +Led Moli  
  }  
  if (mi == 12){
  //NO ES FA RES
  }    
  if (mi == 13){
  digitalWrite(rele2,HIGH);//Moli canto cova
  }  
  if (mi == 14){
  //NO ES FA RES
  }   
  if (mi == 15){
  digitalWrite(rele2,LOW);//Moli canto cova
  }   
  if (mi == 16){
  digitalWrite(rele6,HIGH);//On/Off Màquina de fum
  } 
  if (mi == 17){
  //NO ES FA RES
  }   
  if (mi == 18){
  digitalWrite(rele1,HIGH);//Bomba moli + Gir Moli +Led Moli  
  }
  if (mi == 19){
  //NO ES FA RES
  }  
  if (mi == 20){
  digitalWrite(rele1,LOW);//Bomba moli + Gir Moli +Led Moli  
  }  
  if (mi == 21){
  //NO ES FA RES
  }   
  if (mi == 22){
  digitalWrite(rele3,HIGH);//Boira
  }   
  if (mi == 23){
  //NO ES FA RES
  }   
  if (mi == 24){//OFF cel COMENZA LA NIT
  digitalWrite(rele8,LOW);//Cel 
  } 
  if (mi == 25){
  digitalWrite(rele13,HIGH);//masia + castell banderes
  } 
  if ((mi == 25) && (se == 30)){
  digitalWrite(rele16,HIGH);//poble 1}
  }
  if ((mi == 25) && (se == 35)){
  digitalWrite(rele12,HIGH);//poble 3
  }
  if ((mi == 25) && (se == 40)){
  digitalWrite(rele14,HIGH);//poble 4 + sta caterina
  }
  if ((mi == 25) && (se == 45)){
  digitalWrite(rele13,LOW);//masia + castell banderes
  }
  if ((mi == 25) && (se == 46)){
  digitalWrite(rele15,HIGH);//poble 2 + creu + castell
  }
  if (mi == 26){
  //NO ES FA RE
  } 
  if (mi == 27){
  digitalWrite(rele3,LOW);//Boira
  }   
  if (mi == 28){
  digitalWrite(rele15,LOW);//poble 2 + creu + castell
  digitalWrite(rele13,HIGH);//masia + castell banderes
  } 
  if ((mi == 28) && (se == 30)){
  digitalWrite(rele16,LOW);//poble 1}
  }
  if ((mi == 28) && (se == 35)){
  digitalWrite(rele12,LOW);//poble 3
  }
  if ((mi == 28) && (se == 40)){
  digitalWrite(rele14,LOW);//poble 4 + sta caterina
  }
  if ((mi == 28) && (se == 45)){
  digitalWrite(rele15,LOW);//poble 2 + creu + castell
  }
  if (mi == 29){
  digitalWrite(rele13,LOW);//masia + castell banderes
  } 
  if (mi == 30){    
  digitalWrite(rele1,LOW);//Bomba moli + Gir Moli +Led Moli
  digitalWrite(rele2,LOW);//Moli canto cova
  digitalWrite(rele3,LOW);//Boira
  digitalWrite(rele4,HIGH);//Llum llac
  digitalWrite(rele6,LOW);//On/Off Màquina de fum
  digitalWrite(rele7,HIGH);//Infern + bomba de recirculació riu + foc + llamp + 3 bombetes vermelles
  digitalWrite(rele8,LOW);//Cel
  digitalWrite(rele9,LOW);//Dimmer
  digitalWrite(rele10,LOW);//Polsador contacte Màquina de fum
  digitalWrite(rele11,HIGH);//Naixement + sol + lluna
  digitalWrite(rele12,LOW);//poble 3
  digitalWrite(rele13,LOW);//masia + castell banderes
  digitalWrite(rele14,LOW);//poble 4 + sta caterina
  digitalWrite(rele15,LOW);//poble 2 + creu + castell
  digitalWrite(rele16,LOW);//poble 1}
  }
////2n cicle de 30 min desde el min 30 al 29  
  if (mi == 31){//On cel
  digitalWrite(rele8,HIGH);//Cel 
  }
  if (mi == 32){
  digitalWrite(rele3,HIGH);//Boira
  }
  if (mi == 33){
  //NO ES FA RES
  }  
  if (mi == 34){
  digitalWrite(rele2,HIGH);//Moli canto cova
  }
  if (mi == 35){
  //NO ES FA RES
  }
  if (mi == 36){
  digitalWrite(rele2,LOW);//Moli canto cova
  }
  if (mi == 37){
  digitalWrite(rele3,LOW);//Boira
  }  
  if (mi == 38){
  //NO ES FA RES
  }
  if (mi == 39){
  digitalWrite(rele1,HIGH);//Bomba moli + Gir Moli +Led Moli  
  }
  if (mi == 40){
  //NO ES FA RES
  }  
  if (mi == 41){
  digitalWrite(rele1,LOW);//Bomba moli + Gir Moli +Led Moli  
  }  
  if (mi == 42){
  //NO ES FA RES
  }    
  if (mi == 43){
  digitalWrite(rele2,HIGH);//Moli canto cova
  }  
  if (mi == 44){
  //NO ES FA RES
  }   
  if (mi == 45){
  digitalWrite(rele2,LOW);//Moli canto cova
  }   
  if (mi == 46){
  digitalWrite(rele6,HIGH);//On/Off Màquina de fum
  } 
  if (mi == 47){
  //NO ES FA RES
  }   
  if (mi == 48){
  digitalWrite(rele1,HIGH);//Bomba moli + Gir Moli +Led Moli  
  }
  if (mi == 49){
  //NO ES FA RES
  }  
  if (mi == 50){
  digitalWrite(rele1,LOW);//Bomba moli + Gir Moli +Led Moli  
  }  
  if (mi == 51){
  //NO ES FA RES
  }   
  if (mi == 52){
  digitalWrite(rele3,HIGH);//Boira
  }   
  if (mi == 53){
  //NO ES FA RES
  }   
  if (mi == 54){//OFF cel COMENZA LA NIT
  digitalWrite(rele8,LOW);//Cel 
  } 
  if (mi == 55){
  digitalWrite(rele13,HIGH);//masia + castell banderes
  } 
  if ((mi == 55) && (se == 30)){
  digitalWrite(rele16,HIGH);//poble 1}
  }
  if ((mi == 55) && (se == 35)){
  digitalWrite(rele12,HIGH);//poble 3
  }
  if ((mi == 55) && (se == 40)){
  digitalWrite(rele14,HIGH);//poble 4 + sta caterina
  }
  if ((mi == 55) && (se == 45)){
  digitalWrite(rele13,LOW);//masia + castell banderes
  }
  if ((mi == 55) && (se == 46)){
  digitalWrite(rele15,HIGH);//poble 2 + creu + castell
  }
  if (mi == 56){
  //NO ES FA RE
  } 
  if (mi == 57){
  digitalWrite(rele3,LOW);//Boira
  }   
  if (mi == 58){
  digitalWrite(rele15,LOW);//poble 2 + creu + castell
  digitalWrite(rele13,HIGH);//masia + castell banderes
  } 
  if ((mi == 58) && (se == 30)){
  digitalWrite(rele16,LOW);//poble 1}
  }
  if ((mi == 58) && (se == 35)){
  digitalWrite(rele12,LOW);//poble 3
  }
  if ((mi == 58) && (se == 40)){
  digitalWrite(rele14,LOW);//poble 4 + sta caterina
  }
  if ((mi == 58) && (se == 45)){
  digitalWrite(rele15,LOW);//poble 2 + creu + castell
  }
  if (mi == 59){
  digitalWrite(rele13,LOW);//masia + castell banderes
  } 
  if (mi == 0){    
  digitalWrite(rele1,LOW);//Bomba moli + Gir Moli +Led Moli
  digitalWrite(rele2,LOW);//Moli canto cova
  digitalWrite(rele3,LOW);//Boira
  digitalWrite(rele4,HIGH);//Llum llac
  digitalWrite(rele6,LOW);//On/Off Màquina de fum
  digitalWrite(rele7,HIGH);//Infern + bomba de recirculació riu + foc + llamp + 3 bombetes vermelles
  digitalWrite(rele8,LOW);//Cel
  digitalWrite(rele9,LOW);//Dimmer
  digitalWrite(rele10,LOW);//Polsador contacte Màquina de fum
  digitalWrite(rele11,HIGH);//Naixement + sol + lluna
  digitalWrite(rele12,LOW);//poble 3
  digitalWrite(rele13,LOW);//masia + castell banderes
  digitalWrite(rele14,LOW);//poble 4 + sta caterina
  digitalWrite(rele15,LOW);//poble 2 + creu + castell
  digitalWrite(rele16,LOW);//poble 1}
  }

}
void bt(){
//inici buffer bt
if (Serial.available()> 0 ){
  val= Serial.read();
if (val == 'A') {
digitalWrite(rele1,HIGH);
}else if (val == 'a') {
digitalWrite(rele1,LOW);
}else if (val == 'B'){
digitalWrite(rele2,HIGH);
}else if (val == 'b') {
digitalWrite(rele2,LOW);
}else if (val == 'C') {
digitalWrite(rele3,HIGH);
}else if (val == 'c') {
digitalWrite(rele3,LOW);
}else if (val == 'D') {
digitalWrite(rele4,HIGH);
}else if (val == 'd') {
digitalWrite(rele4,LOW);
}else if (val == 'E') {
digitalWrite(rele5,HIGH);
}else if (val == 'e') {
digitalWrite(rele5,LOW);
}else if (val == 'F') {
digitalWrite(rele6,HIGH);
}else if (val == 'f') {
digitalWrite(rele6,LOW);
}else if (val == 'G') {
digitalWrite(rele7,HIGH);
}else if (val == 'g') {
digitalWrite(rele7,LOW);
}else if (val == 'H') {
digitalWrite(rele8,HIGH);
}else if (val == 'h') {
digitalWrite(rele8,LOW);
}else if (val == 'I') {
digitalWrite(rele9,HIGH);
}else if (val == 'i') {
digitalWrite(rele9,LOW);
}else if (val == 'J') {
digitalWrite(rele10,HIGH);
}else if (val == 'j') {
digitalWrite(rele10,LOW);
}else if (val == 'K') {
digitalWrite(rele11,HIGH);
}else if (val == 'k') {
digitalWrite(rele11,LOW);
}else if (val == 'L') {
digitalWrite(rele12,HIGH);
}else if (val == 'l') {
digitalWrite(rele12,LOW);
}else if (val == 'M') {
digitalWrite(rele13,HIGH);
}else if (val == 'm') {
digitalWrite(rele13,LOW);
}else if (val =='N') {
digitalWrite(rele14,HIGH);
}else if (val == 'n') {
digitalWrite(rele14,LOW);
}else if (val == 'O') {
digitalWrite(rele15,HIGH);
}else if (val == 'o') {
digitalWrite(rele15,LOW);
}else if (val == 'P') {
digitalWrite(rele16,HIGH);
}else if (val == 'p') {
digitalWrite(rele16,LOW);
}
//Generals
else if (val == 'R'){
//General on
digitalWrite(rele1,HIGH);
digitalWrite(rele2,HIGH);
digitalWrite(rele3,HIGH);
digitalWrite(rele4,HIGH);
digitalWrite(rele5,HIGH);
digitalWrite(rele6,HIGH);
digitalWrite(rele7,HIGH);
digitalWrite(rele8,HIGH);
digitalWrite(rele9,HIGH);
digitalWrite(rele10,HIGH);
digitalWrite(rele11,HIGH);
digitalWrite(rele12,HIGH);
digitalWrite(rele13,HIGH);
digitalWrite(rele14,HIGH);
digitalWrite(rele15,HIGH);
digitalWrite(rele16,HIGH);
//General off
}else if (val == 'r'){
digitalWrite(rele1,LOW);
digitalWrite(rele2,LOW);
digitalWrite(rele3,LOW);
digitalWrite(rele4,LOW);
digitalWrite(rele5,LOW);
digitalWrite(rele6,LOW);
digitalWrite(rele7,LOW);
digitalWrite(rele8,LOW);
digitalWrite(rele9,LOW);
digitalWrite(rele10,LOW);
digitalWrite(rele11,LOW);
digitalWrite(rele12,LOW);
digitalWrite(rele13,LOW);
digitalWrite(rele14,LOW);
digitalWrite(rele15,LOW);
digitalWrite(rele16,LOW);
}
}
}

