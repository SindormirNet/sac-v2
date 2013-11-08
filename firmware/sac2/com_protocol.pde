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

byte ProcessReceivedDatagram(sac2_datagram *datagram){
  int i;
  int packet_type;
  byte integrity_check_status;
  byte working_buffer[]={0,0,0,0};

  integrity_check_status=IntegrityCheck();
  
  ClearDatagram(datagram);

  if (!integrity_check_status) {
    for (i=0; i<4; i++) {
      working_buffer[i]=cywm6935.rxbuf[i*2];
    }
    
    datagram->src = (working_buffer[0] & 0x70) >> 4;
    datagram->dst = (working_buffer[0] & 0x0E) >> 1;
    datagram->type= (working_buffer[1] & 0x20) >> 5;
    datagram->parity_byte = working_buffer[3];               // Copy checksum to datagram struct
    
    if (datagram->dst == myID - 48) {
      if (datagram->type == 0) {
        datagram->pl.status.pos = (working_buffer[1] & 0x1E) >> 1;
        datagram->pl.status.speed = (working_buffer[2] & 0x30) >> 4;
        datagram->pl.status.gotoexit = (working_buffer[2] & 0x0E) >> 1;
      }
      else { // datagram->type == 1
        packet_type=(working_buffer[1] & 0x1E) >> 1;
        
        switch (packet_type) {
          case 0x00: // Heartbeat packet
            datagram->type = 6;
          case 0x01: // Status request
            //smth
            break;
          case 0x02: // Remote control command        
            datagram->type = 4;
            datagram->pl.remote.speed    |= (working_buffer[2] & 0x3) >> 4;
            datagram->pl.remote.gotoexit |= (working_buffer[2] & 0x0E) >> 1;
            break;
          case 0x03: // SAC Control Protocol    
            //smth
            break;
          default: // ACK and manual motor control
            if (packet_type&0x08) { // ACK datagram
              datagram->type = 1;
              datagram->pl.ack.checksum |= (working_buffer[1] & 0x0E) << 4;
              datagram->pl.ack.checksum |= (working_buffer[2] & 0x3E) >> 1;
            }
            else { // Manual motor control
              datagram->type = 2;
              datagram->pl.motor.permanent_movement  |= (working_buffer[1] & 0x04) >> 2;
              datagram->pl.motor.permanent_direction |= (working_buffer[1] & 0x02) >> 1;
              datagram->pl.motor.movement  |= (working_buffer[2] & 0x38) >> 3;
              datagram->pl.motor.direction |= (working_buffer[2] & 0x06) >> 1;
            }
            break; 
        }
      }
    }
    else {
      Serial.print("[xNMD]2");
    }
  }
  return integrity_check_status;
}

void SendACK(sac2_datagram *incoming_datagram) {
  sac2_datagram acked_datagram;
  byte temp;
  
  //Reverse source and destination headers
  acked_datagram.src=incoming_datagram->dst;
  acked_datagram.dst=incoming_datagram->src;
  acked_datagram.type=1; //ACK data type
  
  acked_datagram.pl.ack.checksum=incoming_datagram->parity_byte;
  
  PrepareToSendDatagram(&acked_datagram);
  
  delay(5); // Era 50 antes de git
  cywm6935.tx();
  delay(10); // Era 100 antes de git
  cywm6935.tx();
  delay(20); // Esto no estaba antes de git. Con 25 iba bien
  cywm6935.tx();
  
  Serial.print("[xaCS]");
}

int sendHeartbeat() {
  sac2_datagram hb_output_datagram;
  
  ClearDatagram(&hb_output_datagram);
  hb_output_datagram.src  = myID - 48;
  hb_output_datagram.dst  = 0;
  hb_output_datagram.type = 0x06;
  
  PrepareToSendDatagram(&hb_output_datagram);
  
  delay(5); // Era 50 antes de git
  cywm6935.tx();
  delay(10); // Era 100 antes de git
  cywm6935.tx();
  delay(20); // Esto no estaba antes de git. Con 25 iba bien
  cywm6935.tx();
  
}

int sendHeartbeat_OLD() {
  int sendstatus;
  sac2_datagram hb_output_datagram;
  
  ClearDatagram(&hb_output_datagram);
  hb_output_datagram.src  = myID - 48;
  hb_output_datagram.dst  = 0;
  hb_output_datagram.type = 0x06;
  
  sendstatus=SendDatagram(&hb_output_datagram, 1000);  
  Serial.print("Sendstatus: ");  
  Serial.println(sendstatus, HEX); 
  return sendstatus;
}


