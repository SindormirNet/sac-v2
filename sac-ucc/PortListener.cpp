#include "qextserialport.h"
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
    int i=0;

    bool has_header=false;

    while(1)
    {
        data.append(port->read(1),1);
        usleep(5);
        if (data.at(i)=='[')
        {
            data.clear();
            i=0;
            data.append('[');
            has_header=true;
        }
        if (data.at(i++)==']') break;
        if (i>20)
        {
            data="";
            break;
        }
    }

    *str=data;

    if (has_header) emit newString( *str);
}

void PortListener::close_port()
{
    qDebug("Cerrando puerto serie");
    port->close();
}

void PortListener::open_port()
{
    qDebug("Reabriendo puerto serie");
    port->open(QIODevice::ReadWrite);
}

void PortListener::write_port(QString in)
{
    qDebug("Escribiendo al puerto serie");
    port->write(in.toAscii().constData(), in.length());
}

void PortListener::reportWritten(qint64 bytes)
{
    qDebug("some bytes written");
}

void PortListener::reportClose()
{
    qDebug("Closing port");
}

void PortListener::reportDsr(bool status)
{
        if (status)
                qDebug("device was turned on");
        else
                qDebug("device was turned off");
}
