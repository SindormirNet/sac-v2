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

#ifndef VACIO_H
#define VACIO_H
#include <QPen>
#include <QRectF>
#include <QTime>
#include "sac.h"

class Vacio
{
public:
    Vacio();
    ~Vacio();

    void set_position(int, int);
    void set_coords(int, int, int, int);
    void set_width(int);
    void set_color(int,int,int);
    void set_visibility(bool);

    QRectF give_position();
    QPen give_aspect();

    QDateTime last_hb_received;
    int alive; // 0=ND, 1=Alive, 2=Gone
    int hb_count;

    sac_datagram last_datagram_received;

protected:
    int id;
    QRectF position;
    QPen aspect;
};

#endif // VACIO_H
