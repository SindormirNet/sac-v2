#ifndef PORTLISTENER_H_
#define PORTLISTENER_H_

#include <QThread>
#include "qextserialport.h"

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
                void reportWritten(qint64 bytes);
                void reportClose();
                void reportDsr(bool status);
                void close_port();
                void open_port();
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
                        sleep(1000); //Esto hace que el hilo consuma menos CPU
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
