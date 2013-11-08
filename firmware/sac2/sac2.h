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


/* Data Structures */
typedef struct {
  byte pos;
  byte speed;
  byte gotoexit;
} pl_status;

typedef struct {
  byte checksum;
} pl_ack;

typedef struct {
  boolean pip_req;
  boolean pip_ack;
  boolean rtv_begin;
  boolean rtv_end;
} pl_control;

typedef struct {
  boolean permanent_movement;
  boolean permanent_direction;
  byte movement;
  byte direction;
} pl_motor;

typedef struct {
  byte speed;
  byte gotoexit;
} pl_remote;

typedef union {
  pl_status status;
  pl_ack ack;
  pl_motor motor;
  pl_remote remote; 
  pl_control control;
} payload;

typedef struct { //8 bytes total
  byte src;
  byte dst;
  byte type; // 0->Status, 1->ACK, 2->Motor, 3->Control 4->Remote 5->StatusReq 6->Heartbeat
  payload pl;
  byte parity_byte;
} sac2_datagram;

