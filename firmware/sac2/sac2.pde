// SAC Project V2.0 - Copyright (C) 2010 Jorge Gomez Arenas
// This file is part of SAC Project. (http://sac.sindormir.net)
//
// SAC Project is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// SAC Project is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with SAC Project.  If not, see <http://www.gnu.org/licenses/>.
//
// Contact info: Jorge Gomez Arenas <syvic@sindormir.net>

#include <EEPROM.h>
//#include <SoftwareSerial.h>
#include <cyspi.h>
#include <cywm6935.h>
#include "sac2.h"

#define BUILD_VER               "1.0.21"
#define AUTHOR                  "Jorge Gomez"
#define AUTHOR_EMAIL            "syvic@sindormir.net"

/* GPIO defines */

#define HARD_SERIAL_RX          0
#define HARD_SERIAL_TX          1
#define WD_PIN                  6


#define MOTOR_BOARD_SPEED_MSB   14
#define MOTOR_BOARD_SPEED_LSB   15
#define MOTOR_BOARD_T_E         16
#define MOTOR_BOARD_IRQ         17

#define SOFT_SERIAL_RX          18
#define SOFT_SERIAL_TX          19

#define RS232_BAUDRATE          9600


/* Global Variables */
byte myID;

/* Initialize objects */
CYSPI spi = CYSPI();
CYWM6935 cywm6935 = CYWM6935();
//SoftwareSerial mySerial = SoftwareSerial(SOFT_SERIAL_RX, SOFT_SERIAL_TX);


void setup(){
  pinMode(SOFT_SERIAL_RX,INPUT);
  pinMode(SOFT_SERIAL_TX,OUTPUT);
  pinMode(MOTOR_BOARD_SPEED_LSB, OUTPUT);
  pinMode(MOTOR_BOARD_SPEED_MSB,  OUTPUT);
  pinMode(MOTOR_BOARD_T_E,OUTPUT);
  pinMode(MOTOR_BOARD_IRQ,  OUTPUT);
  
  digitalWrite(MOTOR_BOARD_SPEED_LSB,LOW);
  digitalWrite(MOTOR_BOARD_SPEED_MSB,LOW);
  digitalWrite(MOTOR_BOARD_T_E,LOW);
  digitalWrite(MOTOR_BOARD_IRQ,LOW);

  cywm6935.setled(HIGH);
  
  stop_motores();

  Serial.begin(RS232_BAUDRATE);
  //mySerial.begin(RS232_BAUDRATE);

  Serial.println(BUILD_VER);

  Serial.print("Inicializando");

  myID=ReadDevID();
  
  cywm6935.config();  
  spi.config();

  delay(500);
  cywm6935.wireless_start();
  
  Serial.println(BUILD_VER);
  Serial.println("------------------------");
  Serial.print("[w");
  Serial.print (myID - 48);
  Serial.print("]");
  
  attachInterrupt(0, isr_handler, RISING);
  sendHeartbeat();
  
  cywm6935.setled(LOW);
}

void isr_handler() {
  cywm6935.cy_isr_handler();
}

void loop() {
  if (myID == '0x00') {
    menu_writeDevID();
  }
  
  if (myID == '0') {
    ucc_run();
  }
  
  if (myID == '1' || myID == '2' || myID == '3') {
    vacio_run(); //Lauch VACIO/OS
  }
}

