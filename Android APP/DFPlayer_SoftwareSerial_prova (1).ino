/*******************************************************************************
 * DFPlayer_Mini_Mp3, This library provides a quite complete function for      * 
 * DFPlayer mini mp3 module.                                                   *
 * www.github.com/dfrobot/DFPlayer_Mini_Mp3 (github as default source provider)*
 *  DFRobot-A great source for opensource hardware and robot.                  *
 *                                                                             *
 * This file is part of the DFplayer_Mini_Mp3 library.                         *
 *                                                                             *
 * DFPlayer_Mini_Mp3 is free software: you can redistribute it and/or          *
 * modify it under the terms of the GNU Lesser General Public License as       *
 * published by the Free Software Foundation, either version 3 of              *
 * the License, or any later version.                                          *
 *                                                                             *
 * DFPlayer_Mini_Mp3 is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 * GNU Lesser General Public License for more details.                         *
 *                                                                             *
 * DFPlayer_Mini_Mp3 is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 * GNU Lesser General Public License for more details.                         *
 *                                                                             *
 * You should have received a copy of the GNU Lesser General Public            *
 * License along with DFPlayer_Mini_Mp3. If not, see                           *
 * <http://www.gnu.org/licenses/>.                                             *
 *									       *
 ******************************************************************************/

/*
 *	Copyright:	DFRobot
 *	name:		DFPlayer_Mini_Mp3 sample code
 *	Author:		lisper <lisper.li@dfrobot.com>
 *	Date:		2014-05-30
 *	Description:	connect DFPlayer Mini by SoftwareSerial, this code is test on Uno
 *			Note: the mp3 files must put into mp3 folder in your tf card 
 */
 /*adaptat per ROBOT-EC pel pesebre de torroella*/
 
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

int TempsInicial;
int TempsActual;
int Reproduint;
int TempsReproduccio;

SoftwareSerial mySerial(10, 11); // RX, TX /*veure quins ports utilitzem al mega
int dia;
//
void setup () {
	TempsReproduccio = 10000; /*milisegons de reproducció de la cançó*/
	Reproduint = 0;
	TempsInicial = millis();
    dia=1;
	Serial.begin (9600);
	mySerial.begin (9600);
	mp3_set_serial (mySerial);	//set softwareSerial for DFPlayer-mini mp3 module 
	mp3_set_volume (10);
}


//
void loop () {
	switch(dia){
		case 1: 
			TempsActual = millis();    

			if((TempsActual - TempsInicial) < TempsReproduccio) 
			{	
				if(Reproduint == 0) 
				{
					mp3_play(1);
					Reproduint = 1;
				}	
			}
			else 
			{
				Reproduint = 0;
				TempsInicial = millis();
			}
			break;
			
		case 2: 
			TempsActual = millis();    

			if((TempsActual - TempsInicial) < TempsReproduccio) 
			{	
				if(Reproduint == 0) 
				{
					mp3_play(2);
					Reproduint = 1;
				}	
			}
			else 
			{
				Reproduint = 0;
				TempsInicial = millis();
			}
			break;
		case 3:
			mp3_stop();
			break;
	}
}

/*
   mp3_play ();		//start play
   mp3_play (5);	//play "mp3/0005.mp3"
   mp3_next ();		//play next 
   mp3_prev ();		//play previous
   mp3_set_volume (uint16_t volume);	//0~30
   mp3_set_EQ ();	//0~5
   mp3_pause ();
   mp3_stop ();
   void mp3_get_state (); 	//send get state command
   void mp3_get_volume (); 
   void mp3_get_u_sum (); 
   void mp3_get_tf_sum (); 
   void mp3_get_flash_sum (); 
   void mp3_get_tf_current (); 
   void mp3_get_u_current (); 
   void mp3_get_flash_current (); 
   void mp3_single_loop (boolean state);	//set single loop 
   void mp3_DAC (boolean state); 
   void mp3_random_play (); 
 */

