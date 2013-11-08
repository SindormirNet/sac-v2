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

void marcha_alante() {
  //Ir a velocidad maxima
  detachInterrupt(0);
  digitalWrite(MOTOR_BOARD_SPEED_LSB, HIGH);
  digitalWrite(MOTOR_BOARD_SPEED_MSB, HIGH);
  
  digitalWrite(MOTOR_BOARD_IRQ, HIGH);    // Pulse for interrupt
  digitalWrite(MOTOR_BOARD_IRQ, LOW);
  attachInterrupt(0, isr_handler, RISING);
}

void marcha_atras() {
  //Velocidad mnima
  detachInterrupt(0);
  digitalWrite(MOTOR_BOARD_SPEED_LSB, HIGH);
  digitalWrite(MOTOR_BOARD_SPEED_MSB, LOW);
  
  digitalWrite(MOTOR_BOARD_IRQ, HIGH);    // Pulse for interrupt
  digitalWrite(MOTOR_BOARD_IRQ, LOW);
  attachInterrupt(0, isr_handler, RISING);
}

void stop_motores() {
        //Parar
  detachInterrupt(0);
  digitalWrite(MOTOR_BOARD_SPEED_LSB, LOW);
  digitalWrite(MOTOR_BOARD_SPEED_MSB, LOW);
  
  digitalWrite(MOTOR_BOARD_IRQ, HIGH);    // Pulse for interrupt
  digitalWrite(MOTOR_BOARD_IRQ, LOW);
  attachInterrupt(0, isr_handler, RISING);
}

void gira_derecha() { 
    //Velocidad media
  digitalWrite(MOTOR_BOARD_SPEED_LSB, LOW);
  digitalWrite(MOTOR_BOARD_SPEED_MSB, HIGH);
  
  digitalWrite(MOTOR_BOARD_IRQ, HIGH);    // Pulse for interrupt
  digitalWrite(MOTOR_BOARD_IRQ, LOW);
  attachInterrupt(0, isr_handler, RISING);
}

void gira_izquierda(){ 
}

void ir_recto(){
}


/*void marcha_alante(int mspeed) {
  Serial.println("Palante");
  
  digitalWrite(MARCHA_ATRAS, LOW);
  digitalWrite(MARCHA_ALANTE, HIGH);
  delay(100);
  analogWrite(MARCHA_ALANTE, mspeed);
}

void marcha_atras(int mspeed) {
  Serial.println("Patras");
  detachInterrupt(0);
  digitalWrite(MARCHA_ALANTE, LOW);
  digitalWrite(MARCHA_ATRAS, HIGH);
  delay(100);
  analogWrite(MARCHA_ATRAS, mspeed );
  attachInterrupt(0, isr_handler, RISING);
}

void stop_motores() {
  Serial.println("Parando motores");
  detachInterrupt(0);
  digitalWrite(MARCHA_ALANTE, LOW);
  digitalWrite(MARCHA_ATRAS, LOW);
  digitalWrite(GIRA_IZQUIERDA, LOW);
  digitalWrite(GIRA_DERECHA, LOW);
  attachInterrupt(0, isr_handler, RISING);
}

void gira_derecha() {
  Serial.println("Derecha");
  detachInterrupt(0);
  digitalWrite(GIRA_IZQUIERDA, LOW);
  digitalWrite(GIRA_DERECHA, HIGH);
  attachInterrupt(0, isr_handler, RISING);
}

void gira_izquierda() {
  Serial.println("izquierda");
  detachInterrupt(0);
  digitalWrite(GIRA_DERECHA, LOW);
  digitalWrite(GIRA_IZQUIERDA, HIGH);
  attachInterrupt(0, isr_handler, RISING);
}

void ir_recto() {
  Serial.println("recto");
  detachInterrupt(0);
  digitalWrite(GIRA_DERECHA, LOW);
  digitalWrite(GIRA_IZQUIERDA, LOW);
  attachInterrupt(0, isr_handler, RISING);
}*/

