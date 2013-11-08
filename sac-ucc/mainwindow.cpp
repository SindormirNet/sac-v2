#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    int i;

    setWindowTitle("Central Control Unit Client 0.1");

    ui->setupUi(this);

    ui->btnConnect->setEnabled(false);
    ui->btnDisconnect->setEnabled(true);
    ui->pushButton->setEnabled(true);

    scene = new QGraphicsScene(QRect(0, 0, 0, 0));
    view = new QGraphicsView(ui->centralWidget);

    imagen.load("/home/syvic/pista.png", "png", NULL);
    scene->addPixmap(imagen);

    view->setGeometry(QRect(230, 10, 605, 247));
    view->setScene(scene);

    pdatagram.src=0;
    pdatagram.dst=0;
    pdatagram.type=0;
    pdatagram.vel=0;
    pdatagram.pos=0;
    pdatagram.gotoexit=0;

    ui->statusBar->showMessage(tr("CCU Client 0.1 Ready"),10000);
    view->show();
}


MainWindow::~MainWindow()
{
    emit close_serial_port();
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->statusBar->showMessage(tr("Setting up device to Listen Mode"),10000);
    emit write_serial_port("d");
}

void MainWindow::on_btnConnect_clicked()
{
    emit open_serial_port();
    ui->statusBar->showMessage(tr("Connected!"),10000);
    ui->btnConnect->setEnabled(false);
    ui->btnDisconnect->setEnabled(true);
    ui->pushButton->setEnabled(true);
}

void MainWindow::on_btnDisconnect_clicked()
{
    emit close_serial_port();
    ui->statusBar->showMessage(tr("Disconnected"),10000);
    ui->btnConnect->setEnabled(true);
    ui->btnDisconnect->setEnabled(false);
    ui->pushButton->setEnabled(false);
}

void MainWindow::DisplayString( QString string )
{

    QDateTime hora = QDateTime::currentDateTime();
    QString t;
    t=hora.toString( "hh:mm:ss:zzz " );

    if (string.size() > 0)
    {
        switch (string.at(1).toAscii())
        {
            case 'p':
                    ui->lstcomm->addItem(t + string);
                    ui->lstcomm->item(ui->lstcomm->count()-1)->setForeground(Qt::blue);
                    ui->pktcounter->display(ui->pktcounter->value()+1);
                    emit decode_datagram(string); //Por hacer
                    emit display_datagram_content();
                    break;
            case 'w':
                    ui->lstcomm->addItem(t + "TX Reset");
                    ui->lstcomm->item(ui->lstcomm->count()-1)->setBackground(Qt::yellow);
                    break;
            case 'x':
                    if (string.at(2)=='N')
                    {
                        ui->lstcomm->addItem(t + "NACK");
                        ui->lstcomm->item(ui->lstcomm->count()-1)->setForeground(Qt::red);
                    }
                    if (string.at(2)=='A')
                    {
                        ui->lstcomm->addItem(t + "ACK");
                        ui->lstcomm->item(ui->lstcomm->count()-1)->setForeground(Qt::green);
                    }
                    if (string.at(2)=='R')
                    {
                        ui->lstcomm->addItem(t + "RX Error");
                        ui->lstcomm->item(ui->lstcomm->count()-1)->setBackground(Qt::red);
                    }
        }
        ui->lstcomm->setCurrentRow(ui->lstcomm->count()-1);
    }
}

void MainWindow::change_scene_pos(int robot, int pos)
{
    QRectF *ppos;
    QPen *paspect;

    switch (robot)
    {
        case 0:
            paspect=&aspect_vacio1;
            ppos=&pos_vacio1;
            paspect->setBrush(QBrush(QColor(255,0,0)));
            break;
        case 1:
            paspect=&aspect_vacio2;
            ppos=&pos_vacio2;
            paspect->setBrush(QBrush(QColor(0,255,0)));
            break;
        case 2:
            paspect=&aspect_vacio3;
            ppos=&pos_vacio3;
            paspect->setBrush(QBrush(QColor(0,0,255)));
            break;
    }

    ppos->setCoords(20,20,25,25);
    paspect->setWidth(25);

    switch (pos)
    {
        case 0:
            ppos->moveCenter(QPointF(577,128));
            break;
        case 1:
            ppos->moveCenter(QPointF(492,31));
            break;
        case 2:
            ppos->moveCenter(QPointF(303,84));
            break;
        case 3:
            ppos->moveCenter(QPointF(160,46));
            break;
        case 4:
            ppos->moveCenter(QPointF(21,122));
            break;
        case 5:
            ppos->moveCenter(QPointF(141,211));
            break;
        case 6:
            ppos->moveCenter(QPointF(304,147));
            break;
        case 7:
            ppos->moveCenter(QPointF(478,215));
            break;
        default:
            break;
    }

    MainWindow::scene->clear();
    imagen.load("/home/syvic/pista.png", "png", NULL);
    scene->addPixmap(imagen);

    scene->addRect(pos_vacio1, aspect_vacio1);
    scene->addRect(pos_vacio2, aspect_vacio2);
    scene->addRect(pos_vacio3, aspect_vacio3);
}


