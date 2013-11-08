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

#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QThread>
#include <QTimer>

//Por hacer:
//Hacer algo gráficamente para que dos o más robots puedan ocupar el mismo sector

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    QextSerialPort *port = new QextSerialPort(QextSerialPort::EventDriven);

    port->setBaudRate(BAUD9600);
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);

    PortListener * listener = new PortListener(port);

    listener->connect(port, SIGNAL(readyRead()), listener, SLOT(receive()));

    SerialThread * thread = new SerialThread(port);
    a.connect(thread, SIGNAL(finished()), &a, SLOT(quit()));
    thread->start();
    thread->setPriority(QThread::TimeCriticalPriority);

    w.connect( listener, SIGNAL(newString(QString)), &w, SLOT(DisplayString(QString)) );
    w.connect( &w, SIGNAL(close_serial_port()), listener, SLOT(close_port()) );
    w.connect( &w, SIGNAL(open_serial_port(QString)), listener, SLOT(open_port(QString)) );
    w.connect( &w, SIGNAL(write_serial_port(QString)), listener, SLOT(write_port(QString)) );
    w.connect( &w, SIGNAL(change_scene_pos_signal(int, int)), &w, SLOT(change_scene_pos(int, int)) );
    w.connect( &w, SIGNAL(datagram_in_struct(int, bool)), &w, SLOT(display_datagram_content(int, bool)));
    w.connect( &w, SIGNAL(decode_datagram(QString)), &w, SLOT(packet_to_datagram(QString)));
    w.connect( &w, SIGNAL(decode_hb(QString)), &w, SLOT(process_hb(QString)));
    w.connect( &w, SIGNAL(Motorcommand(QString, QString)), &w, SLOT(sendMotorcommand(QString, QString)));

    /*Timer for refreshing the vehicle status table*/
    QTimer  * const  refresh_table_timer =  new QTimer(&w);
    refresh_table_timer->connect(refresh_table_timer, SIGNAL(timeout()), &w, SLOT(refresh_table()));
    refresh_table_timer->start(1000); //One second will be enought

    return a.exec();
}
