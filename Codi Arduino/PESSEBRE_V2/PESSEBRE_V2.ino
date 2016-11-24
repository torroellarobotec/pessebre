//declarar llibreries wire, rtc i i2c
#include <Wire.h>
#include "RTClib.h"
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

const int Reles=16; //Num de reles
const int Estats=50; //Num estats

int MatriuEstats[Reles][Estats];

String MatriuHoraInici[Estats]; 

//String MatriuHoraFi[Estats]; ???????????????????????????????

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
    //Estat 1 Hora _ Minut _
  MatriuHoraInici = { "0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0",
                      "0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0",
                      "0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0",
                      "0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0",
                      "0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0"};
}

////////////////////////////////////////////////////////////////////////////////////////


//void InitMatriuHoraFi()
//{
//  MatriuHoraFi = {  "0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0",
 //                     "0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0",
 //                     "0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0",
 //                     "0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0",
 //                     "0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0","0:0"};
//}


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

  //Primer comprovem si hora+minut correspon a algun estat
  for(int i=0; i<Estats; i++)
  {
    //Cas que la hora i el minut coincideixin per activar un rele
    if(MatriuHoraInici[i] == String(ho) + ":" + String(mi))
    {
      //Mirem quins reles s'han d'activar per aquest estat
      for(int j=0; j<Reles;j++)
      {
        if(MatriuEstats[j,i] == 1) digitalWrite(MatriuReles[j], HIGH);
        if(MatriuEstats[j,i] == 0) digitalWrite(MatriuReles[j], LOW);
      }
    }
  }

}

////////////////////////////////////////////////////////////////////////////////

void Manual()
{
	switch(val)
  {
		case 'A':
      digitalWrite(MatriuReles[1],HIGH);
    break; 

    case 'a':
      digitalWrite(MatriuReles[1],LOW);
    break; 

    case 'B':
      digitalWrite(MatriuReles[2],HIGH);
    break; 

    case 'b':
      digitalWrite(MatriuReles[2],LOW);      
    break; 

    case 'C':
      digitalWrite(MatriuReles[3],HIGH);
    break; 

    case 'c':
      digitalWrite(MatriuReles[3],LOW);
    break; 

    case 'D':
      digitalWrite(MatriuReles[4],HIGH);
    break; 

    case 'd':
      digitalWrite(MatriuReles[4],LOW);
    break; 

    case 'E':
      digitalWrite(MatriuReles[5],HIGH);
    break; 

    case 'e':
      digitalWrite(MatriuReles[5],LOW);
    break; 

    case 'F':
      digitalWrite(MatriuReles[6],HIGH);
    break; 

    case 'f':
      digitalWrite(MatriuReles[6],LOW);
    break; 

    case 'G':
      digitalWrite(MatriuReles[7],HIGH);
    break; 

    case 'g':
      digitalWrite(MatriuReles[7],LOW);
    break; 

    case 'H':
      digitalWrite(MatriuReles[8],HIGH);
    break; 

    case 'h':
      digitalWrite(MatriuReles[8],LOW);
    break; 

    case 'I':
      digitalWrite(MatriuReles[9],HIGH);
    break; 

    case 'i':
      digitalWrite(MatriuReles[9],LOW);
    break; 

    case 'J':
      digitalWrite(MatriuReles[10],HIGH);
    break; 

    case 'j':
      digitalWrite(MatriuReles[10],LOW);
    break; 

    case 'K':
      digitalWrite(MatriuReles[11],HIGH);
    break; 

    case 'k':
      digitalWrite(MatriuReles[11],LOW);
    break; 

    case 'L':
      digitalWrite(MatriuReles[12],HIGH);
    break; 

    case 'l':
      digitalWrite(MatriuReles[12],LOW);
    break; 

    case 'M':
      digitalWrite(MatriuReles[13],HIGH);
    break; 

    case 'm':
      digitalWrite(MatriuReles[13],LOW);
    break; 
    
    case 'N':
      digitalWrite(MatriuReles[14],HIGH);
    break; 
    
    case 'n':
      digitalWrite(MatriuReles[14],LOW);
    break; 

    case 'O':
      digitalWrite(MatriuReles[15],HIGH);
    break; 

    case 'o':
      digitalWrite(MatriuReles[15],LOW);
    break; 

    case 'P':
      digitalWrite(MatriuReles[16],HIGH);
    break; 

    case 'p':
      digitalWrite(MatriuReles[16],LOW);
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

