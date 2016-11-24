//PESSEBRE V1.1 BY BBJ SOLUTIONS & ROBOT-EC

//declarar llibreries wire, rtc i i2c
#include <Wire.h>
#include "RTClib.h"
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

const int Reles=16; //Num de reles
const int Estats=50; //Num estats

int MatriuEstats[Reles][Estats];

String MatriuHoraInici[Estats]; 
String MatriuHoraFi[Estats]; 

int MatriuReles[Reles]

//definim sensor de presencia
#define sensor_moviment  13

//Variables de temps RTC
int mi,ho,se;

//Valor del serial Bluetooth
char val;

//Variable Rellotge
RTC_DS1307 RTC;


/////////////////////////////////////////////////////////////////////////////////////////
void InitMatriuReles()
{
  // 9 Bomba moli + Gir Moli +Led Moli
  // 8 Moli canto cova
  // 7 Boira
  // 6 Llum llac
  // 5 relé que no clava (NU) NO FUNCIONA!!
  // 4 On/Off Màquina de fum
  // 3 Infern + bomba de recirculació riu + foc + llamp + 3 bombetes vermelles
  // 2 Cel
  // 39 Dimmer
  // 41 Polsador contacte Màquina de fum
  // 43 Naixement + sol + lluna
  // 45 poble 3
  // 47 masia + castell banderes
  // 49poble 4 + sta caterina
  // 51 poble 2 + creu + castell
  // 53 poble 1
    MatriuReles = {9,8,7,6,5,4,3,2,39,41,43,45,47,49,51,53};
}


/////////////////////////////////////////////////////////////////////////////////////////
void InitMatriuEstats()
{
  MatriuEstats = 
  {   
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} //Rele1  Bomba moli + Gir Moli +Led Moli
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} //Rele2  Moli canto cova
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} //Rele3  Boir
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} //Rele4  LLum LLac
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} //Rele5  No Funciona!!
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} //Rele6  Màquina de fum on/off
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} //Rele7  Infern + Bomba de recirculació riu + Foc + LLamp + 3 bombetes vermelles
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} //Rele8  Cel
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} //Rele9  Dimmer
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} //Rele10 Polsador contacte màquina de fum
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} //Rele11 Naixement + Sol + LLuna
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} //Rele12 Poble 3
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} //Rele13 Masia + Banderes Castell
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} //Rele14 Poble 4 + Santa Caterina
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} //Rele15 Poble 2 + Creu + Castell
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} //Rele16 Poble 1  
  }
}
////////////////////////////////////////////////////////////////////////////////////////


void InitMatriuHoraInici()
{
  MatriuHoraInici = {"0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0"};
}

////////////////////////////////////////////////////////////////////////////////////////


void InitMatriuHoraFi()
{
  MatriuHoraFi = {"0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0"};
}


/////////////////////////////////////////////////////////////////////////////////
void InitPins()
{
  for(int i=0; i<Reles; i++)
  {
    pinMode((MatriuReles[i],OUTPUT);
    digitalWrite(MatriuReles[i],LOW);
  }
  
  //Falten els pins del bluetooth Quins son??
  
  //Pins del PIR
  pinMode(sensor_moviment, INPUT);

  //Pins del MP3??
}
/////////////////////////////////////////////////////////////////////////////////


//Inicialitzar Bluetooth
void InitBT()
{
  Serial.begin(9600);  
}
////////////////////////////////////////////////////////////////////////////////


void setup()
{
  InitPins();//Inicialitzem tots els pins

  //RTC llegir hora rellotge pc i sincronitzarla al rtc
  Wire.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
  RTC.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
  RTC.adjust(DateTime(__DATE__, __TIME__)); //Sincronitza la hora amb el pc que compila
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
void loop()
{
  Automatic();  
}

////////////////////////////////////////////////////////////////////////////////

void Automatic()
{
  //Incialitzem la variable now amb l'hora actual
  DateTime now = RTC.now(); 
  //Ara obtenim el segon, el minut i la hora actual
  se = (now.minute());
  mi = (now.minute());
  ho = (now.hour());

  //Repassem les seqüències

}

////////////////////////////////////////////////////////////////////////////////

void Manual()
{
	switch(val)
  {
		case 'A':
      digitalWrite(rele1,HIGH);
    break; 

    case 'a':
      digitalWrite(rele1,LOW);
    break; 

    case 'B':
      digitalWrite(rele2,HIGH);
    break; 

    case 'b':
      digitalWrite(rele2,LOW);      
    break; 

    case 'C':
      digitalWrite(rele3,HIGH);
    break; 

    case 'c':
      digitalWrite(rele3,LOW);
    break; 

    case 'D':
      digitalWrite(rele4,HIGH);
    break; 

    case 'd':
      digitalWrite(rele4,LOW);
    break; 

    case 'E':
      digitalWrite(rele5,HIGH);
    break; 

    case 'e':
      digitalWrite(rele5,LOW);
    break; 

    case 'F':
      digitalWrite(rele6,HIGH);
    break; 

    case 'f':
      digitalWrite(rele6,LOW);
    break; 

    case 'G':
      digitalWrite(rele7,HIGH);
    break; 

    case 'g':
      digitalWrite(rele7,LOW);
    break; 

    case 'H':
      digitalWrite(rele8,HIGH);
    break; 

    case 'h':
      digitalWrite(rele8,LOW);
    break; 

    case 'I':
      digitalWrite(rele9,HIGH);
    break; 

    case 'i':
      digitalWrite(rele9,LOW);
    break; 

    case 'J':
      digitalWrite(rele10,HIGH);
    break; 

    case 'j':
      digitalWrite(rele10,LOW);
    break; 

    case 'K':
      digitalWrite(rele11,HIGH);
    break; 

    case 'k':
      digitalWrite(rele11,LOW);
    break; 

    case 'L':
      digitalWrite(rele12,HIGH);
    break; 

    case 'l':
      digitalWrite(rele12,LOW);
    break; 

    case 'M':
      digitalWrite(rele13,HIGH);
    break; 

    case 'm':
      digitalWrite(rele13,LOW);
    break; 
    
    case 'N':
      digitalWrite(rele14,HIGH);
    break; 
    
    case 'n':
      digitalWrite(rele14,LOW);
    break; 

    case 'O':
      digitalWrite(rele15,HIGH);
    break; 

    case 'o':
      digitalWrite(rele15,LOW);
    break; 

    case 'P':
      digitalWrite(rele16,HIGH);
    break; 

    case 'p':
      digitalWrite(rele16,LOW);
    break; 

    //El cas de R i r tenia entés que era per indicar si volies mode manual (R) o no (r) ????????????????????????????????
    case 'R':
      //General on
    break; 

    case 'r':
      //General off      
    break;

    default:
    break;
  }
}

