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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vacio.h"

#include <QTime>
#include <QList>
#include <QFile>

#define NUMBER_OF_VACIOS 3

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    QFile devices;
    QString devicename;

    setWindowTitle("Central Control Unit Client 0.1");

    ui->setupUi(this);

    ui->btnConnect->setEnabled(true);
    ui->btnDisconnect->setEnabled(false);

    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    ui->pushButton_8->setEnabled(false);
    ui->pushButton_9->setEnabled(false);
    ui->pushButton_10->setEnabled(false);
    ui->pushButton_11->setEnabled(false);
    ui->pushButton_12->setEnabled(false);

    //Populate Serial Port Combo box
    devicename="/dev/ttyUSBX";
    for (int i=0; i<8; i++) //Does anybody have more than 8?
    {
        devicename.chop(1); //Drop the last char from devicename
        if (devices.exists(devicename.append(i+48))) //Test for file to exist
            ui->cmbportselector->addItem(devicename.toAscii());
    }

    scene = new QGraphicsScene(QRect(0, 0, 0, 0));
    view = new QGraphicsView(ui->centralWidget);

    view->setStyleSheet("background: transparent");

    imagen.load(":/new/icons/resources/pista-nueva.png", "png", NULL);
    imagen=imagen.scaled(593,225,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    /*QList<QBrush*> cell_color;

    for (int i=0; i<NUMBER_OF_VACIOS; i++)
    {
        cell_color.append(new QBrush);
    }

    cell_color.at(0)->setColor(Qt::red);
    cell_color.at(1)->setColor(Qt::green);
    cell_color.at(2)->setColor(Qt::blue);*/

    scene->addPixmap(imagen);

    //view->setGeometry(QRect(230, 10, 605, 247));
    view->setGeometry(QRect(230, 10, 600, 240));
    view->setScene(scene);

    //Initialize all the Vacios
    for (int i=0; i<NUMBER_OF_VACIOS; i++)
        robots.append(new Vacio());

    ui->spnSender->setMaximum(NUMBER_OF_VACIOS);

    //Temporal: Cambiar este código por otro que autogenere los colores dinámicamente
    robots.at(0)->set_color(255,0,0);
    robots.at(1)->set_color(0,255,0);
    robots.at(2)->set_color(0,0,255);

    ui->statusBar->showMessage(tr("CCU Client 0.1 Ready"),10000);
    view->show();
}


MainWindow::~MainWindow()
{
    emit close_serial_port();
    delete ui;
}

/*void MainWindow::on_pushButton_clicked()
{
    ui->statusBar->showMessage(tr("Setting up device to Listen Mode"),10000);
    emit write_serial_port("d");
}*/

void MainWindow::on_btnConnect_clicked()
{
QList<Vacio*> robots;
    emit open_serial_port(ui->cmbportselector->itemText(ui->cmbportselector->currentIndex()));
    ui->statusBar->showMessage(tr("Connected!"),10000);
    ui->btnConnect->setEnabled(false);
    ui->btnDisconnect->setEnabled(true);
    ui->cmbportselector->setEnabled(false);
}

void MainWindow::on_btnDisconnect_clicked()
{
    emit close_serial_port();
    ui->statusBar->showMessage(tr("Disconnected"),10000);
    ui->btnConnect->setEnabled(true);
    ui->btnDisconnect->setEnabled(false);
    ui->cmbportselector->setEnabled(true);
}

void MainWindow::DisplayString( QString string )
{
    QDateTime hora = QDateTime::currentDateTime();
    QString t;
    t=hora.toString( "hh:mm:ss:zzz " );

    qDebug(string.toAscii());

    if (string.size() > 0)
    {
        switch (string.at(0).toAscii())
        {
            case 'p':
                    string=string.right(8);
                    string.append('\0');
                    ui->lstcomm->addItem(t + string);
                    ui->lstcomm->item(ui->lstcomm->count()-1)->setForeground(Qt::blue);
                    ui->pktcounter->display(ui->pktcounter->value()+1);
                    emit decode_datagram(string);
                    break;
            case 'h':
                    string=string.mid(1,1);
                    ui->lstcomm->addItem(t + "HB from " + string);
                    ui->lstcomm->item(ui->lstcomm->count()-1)->setBackground(Qt::gray);
                    ui->pktcounter->display(ui->pktcounter->value()+1);
                    emit decode_hb(string);
                    break;
            case 'w':
                    string=string.mid(1,1);
                    ui->lstcomm->addItem(t + "ID " + string + " booting");
                    ui->lstcomm->item(ui->lstcomm->count()-1)->setBackground(Qt::yellow);
                    break;
            case 'x':
                    switch(string.at(1).toAscii())
                    {
                    case 'a':
                        ui->lstcomm->addItem(t + "ACK Sent");
                        ui->lstcomm->item(ui->lstcomm->count()-1)->setForeground(Qt::green);
                        break;
                    case 'A':
                        ui->lstcomm->addItem(t + "ACK Recvd");
                        ui->lstcomm->item(ui->lstcomm->count()-1)->setBackground(Qt::green);
                        break;
                    case 'R':
                        ui->lstcomm->addItem(t + "RX Error");
                        ui->lstcomm->item(ui->lstcomm->count()-1)->setBackground(Qt::red);
                        break;
                    case 'T':
                        ui->lstcomm->addItem(t + "TX Error");
                        ui->lstcomm->item(ui->lstcomm->count()-1)->setForeground(Qt::red);
                        break;
                    case 'r':
                        //ui->lstcomm->addItem(t + "RX Timeout");
                        //ui->lstcomm->item(ui->lstcomm->count()-1)->setForeground(Qt::red);
                        break;
                    case 'H':
                        string=string.mid(1,1);
                        ui->lstcomm->addItem(t + "HB Sent");
                        break;
                    }

        }
        ui->lstcomm->setCurrentRow(ui->lstcomm->count()-1);
    }
}