void MainWindow::display_datagram_content()
{

    QTableWidgetItem *pos_tabledata = new QTableWidgetItem;
    QTableWidgetItem *speed_tabledata = new QTableWidgetItem;
    QTableWidgetItem *exit_tabledata = new QTableWidgetItem;

    QString tmp;

    tmp.setNum(pdatagram.gotoexit);
    ui->tb_goto->setText(tmp);
    tmp.setNum(pdatagram.pos);
    ui->tb_pos->setText(tmp);
    tmp.setNum(pdatagram.dst);
    ui->tb_receiver->setText(tmp);
    tmp.setNum(pdatagram.src);
    ui->tb_sender->setText(tmp);
    tmp.setNum(pdatagram.vel);
    ui->tb_speed->setText(tmp);
    tmp.setNum(pdatagram.type);
    ui->tb_type->setText(tmp);

    //Table Position
    tmp.setNum(pdatagram.pos, 10);
    pos_tabledata->setText(tmp);
    ui->tblrobot->setItem(pdatagram.src, 1, pos_tabledata);

    //Table Speed
    tmp.setNum(pdatagram.vel,10);
    speed_tabledata->setText(tmp);
    ui->tblrobot->setItem(pdatagram.src, 2, speed_tabledata);

    //Table Exit
    tmp.setNum(pdatagram.gotoexit,10);
    exit_tabledata->setText(tmp);
    ui->tblrobot->setItem(pdatagram.src, 3, exit_tabledata);

    emit change_scene_pos_signal(pdatagram.src,pdatagram.pos);
}



void MainWindow::on_spnSender_valueChanged(int )
{
    pdatagram.src = ui->spnSender->value();
}

void MainWindow::on_spnReceiver_valueChanged(int )
{
    pdatagram.dst = ui->spnReceiver->value();
}

void MainWindow::on_spnType_valueChanged(int )
{
    pdatagram.type = ui->spnType->value();
}

void MainWindow::on_spnPos_valueChanged(int )
{
    pdatagram.pos = ui->spnPos->value();
}

void MainWindow::on_spnSpeed_valueChanged(int )
{
    pdatagram.vel = ui->spnSpeed->value();
}

void MainWindow::on_spnGoto_valueChanged(int )
{
    pdatagram.gotoexit = ui->spnGoto->value();
}

void MainWindow::on_btnSendDgram_clicked()
{
    emit datagram_in_struct();
}


int MainWindow::calcula_paridad_byte(int mybyte)
{
        int i;
        int count=0;

        for (i=1; i<8; i++)
                if (mybyte & (0x01 << i)) count++;

        return (count&0x01);
}

void MainWindow::packet_to_datagram(QString packet)
{
    int paquete[4];
    qint64 x;
    bool ok;

    qDebug("El paquete recibido es ");

    packet.remove(0,2);
    packet.truncate(8);


    ui->statusBar->showMessage(packet, 10000);

    //x = strtoll(packet, NULL, 16);

    x = packet.toLongLong(&ok, 16);

    paquete[3]=x & 0xff;
    paquete[2]=(x & 0xff00) >> 8;
    paquete[1]=(x & 0xff0000) >> 16;
    paquete[0]=(x & 0x7f000000) >> 24;

    pdatagram.src=(paquete[0]&0x70) >> 4;
    pdatagram.dst=(paquete[0]&0x0E) >> 1;
    pdatagram.type=(paquete[1]&0x20) >> 5;
    pdatagram.pos=(paquete[1]&0x1E) >> 1;
    pdatagram.vel=(paquete[2]&0x30) >> 4;
    pdatagram.gotoexit=(paquete[2]&0x0E) >> 1;

 }


