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

void WriteDevID(int id) {
  detachInterrupt(0);
  EEPROM.write(113,id);
  attachInterrupt(0, isr_handler, RISING);
}

byte ReadDevID() {
  byte id;
  detachInterrupt(0);
  id = EEPROM.read(113);
  attachInterrupt(0, isr_handler, RISING);
  return id;  
}

/*void reset_uC() {
  delay(1000); // This causes watchdog to actuate
}

void wd_alive() {
  digitalWrite(WD_PIN, LOW);      // Minimum TC32M strobe pulse width is 500 ns
  digitalWrite(WD_PIN, HIGH);     // Each digitalWrite takes about 4,5 uS. No need for delayMicroseconds() 
}*/
