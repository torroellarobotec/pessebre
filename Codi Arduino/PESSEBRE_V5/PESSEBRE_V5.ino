#include "RTClib.h"
#include <Wire.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

int TempsInicial;
int TempsActual;
int ReproduintDia;
int ReproduintNit;
int TempsReproduccioDia;
int TempsReproduccioNit;

const int Reles=16; //Num de reles 
const int Estats=13; //Num estats

SoftwareSerial mySerial(10, 11); // RX, TX /*veure quins ports utilitzem al mega

//String MatriuHoraInici[Estats] =  { "0:0","5:0","10:0","15:0","20:0","25:0","25:40","26:20","27:0","27:30","27:50","28:20","29:10"};
//String MatriuHoraInici[Estats] =  { "0:0","0:30","1:0","1:30","2:0","2:30","3:0","3:30","4:0","4:30","5:0","5:30","6:0"};

//MatriuHoraInici
int MatriuHoraInici[Estats][2] = {
  //{0,0},{5,0},{10,0},{15,0},{20,0},{25,0},{25,40},{26,20},{27,0},{27,30},{27,50},{28,20},{29,10}
  {0,0},{0,30},{1,0},{1,30},{2,0},{2,30},{3,0},{3,30},{4,0},{4,30},{5,0},{5,30},{6,0}
};

int MatriuEstats[Estats][Reles+1] = {
   //Dia
   //1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7   
    {0,0,1,1,0,1,1,1,0,0,1,1,0,1,1,1,1},
    {1,1,1,1,0,1,1,1,0,0,1,1,0,1,1,1,1},
    {0,0,1,1,0,1,1,1,0,0,1,1,0,1,1,1,1},
    {1,1,1,1,0,1,1,1,0,0,1,1,0,1,1,1,1},
    {0,0,1,1,0,1,1,1,0,0,1,1,0,1,1,1,1},

   //Nit
   //1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7
    {1,1,0,1,0,1,1,1,1,0,1,0,0,0,0,0,2},
    {1,1,0,1,0,1,1,1,1,0,1,1,0,1,0,0,2},
    {1,1,0,1,0,1,1,1,1,0,1,0,0,1,1,0,2},
    {1,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,2},
    //Encesa banderes
    {0,0,0,0,0,1,1,1,1,0,1,0,1,0,0,0,2},
    //continua nit
    {1,1,0,1,0,1,1,1,1,0,1,1,0,0,0,1,2},  
    {1,1,0,1,0,1,1,1,1,0,1,1,0,0,1,0,2},
    {1,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,2}
};

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
int MatriuReles[Reles] = {9,8,7,6,5,4,3,2,39,41,43,45,47,49,51,53};

//Variables de temps RTC
int mi,ho,se;

//Valor del serial Bluetooth
char val;

//Variable Rellotge
RTC_DS1307 RTC;


/////////////////////////////////////////////////////////////////////////////////

void InitPins()
{
  for(int i=0; i<Reles; i++)
  {
    pinMode(MatriuReles[i],OUTPUT);
    digitalWrite(MatriuReles[i],LOW);
  }
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
  delay(1000);
  
  InitPins();//Inicialitzem tots els pins
  InitBT();
  
  TempsReproduccioDia = (2*60+16)*1000; //Dura 2 minuts i 16 segons
  TempsReproduccioNit = (1*60+32)*1000; //Dura 1 minut i 32 segons

  //Incialitzem MP3
  mySerial.begin (9600);
  mp3_set_serial (mySerial);  //set softwareSerial for DFPlayer-mini mp3 module 
  mp3_set_volume (20);
  
  ReproduintDia = 0;
  ReproduintNit = 0;


  //RTC llegir hora rellotge pc i sincronitzarla al rtc
  Wire.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
  RTC.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
  RTC.adjust(DateTime(__DATE__, __TIME__)); //Sincronitza la hora amb el pc que compila
}

////////////////////////////////////////////////////////////////////////////////

void loop()
{
  mp3_stop();  
  
  //reset();
  
  //TestMusica();
  Automatic();  
  //TestReles();
}

//////////////////////////////////////////////////////////////////////////////////////

void TestMusica()
{
  mp3_play(1);  
  delay(30000);
}

///////////////////////////////////////////////////////////////////////////////////////

void reset()
{
    digitalWrite(39,HIGH);  
}

/////////////////////////////////////////////////////////////////////////////////////

void TestReles()
{
  for(int i=0;i<Reles;i++)
  {
    Serial.print("Rele: " + String(i+1) + " Pin: " + String(MatriuReles[i]) + " HIGH");
    digitalWrite(MatriuReles[i], HIGH);
    delay(5000);

    Serial.print("Rele: " + String(i+1) + " Pin: " + String(MatriuReles[i]) + " LOW");
    digitalWrite(MatriuReles[i], LOW);
    delay(2000);
  }
}
////////////////////////////////////////////////////////////////////////////////

void Automatic()
{
  //Incialitzem la variable now amb l'hora actual
  DateTime now = RTC.now(); 
  //Ara obtenim el segon, el minut i la hora actual
  se = (now.second());
  mi = (now.minute());
  ho = (now.hour());

  if(mi >= 30) mi = mi-30;

  //Primer comprovem si hora+minut correspon a algun estat  
  for(int i=0; i<Estats; i++)
  {
    //Cas que el minut i la hora coincideixin per activar un rele
    if(MatriuHoraInici[i][0] == mi and MatriuHoraInici[i][1] == se)
    {
      //Mirem quins reles s'han d'activar per aquest estat
      for(int j=0; j<Reles;j++)
      {
        if(MatriuEstats[i][j] == 1) digitalWrite(MatriuReles[j], HIGH);
        if(MatriuEstats[i][j] == 0) digitalWrite(MatriuReles[j], LOW);
      }

      //Mirem si engegar o parar la música (0-Parat, 1-Pista1, 2-Pista3)      
      if(MatriuEstats[i][Reles+1] == 1) //Música de dia
      {
        TempsActual = millis();
        if((TempsActual - TempsInicial) < TempsReproduccioDia) 
        { 
          if(ReproduintDia == 0) 
          {
            mp3_play(1);
            ReproduintDia = 1;
            ReproduintNit = 0;
          } 
        }
        else 
        {
          ReproduintDia = 0;
          TempsInicial = millis();
        }         
      }
      
      if(MatriuEstats[i][Reles+1] == 2) //Música de nit
      {
        TempsActual = millis();
        if((TempsActual - TempsInicial) < TempsReproduccioNit) 
        { 
          if(ReproduintNit == 0) 
          {
            mp3_play(2);
            ReproduintNit = 1;
            ReproduintDia = 0;
          } 
        }
        else 
        {
          ReproduintNit = 0;
          TempsInicial = millis();
        }             
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