void ReceiveDatagram(sac2_datagram *incomming_datagram, int gtimeout) {
  int recv_len=0;
  int recv_status;
  int second_tries_timeout=1000; //Con 1000 va muy bien
  int nack_tries_count=0;
  
  int canceled_by_user=0;
  int gtimeout_ocurred=0;
  int max_retries_reached=0;
  unsigned long int timer;

  timer=millis();

  do {
    recv_status=1; //Nuevo syv. no estaba antes del git
    cywm6935.clear_rx_buf(); //estaba aqui
    recv_len = cywm6935.rx(second_tries_timeout);

    if (recv_len == 8) { 
      recv_status=ProcessReceivedDatagram(incomming_datagram);
      
      delay(1); // Era 300 antes de git. Con 10 parece que funcionaba mejor. Sin esta espera no va mal
      if (recv_status) {
        second_tries_timeout=50; // Era 1000 antes de git. Con 50 parece que funcioanaba mejor
        nack_tries_count++;
      }
      if (nack_tries_count >50) {  // Era 18 antes de git. Con 20 parece que funcionaba mejor. syv a 50 3006
        max_retries_reached=1;
        break; 
      }
    }
    if (gtimeout!=0 && millis() >= timer + gtimeout) {
      gtimeout_ocurred=1;
      break;
    }

  } while (recv_status);

  if (!recv_status) {
    if (incomming_datagram->dst==(myID - 48)) {
      if (incomming_datagram->type==0) {
        Serial.print("[p");
        for (int i=0; i<8; i+=2) {
          Serial.print (cywm6935.rxbuf[i], HEX);
        }
        Serial.println("]");
      }
      if (incomming_datagram->type==6) { //Heartbeat packets
        Serial.print("[h");
        Serial.print(incomming_datagram->src, HEX);
        Serial.print("]");
      }
      
      if (incomming_datagram->type!=1) //Do not ack acks
        SendACK(incomming_datagram);
    }
    else {
      Serial.print("[xNMD] "); // Not my destination
    }
  }
  else {
    if (max_retries_reached) {
      Serial.println("[xRXE]");
      cywm6935.td_Init();  //Puesto de nuevo tras git. Nuevo Version 1.0.12
    }
    if (canceled_by_user) {
      Serial.print("[xCBU]"); // Cancelled by user
    }
    if (gtimeout_ocurred) {
      //Serial.print("[xrTO]"); // Receive timeout
    }
  }
}

/* Funciones adaptadas ****************************************************************************************************/

byte SendDatagram(sac2_datagram *output_datagram, int timeout) {
  int recv_len;
  byte recv_status;
  byte send_status=0x00;
  /*
   * send_status:
   * 0x00 -> Everything ok
   * 0x01 -> Timed out
   * 0x02 -> Max retries reached
   */
  unsigned long int timer;
  int max_retries=20;
  sac2_datagram response_datagram;
  
  timer=millis();
  
  PrepareToSendDatagram(output_datagram);
  do {    
    cywm6935.tx();

    cywm6935.clear_rx_buf();    // Prepare for ACK
    
    recv_len = cywm6935.rx(100); // Era 50 antes de librerias. Con 500 parece que funciona bien.
                                 // probado con 100 y no va bien

    if (recv_len == -1) max_retries--; 

    if (recv_len == 8) recv_status=ProcessReceivedDatagram(&response_datagram);

    if (max_retries < 1) {
      send_status |= 0x02; // xMRE
      break;
    }
    
    if ((timeout!=0) && (millis()>=timer+timeout)) {
      send_status |= 0x01; // xTTO
      break;
    }
    
  }while ((recv_status != 0x00) || (response_datagram.pl.ack.checksum != output_datagram->parity_byte)); //Cuidado con esto
  
  if (!send_status) Serial.println("[xACR]");
  
  return send_status;

}

