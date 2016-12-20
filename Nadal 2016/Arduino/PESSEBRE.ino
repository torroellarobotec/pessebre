//4-12-2016

#include <Wire.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include <DS1302.h>
#include <LiquidCrystal.h>

uint8_t RST_PIN = 52; //RST pin attach to BLANC
uint8_t SDA_PIN = 50; //IO pin attach to LILA
uint8_t SCL_PIN = 48; //clk Pin attach to GROC
DS1302 rtc(RST_PIN, SDA_PIN, SCL_PIN);//create a variable type of DS1302

/*
  Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
  pin 12 is connected to the DataIn
  pin 11 is connected to the CLK
  pin 10 is connected to LOAD
  We have only a single MAX72XX.
*/
LiquidCrystal lcd(22, 24, 26, 28, 30, 32);



long TempsInicial;
long TempsActual;
int ReproduintDia;
int ReproduintNit;
long TempsReproduccioDia;
long TempsReproduccioNit;
int repmusica;
int EstatMusica;
int Test = 0;
int indexPrint = 0;
int old_sec = 0;
int indexEstat = 0;
String displayManual = "";

int pinControl = 13;
int indexControl = 0;

int control = 0;

int modeAutomatic = 1;
int modeAnterior = 1;

const int Reles = 16; //Num de reles
const int Estats = 13; //Num estats

SoftwareSerial mySerial(10, 11); // Serial mp3 groc10 taronja11

//SoftwareSerial mySerialControl(37, 29); // R T
//SoftwareSerial mySerialBT(34, 36); // R T

//MatriuHoraInici
int MatriuHoraInici[Estats][2] = {
  // {0,0},{5,0},{10,0},{15,0},{20,0},{25,0},{25,40},{26,20},{27,0},{27,30},{27,50},{28,20},{29,10}  //loop 30 min
  {0, 0}, {3, 0}, {4, 0}, {9, 0}, {11, 0}, {12, 0}, {12, 20}, {13, 10}, {13, 30}, {13, 55}, {14, 10}, {14, 20}, {14, 30} //loop 15 min
  // {0,0},{3,0},{4,0},(9,0},{11,0},{12,0},{12,20},{13,10},{13,30},{13,55},{14,10},{14,20},{14,30}  //loop 15 min
  //(0, 0}, {0, 10}, {0, 20}, {0, 30}, {0, 40}, {0, 50}, {1, 0}, {1, 10}, {1, 20}, {1, 30}, {1, 40}, {1, 50}, {2, 0}
};

// el relé+1 indica la cançó a tocar
int MatriuEstats[Estats][Reles + 1] = {
  //Dia
  //1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7
  {1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1},
  {1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1},
  {1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1},
  {1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1},
  {1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1},

  //Nit
  //1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7
  {0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1},
  {0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 2},
  {0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 2},
  {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 2},
  //Encesa banderes
  {0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 2},
  //continua nit
  {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 2},
  {0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 2},
  {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 2}
};

// Definició dels relés en docment a part
//
int MatriuReles[Reles] = {9, 8, 7, 6, 5, 4, 3, 2, 53, 51, 49, 47, 45, 43, 41, 39};

//Variables de temps RTC
int mi, ho, se;

//Valor del serial Bluetooth
char val;

//Variable Rellotge
//RTC_DS1307 RTC;



////////////////////////////////////////////////////////////////////////////////

void setup()
{

  InitSerial();

  //Posar a hora
  // Time t(2016, 12, 16, 20, 45, 0, 0);//initialize the time
  // rtc.time(t);


  Serial.println("Start init");
  TempsInicial = millis();
  InitPins();//Inicialitzem tots els pins


  TempsReproduccioDia = 136000; //Dura 2 minuts i 16 segons
  TempsReproduccioNit = 92000; //Dura 1 minut i 32 segons

  //Incialitzem MP3
  mySerial.begin (9600);

  mp3_set_serial (mySerial);  //set softwareSerial for DFPlayer-mini mp3 module
  mp3_set_volume (20);
  mp3_stop ();


  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Iniciant...");

  ReproduintDia = 0;
  ReproduintNit = 0;


  TempsInicial = 0;
  TempsActual = 0;


  repmusica = 1;
  EstatMusica = 0;
  canviEstatInicial();
  Serial.println("Finish init");
}
////////////////////////////////////////////////////////////////////////////////

