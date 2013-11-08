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

#ifndef PORTLISTENER_H_
#define PORTLISTENER_H_

#include <QThread>
#include <qextserialport/qextserialport.h>

class QextSerialPort;

class PortListener : public QObject
{
        Q_OBJECT

        QextSerialPort * port;

        public:
                PortListener(QextSerialPort * port, QObject * parent = 0);

        signals:
                void newString( QString string );

        public slots:
                void receive();
                void close_port();
                void open_port(QString portportname);
                void write_port(QString in);

        private:
                QString* str;
};

class SerialThread: public QThread
{
        QextSerialPort * port;

        protected:
                virtual void run()
                {
                    while(1)
                    {
                        sleep(1); //Esto hace que el hilo consuma menos CPU
                    }
                }

        public:
                SerialThread(QextSerialPort * port, QObject * parent = 0):
                        QThread(parent)
                {
                        this->port = port;
                }
};

#endif // PORTLISTENER_H_
