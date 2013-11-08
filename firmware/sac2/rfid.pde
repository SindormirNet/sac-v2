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

int rfid_decode() {
  char tag_ID[]={0,0,0,0,0,0,0,0,0,0,'\0'};
  byte checksum;
  byte temp;
  int  conv_value=-1;
  int  frame_begin=0;
  int  frame_end=0;  
  int  pre_end=0;
  int  count=0;
  int  i;

  while(1) {  // Not using cheksum bytes here cause rfid module sends it incorrectly
    if (Serial.available() > 0) {
      temp=Serial.read();

      if (temp == 0x02 || temp == 0x03 || pre_end == 0x01) {
        if (temp == 0x02) { // Begining of frame detected
          frame_begin=1; 
          count=0;
        } 
        if (temp == 0x03) { // End of frame detected
          frame_begin=0;
          frame_end=1;
        }
        if (pre_end == 0x01) {
          pre_end=0x00;
        }
      }
      else { //N
        if (!frame_begin) {
          break;  // Detected data without previous header
        }

        if (count == 10) { // Reading checksum
          pre_end=0x01;
          checksum=temp;
        }
        else {
          tag_ID[count++]=temp;
        }
      }

      if (frame_end) {
        if (strcmp(tag_ID, "1D00459F9D")  == 0) conv_value=0;
        if (strcmp(tag_ID, "1D0045D6D9")  == 0) conv_value=1;
        if (strcmp(tag_ID, "1D004587F4")  == 0) conv_value=2;
        if (strcmp(tag_ID, "1D0045C636")  == 0) conv_value=3;
        if (strcmp(tag_ID, "1D0045E488")  == 0) conv_value=4;
        if (strcmp(tag_ID, "01074C8228")  == 0) conv_value=5;
        if (strcmp(tag_ID, "1F001AA1D2")  == 0) conv_value=6;
        if (strcmp(tag_ID, "3800C9D147")  == 0) conv_value=6;
        if (strcmp(tag_ID, "3800CA3C6B")  == 0) conv_value=7;
        if (strcmp(tag_ID, "3800CA0A28")  == 0) conv_value=8;
        if (strcmp(tag_ID, "3800CA437D")  == 0) conv_value=9;
        break;
      }
    }
    if (Serial.available() < 1) {  
      break;
    }
  }
  return conv_value;
}


