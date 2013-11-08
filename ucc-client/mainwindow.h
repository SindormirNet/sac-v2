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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QObject>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "PortListener.h"
#include "sac.h"
#include "vacio.h"


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
    QGraphicsScene* scene;
    QPixmap imagen;
    QGraphicsView* view;
    QList<Vacio*> robots;

    sac_datagram forged_datagram;

signals:
    void close_serial_port();
    void open_serial_port(QString port);
    void write_serial_port(QString in);
    void change_scene_pos_signal(int robot, int pos);
    void datagram_in_struct(int, bool);
    void decode_datagram(QString);
    void decode_hb(QString);
    void Motorcommand(QString, QString);

private slots:
    void on_pushButton_2_clicked();
    void on_comboBox_3_activated(QString );
    void on_comboBox_2_activated(QString );
    void on_comboBox_activated(QString );
    void on_comboBox_6_activated(QString);
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_comboBox_4_currentIndexChanged(int index);
    void on_pushButton_7_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_btnTestComm_clicked();
    void on_btnRadioReset_clicked();
    //void on_pushButton_3_clicked();
    void on_btnSendDgram_clicked();
    void on_btnDisconnect_clicked();
    void on_btnConnect_clicked();
    //void on_pushButton_clicked();
    void change_scene_pos(int, int);
    void display_datagram_content(int, bool);
    void packet_to_datagram(QString);
    void process_hb(QString);

public slots:
    void DisplayString(QString string);
    void sendMotorcommand(QString mov, QString dir);
    void refresh_table();
};


#endif // MAINWINDOW_H
