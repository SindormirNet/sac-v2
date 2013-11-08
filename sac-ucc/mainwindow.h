#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QObject>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "PortListener.h"
#include "sac.h"


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QextSerialPort * port;

    QGraphicsScene* scene; //= new QGraphicsScene(QRect(0, 0, 0, 0));
    QPixmap imagen;
    QGraphicsView* view; // = new QGraphicsView(ui->centralWidget);

    sac_datagram pdatagram;

    QRectF pos_vacio1;
    QPen aspect_vacio1;

    QRectF pos_vacio2;
    QPen aspect_vacio2;

    QRectF pos_vacio3;
    QPen aspect_vacio3;

signals:
    void close_serial_port();
    void open_serial_port();
    void write_serial_port(QString in);
    void change_scene_pos_signal(int robot, int pos);
    void datagram_in_struct();
    void decode_datagram(QString);

private slots:
    void on_btnSendDgram_clicked();
    void on_spnGoto_valueChanged(int );
    void on_spnSpeed_valueChanged(int );
    void on_spnPos_valueChanged(int );
    void on_spnType_valueChanged(int );
    void on_spnReceiver_valueChanged(int );
    void on_spnSender_valueChanged(int );
    void on_btnDisconnect_clicked();
    void on_btnConnect_clicked();
    void on_pushButton_clicked();
    void change_scene_pos(int, int);
    void display_datagram_content();
    int calcula_paridad_byte(int);
    void packet_to_datagram(QString);

public slots:
    void DisplayString( QString string );

};


#endif // MAINWINDOW_H