void loop()
{



  //mp3_stop();

  llegirSerie();
  llegirSerieBt();
  if (modeAutomatic == 1)
  {
    Automatic();
  }
  else
  {
    if (modeAnterior == 1)
    {
      resetEstat(0);
      modeAnterior = 0;
    }
    pintaSegments(0, 0, 0);

  }


  delay(800);
  digitalWrite(pinControl, !digitalRead(pinControl));

  if (modeAnterior = 0)
  {
    Time t = rtc.time();


    int hora = (int)t.hr;
    int mi = (int)t.min;
    int se = (int)t.sec;
    // lc.setChar(0, 7, '-', false);

  }
}


/////////////////////////////////////////////////////////////////////////////////

void InitPins()
{
  for (int i = 0; i < Reles; i++)
  {
    pinMode(MatriuReles[i], OUTPUT);
    digitalWrite(MatriuReles[i], LOW);
  }
  pinMode(pinControl, OUTPUT);
  digitalWrite(MatriuReles[8], HIGH); //Dimmer dia
  digitalWrite(MatriuReles[9], HIGH); //Fum
}

/////////////////////////////////////////////////////////////////////////////////

//Inicialitzar POt Serie
void InitSerial()
{
  Serial.begin(9600);
  Serial3.begin(9600);
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
  digitalWrite(39, HIGH);
}

/////////////////////////////////////////////////////////////////////////////////////

void TestReles()
{
  for (int i = 0; i < Reles; i++)
  {
    Serial.println("Rele: " + String(i + 1) + " Pin: " + String(MatriuReles[i]) + " HIGH");
    digitalWrite(MatriuReles[i], HIGH);
    delay(5000);

    Serial.println("Rele: " + String(i + 1) + " Pin: " + String(MatriuReles[i]) + " LOW");
    digitalWrite(MatriuReles[i], LOW);
    delay(2000);
  }
}
////////////////////////////////////////////////////////////////////////////////
void pintaSegments( int minu, int seg, int eventActual)
{
  lcd.begin(16, 2);

  String cad = "Estat:";
  if (modeAutomatic == 0)
  {
    cad += " MANUAL";
  }
  else
  {
    cad += (eventActual / 10);
    cad += (eventActual % 10);


    int seguentEstat = eventActual + 1;
    cad += " > ";
    if (seguentEstat >= Estats)
    {
      seguentEstat = 0;
      cad += "15:00";
    }
    else
    {
      int hestat =  MatriuHoraInici [seguentEstat][0];
      cad += (hestat / 10);
      cad += (hestat % 10);
      cad += ":";
      hestat =  MatriuHoraInici [ seguentEstat][1];
      cad += (hestat / 10);
      cad += (hestat % 10);
    }
  }


  lcd.print( cad);

  cad = "";
  lcd.setCursor(0, 1);
  Time t = rtc.time();


  int hora = (int)t.hr;
  int mi = (int)t.min;
  int se = (int)t.sec;
  cad += (hora / 10);
  cad += (hora % 10);
  cad += ":";
  cad += (mi / 10);
  cad += (mi % 10);
  cad += ":";
  cad += (se / 10);
  cad += (se % 10);
  if (modeAutomatic == 0)
  {
    cad += "   " + displayManual;
  }

  else
  {

    cad += "   ";


    cad += (minu / 10);
    cad += (minu % 10);
    cad += ":";
    cad += ( seg / 10);
    cad += (seg % 10);
  }






  lcd.print(cad);

}



void Automatic()
{
  indexPrint++;

  Musica();

  Time t = rtc.time();


  int hora = (int)t.hr;
  int mi = (int)t.min;
  int se = (int)t.sec;



  if (indexPrint == 10)
  {
    Serial.print(hora, DEC);
    Serial.print(":");
    Serial.print(mi, DEC);

    Serial.print(":");
    Serial.println(se, DEC);


  }




  // sequencia rapida
  if (mi >= 15)
  {
    int factor = mi / 15;
    mi = mi - factor * 15;
  }
  if (indexPrint == 10)
  {
    Serial.println("Minuts modificats: " + (String) mi + ":" + (String) se);
    Serial.println("Estat actual: " + (String) indexEstat);
    indexPrint = 0;

  }

  //escriure info
  pintaSegments(mi, se, indexEstat);


  //if (mi >= 30) mi = mi - 30;  //repetir cada 1/2 hora;



  //Primer comprovem si hora+minut correspon a algun estat
  for (int i = 0; i < Estats; i++)
  {
    //Serial.println("Minuts(Actual/Estat): " + String(mi) + "/" + String(MatriuHoraInici[i][0]) + " Segons(Actual/Estat): " + String(se) + "/" + String(MatriuHoraInici[i][1]));
    //Cas que el minut i la hora coincideixin per activar un rele
    if (MatriuHoraInici[i][0] == mi and MatriuHoraInici[i][1] == se)
    {
      Serial.println("Canvi d'estat: " + String(i));
      indexEstat = i;
      //Mirem quins reles s'han d'activar per aquest estat
      for (int j = 0; j < (Reles + 1); j++)
      {
        if (j == (Reles))
        {
          repmusica = MatriuEstats[i][j];

        }
        else
        {
          if (MatriuEstats[i][j] == 1) digitalWrite(MatriuReles[j], HIGH);

          if (MatriuEstats[i][j] == 0) digitalWrite(MatriuReles[j], LOW);
        }

      }

      delay(1000);

    }
  }
}