void PrepareToSendDatagram(sac2_datagram *datagram) {
  int par_count=0;
  
  cywm6935.clear_tx_buf();

  //Building first byte
  cywm6935.txbuf[0] |= (datagram->src & 0x07) << 4;
  cywm6935.txbuf[0] |= (datagram->dst & 0x07) << 1;
  cywm6935.txbuf[0] |= get_parity_bit(cywm6935.txbuf[0]);

  //Building second and thirth byte
  cywm6935.txbuf[1] |= 0x80; // Header
  cywm6935.txbuf[2] |= 0xC0; // Header
  
  switch (datagram->type) {
    case 0: // Status datagram
      cywm6935.txbuf[1] |= (datagram->pl.status.pos & 0x0F)  << 1;
      cywm6935.txbuf[2] |= (datagram->pl.status.speed & 0x03)  << 4;
      cywm6935.txbuf[2] |= (datagram->pl.status.gotoexit & 0x07) << 1;
      break;
    case 1: // ACK response
      cywm6935.txbuf[1] |= 0x01 << 5; //type
      cywm6935.txbuf[1] |= 0x01 << 4; //control packet type
      cywm6935.txbuf[1] |= (datagram->pl.ack.checksum & 0xE0) >> 4;
      cywm6935.txbuf[2] |= (datagram->pl.ack.checksum & 0x1F) << 1;
      break;
    case 2: // Motor control
      cywm6935.txbuf[1] |= 0x01 << 5; //type
      cywm6935.txbuf[1] |= 0x01 << 3; //control packet type
      cywm6935.txbuf[1] |= (datagram->pl.motor.permanent_movement & 0x01)  << 2;
      cywm6935.txbuf[1] |= (datagram->pl.motor.permanent_direction & 0x01) << 1;
      cywm6935.txbuf[2] |= (datagram->pl.motor.movement & 0x07)  << 3;
      cywm6935.txbuf[2] |= (datagram->pl.motor.direction & 0x03)  << 1;
      break;  
    case 3: // SACP Control   
      cywm6935.txbuf[1] |= 0x01 << 5; //type
      cywm6935.txbuf[1] |= 0x03 << 1; //control packet type      
      if (datagram->pl.control.pip_ack)   cywm6935.txbuf[2] |= 0x06; //Set 2nd & 3th bits
      if (datagram->pl.control.pip_req)   cywm6935.txbuf[2] |= 0x04; //Set 3th bit
      if (datagram->pl.control.rtv_begin) cywm6935.txbuf[2] |= 0x08; //Set 4th bit
      if (datagram->pl.control.rtv_end)   cywm6935.txbuf[2] &= 0xF7; //Erase 4th bit
      break;
    case 4: // Remote control
      cywm6935.txbuf[1] |= 0x01 << 5; //type
      cywm6935.txbuf[1] |= 0x02 << 1; //control packet type 
      cywm6935.txbuf[2] |= (datagram->pl.remote.speed & 0x03)  << 4;
      cywm6935.txbuf[2] |= (datagram->pl.remote.gotoexit & 0x07) << 1;
      break;
    case 5: // Status request
      cywm6935.txbuf[1] |= 0x01 << 5; //type
      cywm6935.txbuf[1] |= 0x01 << 1; //control packet type 
      break;
    case 6: // Heartbeat
      cywm6935.txbuf[1] |= 0x01 << 5; //type
      break;      
  }    
  cywm6935.txbuf[1] |= get_parity_bit(cywm6935.txbuf[1]);
  cywm6935.txbuf[2] |= get_parity_bit(cywm6935.txbuf[2]);

  //Building parity byte
  for (int i=0; i<8; i++) {
    par_count=0;
    for (int j=0; j<3; j++) 
      if (cywm6935.txbuf[j] & (0x01 << i)) par_count++;
    if (par_count & 0x01) cywm6935.txbuf[3] |= 0x01 << i;
  }
  
  //Store parity byte in sac2_datagram structure
  datagram->parity_byte=cywm6935.txbuf[3];
}

/* Funciones comprobadas *******************************************/

void ClearDatagram(sac2_datagram *datagram) {
    datagram->src=0x00;
    datagram->dst=0x00;
    datagram->type=0x00;
    datagram->pl.motor.permanent_movement=0x00; //Se elije la union motor por ser la más grande
    datagram->pl.motor.permanent_direction=0x00;
    datagram->pl.motor.movement=0x00;
    datagram->pl.motor.direction=0x00; 
}

/*******************************************************************
 * Error_Word:  VHHHBPPP
 *
 * V = Valid byte H = Headers B = Parity Byte P = Individual parities
 * Everything ok= 0x00
 *******************************************************************/
int IntegrityCheck() { //This function does not care about payload
  int i,j;
  int error_word=0x00;
  int working_buffer[]={0,0,0,0};
  int par_count=0;
  int parity_byte=0;
  
  for (i=0; i<4; i++) { // Analyze Valid bytes and split data from valid bytes
    working_buffer[i]=cywm6935.rxbuf[i*2];
    if (cywm6935.rxbuf[i*2+1] != 0xFF) error_word |= 0x01 << 7;
  }  

  for (i=0; i<3; i++) { //Check last bit parity
    par_count=0;
    for (j=1; j<8; j++) if (working_buffer[i] & 0x01 << j ) par_count++;
    if ( par_count&0x01 - working_buffer[i]&0x01) error_word |= 0x01 <<i;
  }

  for (i=0; i<8; i++) {
    par_count=0;
    for (j=0; j<3; j++) if (working_buffer[j] & 0x01 << i) par_count++;
    if (par_count & 0x01) parity_byte |= 0x01 << i;
  }
  if (parity_byte != working_buffer[3]) error_word |= 0x01 <<3;

  //Check headers
  if  (working_buffer[0] & 0x80) error_word |= 0x01 <<4;
  if  (!(working_buffer[1] & 0x80) || (working_buffer[1] & 0x40) ) error_word |= 0x01 <<5;
  if  (!(working_buffer[2] & 0x80) && !(working_buffer[1] & 0x40) ) error_word |= 0x01 <<6;

  return error_word;
}

byte get_parity_bit(byte mybyte) {
  byte i;
  byte count=0;

  for (i=1; i<8; i++)
    if (mybyte & (0x01 << i)) count++;

  return (count&0x01);
}

