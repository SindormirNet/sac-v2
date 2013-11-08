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

#include "vacio.h"

Vacio::Vacio()
{
    qDebug("Initializing new vacio");

    set_coords(20,20,25,25);
    set_width(25);
    set_position(302,124);
    set_visibility(false);

    alive=0;
    hb_count=0;
    last_hb_received.fromString("1.1.00", "d.M.yy");

}

Vacio::~Vacio()
{
    qDebug("Muriendo Object Vacio");
}

void Vacio::set_position(int x, int y)
{
    position.moveCenter(QPointF(x,y));
}

void Vacio::set_coords(int x1, int y1, int x2, int y2)
{
    position.setCoords(x1,y1,x2,y2);
}

void Vacio::set_width(int width)
{
    aspect.setWidth(width);
}

void Vacio::set_color(int r,int g,int b)
{
    aspect.setBrush(QBrush(QColor(r,g,b)));
}

void Vacio::set_visibility(bool visibility)
{
    if (visibility)
        aspect.setWidth(25);
    else
        aspect.setWidth(0);
}

QRectF Vacio::give_position()
{
    return (position);
}

QPen Vacio::give_aspect()
{
    return(aspect);
}