void MainWindow::change_scene_pos(int robot, int pos)
{
    robots.at(robot)->set_coords(20,20,25,25);
    robots.at(robot)->set_visibility(true);

    switch (pos)
    {
        case 0:
            robots.at(robot)->set_position(164,41); // 137,46);
            break;
        case 1:
            robots.at(robot)->set_position(57,123); // 55,128);
            break;
        case 2:
            robots.at(robot)->set_position(174,170); // 172,178);
            break;
        case 3:
            robots.at(robot)->set_position(418,193); // 425,204);
            break;
        case 4:
            robots.at(robot)->set_position(545,138); // 552,133);
            break;
        case 5:
            robots.at(robot)->set_position(432,44); // 442,45);
            break;
        case 6:
            robots.at(robot)->set_position(46,199); // 42,212);
            break;
        case 7:
            robots.at(robot)->set_position(314,184); //328,193);
            break;
        case 8:
            robots.at(robot)->set_position(549,38); // 552,23);
            break;
        case 9:
            robots.at(robot)->set_position(278,42); //276,40);
            break;
        default:
            break;
    }

    MainWindow::scene->clear();
    imagen.load(":/new/icons/resources/pista-nueva.png", "png", NULL);
    imagen=imagen.scaled(593,225,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    scene->addPixmap(imagen);

    for(int i=0; i<NUMBER_OF_VACIOS; i++)
        scene->addRect(robots.at(i)->give_position(), robots.at(i)->give_aspect());
}


void MainWindow::display_datagram_content(int robot, bool forged)
{
    sac_datagram *pdatagram;

    if (forged)
        pdatagram=&forged_datagram;
    else
        pdatagram=&robots.at(robot)->last_datagram_received;

    QTableWidgetItem *pos_tabledata = new QTableWidgetItem;
    QTableWidgetItem *speed_tabledata = new QTableWidgetItem;
    QTableWidgetItem *exit_tabledata = new QTableWidgetItem;

    QString tmp;

    tmp.setNum(pdatagram->gotoexit);
    ui->tb_goto->setText(tmp);
    tmp.setNum(pdatagram->pos);
    ui->tb_pos->setText(tmp);
    tmp.setNum(pdatagram->dst);
    ui->tb_receiver->setText(tmp);
    tmp.setNum(pdatagram->src);
    ui->tb_sender->setText(tmp);
    tmp.setNum(pdatagram->vel);
    ui->tb_speed->setText(tmp);
    tmp.setNum(pdatagram->type);
    ui->tb_type->setText(tmp);

    if (pdatagram->type==0)
    {
        //Table Position
        tmp.setNum(pdatagram->pos, 10);
        pos_tabledata->setText(tmp);
        ui->tblrobot->setItem(pdatagram->src-1, 1, pos_tabledata);

        //Table Speed
        tmp.setNum(pdatagram->vel,10);
        speed_tabledata->setText(tmp);
        ui->tblrobot->setItem(pdatagram->src-1, 2, speed_tabledata);

        //Table Exit
        tmp.setNum(pdatagram->gotoexit,10);
        exit_tabledata->setText(tmp);
        ui->tblrobot->setItem(pdatagram->src-1, 3, exit_tabledata);

        emit change_scene_pos_signal(pdatagram->src-1,pdatagram->pos);
    }
}

void MainWindow::on_btnSendDgram_clicked()
{
    forged_datagram.src  = ui->spnSender->value();
    forged_datagram.dst  = ui->spnReceiver->value();
    forged_datagram.type = ui->spnType->value();
    forged_datagram.pos  = ui->spnPos->value();
    forged_datagram.vel  = ui->spnSpeed->value();
    forged_datagram.gotoexit = ui->spnGoto->value();

    emit datagram_in_struct(ui->spnSender->value(), true);
}

void MainWindow::process_hb(QString alived)
{
    bool ok;

    robots.at(alived.toInt(&ok,10)-1)->last_hb_received = QDateTime::currentDateTime();
    robots.at(alived.toInt(&ok,10)-1)->hb_count++;
}

void MainWindow::refresh_table()
{
    QDateTime now = QDateTime::currentDateTime();
    QList<QTableWidgetItem*> status_cell;
    QList<QTableWidgetItem*> hbcount_cell;
    QList<QTableWidgetItem*> lasthb_cell;

    //QString t;
    QString tmp;

    //qDebug("Refrescando tabla");

    for(int i=0; i<NUMBER_OF_VACIOS; i++)
    {
        status_cell.append(new QTableWidgetItem);
        hbcount_cell.append(new QTableWidgetItem);
        lasthb_cell.append(new QTableWidgetItem);

        tmp.setNum(robots.at(i)->last_hb_received.secsTo(now));

        if (robots.at(i)->last_hb_received.secsTo(now) < 300) status_cell.at(i)->setText("Alive");
        else status_cell.at(i)->setText("Gone");
        if (robots.at(i)->last_hb_received.daysTo(now) > 365) status_cell.at(i)->setText("ND");
        ui->tblrobot->setItem(i, 0, status_cell.at(i));
        status_cell.at(i)->setForeground(Qt::white);

        if (i==0) status_cell.at(i)->setBackground(Qt::red);
        if (i==1) status_cell.at(i)->setBackground(Qt::green);
        if (i==2) status_cell.at(i)->setBackground(Qt::blue);

        tmp.setNum(robots.at(i)->hb_count);
        hbcount_cell.at(i)->setText(tmp);
        ui->tblrobot->setItem(i, 4, hbcount_cell.at(i));

        tmp=robots.at(i)->last_hb_received.toString("hh:mm:ss");
        lasthb_cell.at(i)->setText(tmp);
        ui->tblrobot->setItem(i, 5, lasthb_cell.at(i));
    }
}

void MainWindow::packet_to_datagram(QString packet)
{
    int paquete[4];
    qint64 x;
    bool ok;

    int robot;

    ui->statusBar->showMessage(packet, 10000);

    x = packet.toLongLong(&ok, 16);

    paquete[3]=x & 0xff;
    paquete[2]=(x & 0xff00) >> 8;
    paquete[1]=(x & 0xff0000) >> 16;
    paquete[0]=(x & 0x7f000000) >> 24;

    robot=(paquete[0]&0x70) >> 4;

    if (robot>=3) robot=2; //Arreglar el id que manda el robot

    robots.at(robot)->last_datagram_received.src=robot;
    robots.at(robot)->last_datagram_received.dst=(paquete[0]&0x0E) >> 1;
    robots.at(robot)->last_datagram_received.type=(paquete[1]&0x20) >> 5;
    robots.at(robot)->last_datagram_received.pos=(paquete[1]&0x1E) >> 1;
    robots.at(robot)->last_datagram_received.vel=(paquete[2]&0x30) >> 4;
    robots.at(robot)->last_datagram_received.gotoexit=(paquete[2]&0x0E) >> 1;

    robots.at(robot-1)->last_hb_received = QDateTime::currentDateTime();

    emit datagram_in_struct(robot, false);

 }

void MainWindow::on_btnRadioReset_clicked()
{
    ui->statusBar->showMessage(tr("Resetting radio"),10000);
    emit write_serial_port("i");
}

void MainWindow::on_btnTestComm_clicked()
{
    ui->lstcomm->clear();
}


void MainWindow::on_pushButton_4_clicked() // Arriba
{
    emit Motorcommand("f", "0");
}

void MainWindow::on_pushButton_5_clicked() // Abajo
{
    emit Motorcommand("b", "0");
}

void MainWindow::on_pushButton_6_clicked() // Parar
{
    emit Motorcommand("s", "0");
}

void MainWindow::on_pushButton_7_clicked() // Derecha
{
    emit Motorcommand("s", "1");
}

void MainWindow::on_pushButton_8_clicked() // Izquierda
{
    emit Motorcommand("s", "2");
}

void MainWindow::on_pushButton_9_clicked() // Arriba derecha
{
    emit Motorcommand("f", "1");
}

void MainWindow::on_pushButton_10_clicked() // Abajo derecha
{
    emit Motorcommand("b", "1");
}

void MainWindow::on_pushButton_11_clicked() // Abajo izquierda
{
    emit Motorcommand("b", "2");
}

void MainWindow::on_pushButton_12_clicked() // Arriba izquierda
{
    emit Motorcommand("f", "2");
}

void MainWindow::sendMotorcommand(QString mov, QString dir)
{
    QString Motormessage;
    /*
      Manual motor control data format:
       mTMSD (To, Movement (b/f/s), Speed, Direction(0/1/2))
    */

    Motormessage.append('m');
    Motormessage.append(ui->comboBox_4->itemText(ui->comboBox_4->currentIndex()));
    Motormessage.append(mov);
    Motormessage.append(ui->comboBox_6->itemText(ui->comboBox_6->currentIndex()));
    Motormessage.append(dir);

    qDebug("Escribiendo motor");

    emit write_serial_port(Motormessage);

}

void MainWindow::on_comboBox_4_currentIndexChanged(int)
{
    if (ui->comboBox_6->currentIndex() > 0 && ui->comboBox_4->currentIndex() > 0)
    {
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_6->setEnabled(true);
        ui->pushButton_7->setEnabled(true);
        ui->pushButton_8->setEnabled(true);
        ui->pushButton_9->setEnabled(true);
        ui->pushButton_10->setEnabled(true);
        ui->pushButton_11->setEnabled(true);
        ui->pushButton_12->setEnabled(true);
    }
    else
    {
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
        ui->pushButton_7->setEnabled(false);
        ui->pushButton_8->setEnabled(false);
        ui->pushButton_9->setEnabled(false);
        ui->pushButton_10->setEnabled(false);
        ui->pushButton_11->setEnabled(false);
        ui->pushButton_12->setEnabled(false);
    }
}

void MainWindow::on_comboBox_6_activated(QString )
{
    if (ui->comboBox_6->currentIndex() > 0 && ui->comboBox_4->currentIndex() > 0)
    {
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_6->setEnabled(true);
        ui->pushButton_7->setEnabled(true);
        ui->pushButton_8->setEnabled(true);
        ui->pushButton_9->setEnabled(true);
        ui->pushButton_10->setEnabled(true);
        ui->pushButton_11->setEnabled(true);
        ui->pushButton_12->setEnabled(true);
    }
    else
    {
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
        ui->pushButton_7->setEnabled(false);
        ui->pushButton_8->setEnabled(false);
        ui->pushButton_9->setEnabled(false);
        ui->pushButton_10->setEnabled(false);
        ui->pushButton_11->setEnabled(false);
        ui->pushButton_12->setEnabled(false);
    }

}

void MainWindow::on_comboBox_activated(QString )
{
    if (ui->comboBox->currentIndex() > 0 && ui->comboBox_2->currentIndex() > 0 && ui->comboBox_3->currentIndex() > 0 )
        ui->pushButton_2->setEnabled(true);
    else
        ui->pushButton_2->setEnabled(false);

}

void MainWindow::on_comboBox_2_activated(QString )
{
    if (ui->comboBox->currentIndex() > 0 && ui->comboBox_2->currentIndex() > 0 && ui->comboBox_3->currentIndex() > 0 )
        ui->pushButton_2->setEnabled(true);
    else
        ui->pushButton_2->setEnabled(false);
}

void MainWindow::on_comboBox_3_activated(QString )
{
    if (ui->comboBox->currentIndex() > 0 && ui->comboBox_2->currentIndex() > 0 && ui->comboBox_3->currentIndex() > 0 )
        ui->pushButton_2->setEnabled(true);
    else
        ui->pushButton_2->setEnabled(false);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString Remotemessage;
    QString dest;
    char a, *b;
    b=&a;
    /*
      Manual motor control data format:
       mTMSD (To, Movement (b/f/s), Speed, Direction(0/1/2))
    */

    if (ui->comboBox->itemText(ui->comboBox->currentIndex())=="All")
    {
        for (int i=0; i<3; i++)
        {
            dest.clear();
            a=i+48;
            dest.fromAscii(b,1);
            Remotemessage.append('r');
            Remotemessage.append(dest);
            Remotemessage.append(ui->comboBox_2->itemText(ui->comboBox_2->currentIndex()));
            Remotemessage.append(ui->comboBox_3->itemText(ui->comboBox_3->currentIndex()));
            sleep(3);
        }
    }
    else
    {
        Remotemessage.append('r');
        Remotemessage.append(ui->comboBox->itemText(ui->comboBox->currentIndex()));
        Remotemessage.append(ui->comboBox_2->itemText(ui->comboBox_2->currentIndex()));
        Remotemessage.append(ui->comboBox_3->itemText(ui->comboBox_3->currentIndex()));
    }

    qDebug("Escribiendo remote");

    emit write_serial_port(Remotemessage);
}
