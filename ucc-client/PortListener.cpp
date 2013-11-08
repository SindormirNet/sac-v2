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


#include <qextserialport/qextserialport.h>
#include "mainwindow.h"

PortListener::PortListener(QextSerialPort * port, QObject * parent):
        QObject(parent)
{
        this->port = port;
}

void PortListener::receive()
{
    str  = new QString;
    QByteArray data="";
    QByteArray temp;
    int i=0;

    bool has_header=false;
    bool com_finished=false;

    do
    {
        data.append(port->read(1));

        if (!has_header)
        {
            if (data.at(i)=='[')
            {
                data.clear();
                i=0;
                has_header=true;
            }
            else
            {
                break;
            }
        }
        else //has_header==true
        {
            if (data.at(i++)==']')
            {
                has_header=false;
                com_finished=true;
                data.truncate(i-1);
             }
            if (data.length()>20) break;
        }
    }while(!com_finished);

    if (com_finished)
    {
        *str=data;
        emit newString( *str);
    }
}

void PortListener::close_port()
{
    qDebug("Cerrando puerto serie");
    port->close();
}

void PortListener::open_port(QString portname)
{
    qDebug("Reabriendo puerto serie");
    port->setPortName(portname.toAscii());
    port->open(QIODevice::ReadWrite);
}

void PortListener::write_port(QString in)
{
    qDebug("Escribiendo al puerto serie");
    port->write(in.toAscii().constData(), in.length());
}