void canviEstatInicial()
{
  for (int j = 0; j < (Reles + 1); j++)
  {

    if (MatriuEstats[0][j] == 1) digitalWrite(MatriuReles[j], HIGH);

    if (MatriuEstats[0][j] == 0) digitalWrite(MatriuReles[j], LOW);
    Serial.println("Rele " + (String) j + " = " + MatriuEstats[0][j]);

  }

}
////////////////////////////////////////////////////////////////////////////////

void Musica()
{
  //  Serial.print(repmusica);
  //  Serial.print("..." );
  //  Serial.print((String) EstatMusica );
  //  Serial.println("." );
  if (repmusica != EstatMusica)
  {
    ReproduintDia = 0;
    ReproduintNit = 0;
    EstatMusica = repmusica;
    TempsInicial = millis();

  }


  if (repmusica == 1)
  {

    TempsActual = millis();

    if ((TempsActual - TempsInicial) < TempsReproduccioDia)
    {
      if (ReproduintDia == 0)
      {
        Serial.println("Play musica Dia");
        mp3_play(1);
        TempsInicial = millis();
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
  else
  {
    TempsActual = millis();
    if ((TempsActual - TempsInicial) < TempsReproduccioNit)
    {
      if (ReproduintNit == 0)
      {
        Serial.println("Play musica Nit");
        mp3_play(2);
        TempsInicial = millis();
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

////////////////////////////////////////////////////////////////////////////////

void resetEstat(int estat)
{
  int i = estat;
  for (int j = 0; j < (Reles + 1); j++)
  {
    if (j == (Reles))
    {
      repmusica = MatriuEstats[i][j];

    }
    else
    {
      if (MatriuEstats[i][j] == 1) digitalWrite(MatriuReles[j], HIGH);

      if (MatriuEstats[i][j] == 0) digitalWrite(MatriuReles[j], LOW);
    }

  }

  Serial.println("Canvi a estat " + (String) i);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void llegirSerie()
{

  if (Serial.available() > 0)
  {
    // read the incoming byte:
    int incomingByte = Serial.read();

    decodificaSerie(incomingByte);

  }
}
void llegirSerieBt()
{
  //Serial.print(".");
  if (Serial3.available())
  {
    //Serial.println("BT");
    // read the incoming byte:
    int incomingByte = Serial3.read();

    decodificaSerie(incomingByte);

  }
}
void decodificaSerie (int incomingByte)
{
  int car = 0;
  if (incomingByte > 47) //ignorar caracters estranys
  {
    if ((incomingByte > 47) && (incomingByte < 59))
    {
      car = incomingByte - 48;
    }
    if ((incomingByte > 64) && (incomingByte < 71))
    {
      car = incomingByte - 55;
    }
    if ((incomingByte > 96) && (incomingByte < 123))
    {
      car = incomingByte - 87;
    }

    if (incomingByte == 88 or incomingByte == 120) // X
    {
      resetEstat(0);

    }
    else
    {
      if (incomingByte == 90 or incomingByte == 122) // Z
      {
        if (modeAutomatic == 1)
        {
          modeAutomatic = 0;
          Serial.println("Pas a mode manual");
          displayManual = "";
        }
        else
        {
          modeAutomatic = 1;
          Serial.println("Pas a mode automatic");
        }

      }
      else
      {


        digitalWrite(MatriuReles[car], !digitalRead (MatriuReles[car]));



        Serial.println("Canvi rele " + (String) car + " a " + (String) digitalRead (MatriuReles[car]));
        displayManual = "R";
        displayManual += car / 10;
        displayManual += car % 10;
        displayManual += "=" + (String) digitalRead (MatriuReles[car]);
      }

    }
  }

}

