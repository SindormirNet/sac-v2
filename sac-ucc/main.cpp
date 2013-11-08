#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QThread>


//Por hacer:

//Recrear la clase vacio
//Hacer una QList de la objectos Vacio
//Limpiar includes no necesarios
//[FW] Posibilidad de salir del modo Liste
//Faltan posiciones en el circuito, las de las salidas
//Hacer algo gráficamente para que dos o más robots puedan ocupar el mismo sector
//[FW] Resetear si RX ERROR !mirar bien esto!
//Análisis de paquetes reales recibidos. Coger código en C
//Connect y disconnect son autistas
//[FW] Timeout muy largo entre NACKS
//Que el packet forge muestre el código HEXA que se está simulando


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    QextSerialPort * port = new QextSerialPort("/dev/ttyUSB0", QextSerialPort::EventDriven);

    port->setBaudRate(BAUD9600);
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);
    port->open(QIODevice::ReadWrite);

    /*if (!(port->lineStatus() & LS_DSR)) {
            qDebug("warning: device is not turned on");
    }*/

    PortListener * listener = new PortListener(port);

    listener->connect(port, SIGNAL(readyRead()), listener, SLOT(receive()));
    listener->connect(port, SIGNAL(bytesWritten(qint64)), listener, SLOT(reportWritten(qint64)));
    listener->connect(port, SIGNAL(aboutToClose()), listener, SLOT(reportClose()));
    listener->connect(port, SIGNAL(dsrChanged(bool)), listener, SLOT(reportDsr(bool)));

    SerialThread * thread = new SerialThread(port);
    a.connect(thread, SIGNAL(finished()), &a, SLOT(quit()));
    thread->start();

    w.connect( listener, SIGNAL(newString(QString)), &w, SLOT(DisplayString(QString)) );
    w.connect( &w, SIGNAL(close_serial_port()), listener, SLOT(close_port()) );
    w.connect( &w, SIGNAL(open_serial_port()), listener, SLOT(open_port()) );
    w.connect( &w, SIGNAL(write_serial_port(QString)), listener, SLOT(write_port(QString)) );
    w.connect( &w, SIGNAL(change_scene_pos_signal(int, int)), &w, SLOT(change_scene_pos(int, int)) );
    w.connect( &w, SIGNAL(datagram_in_struct()), &w, SLOT(display_datagram_content()));
    w.connect( &w, SIGNAL(decode_datagram(QString)), &w, SLOT(packet_to_datagram(QString)));

    //event loop is required to utilize signals and slots mechanism
    return a.exec();
}
