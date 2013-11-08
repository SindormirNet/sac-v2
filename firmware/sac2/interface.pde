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

void vacio_run() {
  int rfid_val;
  byte command=0;
  
  sac2_datagram status_datagram;
  sac2_datagram incomming_datagram;
  
  unsigned long int timer;
  
  timer=millis();
  
  cywm6935.setled(HIGH);
  while(1) {
    if (millis()>= timer+60000) {
      sendHeartbeat();
      timer=millis();
    }
    rfid_val = rfid_decode();
    if (rfid_val >= 0) {
      cywm6935.setled(LOW);
      ClearDatagram(&status_datagram);
      status_datagram.src= myID - 48; // Convert ascii number to dec. number
      status_datagram.dst=0x00;
      status_datagram.type=0x00;
      status_datagram.pl.status.pos=rfid_val;
      status_datagram.pl.status.speed=0x02;       // Example data
      status_datagram.pl.status.gotoexit=0x05;  // Example data
      SendDatagram(&status_datagram, 5000);
      timer=millis();
      cywm6935.setled(HIGH);
    }
    
    //Serial.println("recibiendo algo");
    ClearDatagram(&incomming_datagram);
    ReceiveDatagram(&incomming_datagram, 1000); //Was 1000
    
    
    //Serial.println("processing");
    if (incomming_datagram.type == 2) { //Motor control
      if (incomming_datagram.pl.motor.movement  == 0x00 || incomming_datagram.pl.motor.movement  == 0x04 ) stop_motores();
      if (incomming_datagram.pl.motor.movement  == 0x01) marcha_atras(); 
      if (incomming_datagram.pl.motor.movement  == 0x02) marcha_atras();
      if (incomming_datagram.pl.motor.movement  == 0x03) marcha_atras();
      if (incomming_datagram.pl.motor.movement  == 0x05) marcha_alante(); 
      if (incomming_datagram.pl.motor.movement  == 0x06) marcha_alante();
      if (incomming_datagram.pl.motor.movement  == 0x07) marcha_alante();
    
      if (incomming_datagram.pl.motor.direction == 0x00 || incomming_datagram.pl.motor.direction==0x03) ir_recto();
      if (incomming_datagram.pl.motor.direction == 0x01) gira_derecha(); 
      if (incomming_datagram.pl.motor.direction == 0x02) gira_izquierda();
      timer=millis();
    }
    if (incomming_datagram.type == 4) { //Remote control
      //Serial.println("RCtrl recvd");
      timer=millis();
    }
  }
  cywm6935.setled(LOW);
}

void ucc_run() {
  byte command=0;
  sac2_datagram menu_output_datagram;
  unsigned long int timer;
  
  timer=millis();
  
  while(1) {
    if (millis()>= timer+60000) {
      sendHeartbeat();
      Serial.println("[xH]");
      timer=millis();
    }
    
    cywm6935.setled(HIGH);
    ClearDatagram(&menu_output_datagram);
    ReceiveDatagram(&menu_output_datagram, 1000);
    cywm6935.setled(LOW);

    if (Serial.available() > 0) {
      command = Serial.read();

      switch (command) {
      case 0x6D: //m 
        ucc_sendMotorCommand();
        timer=millis();
        break;   
    
      case 0x72: //r
        ucc_sendRemoteCommand();
        timer=millis();
        break;  
    
      case 0x69: //i
        cywm6935.td_Init();
        Serial.print("[w");
        Serial.print (myID);   
        Serial.println("]");
        break; 
      }
    }
    delayMicroseconds(10); //Puesto para evitar el cuelgue en la recepcion de la UCC
  }
}

int ucc_sendMotorCommand() {
  byte dst;
  byte movement;
  byte direction;
  byte speed;
  int sendstatus;
  
  sac2_datagram menu_output_datagram;
  
  while (Serial.available() < 1){};
  dst = Serial.read();
  while (Serial.available() < 1){};
  movement = Serial.read();
  while (Serial.available() < 1){};
  speed = Serial.read();
  while (Serial.available() < 1){};
  direction = Serial.read();
  
  if (movement=='f') movement = (speed-48) + 4;
  if (movement=='b') movement = (speed-48) + 0;
  if (movement=='s') movement = 0;
      
  ClearDatagram(&menu_output_datagram);
  menu_output_datagram.src=myID - 48;
  menu_output_datagram.dst=dst - 48;
  menu_output_datagram.type=0x02;
  menu_output_datagram.pl.motor.movement= movement;
  menu_output_datagram.pl.motor.direction= direction - 48;
  
  sendstatus=SendDatagram(&menu_output_datagram, 5000);
  Serial.print("Sendstatus: ");  
  Serial.println(sendstatus, HEX);
  return sendstatus;
}

int ucc_sendRemoteCommand() {
  byte dst;
  byte speed;
  byte gotoexit;
  int sendstatus;
  
  sac2_datagram menu_output_datagram;
  
  while (Serial.available() < 1){};
  dst = Serial.read();
  while (Serial.available() < 1){};
  speed = Serial.read();
  while (Serial.available() < 1){};
  gotoexit = Serial.read();
      
  ClearDatagram(&menu_output_datagram);
  menu_output_datagram.src  = myID - 48;
  menu_output_datagram.dst  = dst - 48;
  menu_output_datagram.type = 0x04;
  menu_output_datagram.pl.remote.speed = speed-48;
  menu_output_datagram.pl.remote.gotoexit = gotoexit-48;
  
  sendstatus=SendDatagram(&menu_output_datagram, 5000);
  Serial.print("Sendstatus: ");  
  Serial.println(sendstatus, HEX); 
  return sendstatus;
}

void menu_writeDevID() {
  byte id;

  Serial.print("root@cywm6935:/device_id/$ ");
  while (Serial.available() < 1) {};

  id = Serial.read();
  EEPROM.write(0,id);
  Serial.print("Writing <");
  Serial.print(id,HEX);
  Serial.println("> to EEPROM");
}

