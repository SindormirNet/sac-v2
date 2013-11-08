/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Jul 29 08:02:18 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *lblStatus;
    QPushButton *btnConnect;
    QPushButton *btnDisconnect;
    QFrame *frame;
    QGroupBox *groupBox_2;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QPushButton *pushButton_2;
    QComboBox *comboBox_3;
    QLabel *label_17;
    QFrame *frame_2;
    QGroupBox *groupBox_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *tb_sender;
    QLineEdit *tb_receiver;
    QLineEdit *tb_type;
    QLineEdit *tb_speed;
    QLineEdit *tb_goto;
    QLabel *label_16;
    QLabel *label_4;
    QLineEdit *tb_pos;
    QFrame *frame_3;
    QGroupBox *groupBox_4;
    QTableWidget *tblrobot;
    QLabel *label_14;
    QFrame *frame_4;
    QFrame *frame_5;
    QGroupBox *groupBox_5;
    QLabel *label_7;
    QLabel *label_9;
    QLabel *label_12;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_8;
    QSpinBox *spnSender;
    QSpinBox *spnReceiver;
    QSpinBox *spnType;
    QSpinBox *spnPos;
    QSpinBox *spnSpeed;
    QSpinBox *spnGoto;
    QPushButton *btnSendDgram;
    QLabel *label_15;
    QFrame *frame_6;
    QGroupBox *groupBox;
    QListWidget *lstcomm;
    QLCDNumber *pktcounter;
    QLabel *label_13;
    QPushButton *btnTestComm;
    QFrame *frame_7;
    QGroupBox *groupBox_6;
    QPushButton *pushButton_12;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_11;
    QPushButton *pushButton_4;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QComboBox *comboBox_4;
    QLabel *label_18;
    QComboBox *comboBox_6;
    QComboBox *comboBox_5;
    QComboBox *cmbportselector;
    QFrame *frame_8;
    QGroupBox *groupBox_7;
    QPushButton *btnRadioReset;
    QLabel *label_20;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(1024, 430);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1024, 430));
        MainWindow->setMaximumSize(QSize(1024, 430));
        MainWindow->setAutoFillBackground(true);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lblStatus = new QLabel(centralWidget);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
        lblStatus->setGeometry(QRect(231, 30, 91, 20));
        btnConnect = new QPushButton(centralWidget);
        btnConnect->setObjectName(QString::fromUtf8("btnConnect"));
        btnConnect->setGeometry(QRect(160, 10, 28, 27));
        btnConnect->setStyleSheet(QString::fromUtf8("background-image: url(:/new/icons/resources/network-connect.png);"));
        btnDisconnect = new QPushButton(centralWidget);
        btnDisconnect->setObjectName(QString::fromUtf8("btnDisconnect"));
        btnDisconnect->setGeometry(QRect(190, 10, 28, 27));
        btnDisconnect->setStyleSheet(QString::fromUtf8("background-image: url(:/new/icons/resources/network-disconnect.png);"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(230, 340, 241, 61));
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 0, 241, 61));
        groupBox_2->setStyleSheet(QString::fromUtf8(""));
        groupBox_2->setFlat(false);
        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(10, 20, 61, 31));
        comboBox_2 = new QComboBox(groupBox_2);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(70, 20, 71, 31));
        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setEnabled(false);
        pushButton_2->setGeometry(QRect(190, 20, 41, 31));
        comboBox_3 = new QComboBox(groupBox_2);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(140, 20, 51, 31));
        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(0, 0, 251, 21));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_17->setFont(font);
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(230, 270, 241, 61));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        groupBox_3 = new QGroupBox(frame_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 0, 241, 61));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(16, 20, 51, 17));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 40, 62, 17));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(173, 20, 41, 17));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(95, 40, 51, 17));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(170, 40, 41, 17));
        tb_sender = new QLineEdit(groupBox_3);
        tb_sender->setObjectName(QString::fromUtf8("tb_sender"));
        tb_sender->setGeometry(QRect(65, 18, 31, 21));
        tb_sender->setReadOnly(true);
        tb_receiver = new QLineEdit(groupBox_3);
        tb_receiver->setObjectName(QString::fromUtf8("tb_receiver"));
        tb_receiver->setGeometry(QRect(65, 38, 31, 21));
        tb_receiver->setReadOnly(true);
        tb_type = new QLineEdit(groupBox_3);
        tb_type->setObjectName(QString::fromUtf8("tb_type"));
        tb_type->setGeometry(QRect(205, 18, 31, 21));
        tb_type->setReadOnly(true);
        tb_speed = new QLineEdit(groupBox_3);
        tb_speed->setObjectName(QString::fromUtf8("tb_speed"));
        tb_speed->setGeometry(QRect(140, 38, 31, 21));
        tb_speed->setReadOnly(true);
        tb_goto = new QLineEdit(groupBox_3);
        tb_goto->setObjectName(QString::fromUtf8("tb_goto"));
        tb_goto->setGeometry(QRect(205, 38, 31, 21));
        tb_goto->setReadOnly(true);
        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(0, 0, 191, 21));
        label_16->setFont(font);
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(111, 20, 31, 17));
        tb_pos = new QLineEdit(groupBox_3);
        tb_pos->setObjectName(QString::fromUtf8("tb_pos"));
        tb_pos->setGeometry(QRect(140, 18, 31, 21));
        tb_pos->setReadOnly(true);
        frame_3 = new QFrame(centralWidget);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(480, 270, 351, 131));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        groupBox_4 = new QGroupBox(frame_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(0, 0, 351, 131));
        tblrobot = new QTableWidget(groupBox_4);
        if (tblrobot->columnCount() < 6)
            tblrobot->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tblrobot->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tblrobot->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tblrobot->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tblrobot->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tblrobot->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tblrobot->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (tblrobot->rowCount() < 3)
            tblrobot->setRowCount(3);
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        QBrush brush1(QColor(255, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setBackground(brush1);
        __qtablewidgetitem6->setForeground(brush);
        tblrobot->setItem(0, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tblrobot->setItem(0, 4, __qtablewidgetitem7);
        QBrush brush2(QColor(0, 255, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setBackground(brush2);
        tblrobot->setItem(1, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tblrobot->setItem(1, 4, __qtablewidgetitem9);
        QBrush brush3(QColor(255, 255, 255, 255));
        brush3.setStyle(Qt::NoBrush);
        QBrush brush4(QColor(0, 0, 255, 255));
        brush4.setStyle(Qt::SolidPattern);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setBackground(brush4);
        __qtablewidgetitem10->setForeground(brush3);
        tblrobot->setItem(2, 0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tblrobot->setItem(2, 4, __qtablewidgetitem11);
        tblrobot->setObjectName(QString::fromUtf8("tblrobot"));
        tblrobot->setGeometry(QRect(10, 20, 341, 101));
        tblrobot->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tblrobot->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tblrobot->setAutoScroll(false);
        tblrobot->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tblrobot->setTabKeyNavigation(false);
        tblrobot->setProperty("showDropIndicator", QVariant(false));
        tblrobot->setDragDropOverwriteMode(false);
        tblrobot->setAlternatingRowColors(true);
        tblrobot->setSelectionMode(QAbstractItemView::NoSelection);
        tblrobot->setSelectionBehavior(QAbstractItemView::SelectRows);
        tblrobot->setRowCount(3);
        tblrobot->setColumnCount(6);
        tblrobot->horizontalHeader()->setCascadingSectionResizes(true);
        tblrobot->horizontalHeader()->setDefaultSectionSize(50);
        tblrobot->horizontalHeader()->setHighlightSections(false);
        tblrobot->horizontalHeader()->setMinimumSectionSize(50);
        tblrobot->horizontalHeader()->setStretchLastSection(true);
        tblrobot->verticalHeader()->setVisible(false);
        tblrobot->verticalHeader()->setDefaultSectionSize(25);
        tblrobot->verticalHeader()->setHighlightSections(false);
        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 0, 151, 21));
        label_14->setFont(font);
        frame_4 = new QFrame(centralWidget);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setGeometry(QRect(230, 10, 600, 242));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        frame_5 = new QFrame(centralWidget);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setGeometry(QRect(850, 10, 161, 241));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        groupBox_5 = new QGroupBox(frame_5);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(0, 0, 161, 241));
        label_7 = new QLabel(groupBox_5);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 35, 61, 17));
        label_9 = new QLabel(groupBox_5);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(9, 66, 71, 17));
        label_12 = new QLabel(groupBox_5);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(35, 96, 41, 17));
        label_10 = new QLabel(groupBox_5);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(42, 125, 41, 17));
        label_11 = new QLabel(groupBox_5);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(25, 155, 51, 17));
        label_8 = new QLabel(groupBox_5);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(34, 185, 41, 17));
        spnSender = new QSpinBox(groupBox_5);
        spnSender->setObjectName(QString::fromUtf8("spnSender"));
        spnSender->setGeometry(QRect(80, 30, 55, 27));
        spnSender->setMinimum(1);
        spnSender->setMaximum(3);
        spnSender->setValue(1);
        spnReceiver = new QSpinBox(groupBox_5);
        spnReceiver->setObjectName(QString::fromUtf8("spnReceiver"));
        spnReceiver->setGeometry(QRect(80, 60, 55, 27));
        spnType = new QSpinBox(groupBox_5);
        spnType->setObjectName(QString::fromUtf8("spnType"));
        spnType->setGeometry(QRect(80, 90, 55, 27));
        spnPos = new QSpinBox(groupBox_5);
        spnPos->setObjectName(QString::fromUtf8("spnPos"));
        spnPos->setGeometry(QRect(80, 120, 55, 27));
        spnSpeed = new QSpinBox(groupBox_5);
        spnSpeed->setObjectName(QString::fromUtf8("spnSpeed"));
        spnSpeed->setGeometry(QRect(80, 150, 55, 27));
        spnGoto = new QSpinBox(groupBox_5);
        spnGoto->setObjectName(QString::fromUtf8("spnGoto"));
        spnGoto->setGeometry(QRect(80, 180, 55, 27));
        btnSendDgram = new QPushButton(groupBox_5);
        btnSendDgram->setObjectName(QString::fromUtf8("btnSendDgram"));
        btnSendDgram->setGeometry(QRect(24, 210, 111, 27));
        label_15 = new QLabel(groupBox_5);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 6, 131, 20));
        label_15->setFont(font);
        frame_6 = new QFrame(centralWidget);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setGeometry(QRect(10, 40, 211, 291));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        groupBox = new QGroupBox(frame_6);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 211, 291));
        lstcomm = new QListWidget(groupBox);
        lstcomm->setObjectName(QString::fromUtf8("lstcomm"));
        lstcomm->setGeometry(QRect(10, 40, 191, 231));
        sizePolicy.setHeightForWidth(lstcomm->sizePolicy().hasHeightForWidth());
        lstcomm->setSizePolicy(sizePolicy);
        lstcomm->setAutoFillBackground(true);
        lstcomm->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        lstcomm->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        pktcounter = new QLCDNumber(groupBox);
        pktcounter->setObjectName(QString::fromUtf8("pktcounter"));
        pktcounter->setGeometry(QRect(140, 10, 41, 23));
        pktcounter->setFrameShape(QFrame::StyledPanel);
        pktcounter->setFrameShadow(QFrame::Raised);
        pktcounter->setNumDigits(4);
        pktcounter->setSegmentStyle(QLCDNumber::Flat);
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 10, 121, 21));
        label_13->setFont(font);
        btnTestComm = new QPushButton(groupBox);
        btnTestComm->setObjectName(QString::fromUtf8("btnTestComm"));
        btnTestComm->setGeometry(QRect(10, 267, 191, 20));
        frame_7 = new QFrame(centralWidget);
        frame_7->setObjectName(QString::fromUtf8("frame_7"));
        frame_7->setGeometry(QRect(850, 270, 161, 91));
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Raised);
        groupBox_6 = new QGroupBox(frame_7);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(0, 0, 161, 91));
        pushButton_12 = new QPushButton(groupBox_6);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setGeometry(QRect(10, 20, 21, 21));
        pushButton_12->setStyleSheet(QString::fromUtf8("background-image: url(:/new/icons/resources/arrow-up-left.png);"));
        pushButton_7 = new QPushButton(groupBox_6);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(50, 40, 21, 21));
        pushButton_7->setStyleSheet(QString::fromUtf8("background-image: url(:/new/icons/resources/arrow-right.png);"));
        pushButton_8 = new QPushButton(groupBox_6);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(10, 40, 21, 21));
        pushButton_8->setStyleSheet(QString::fromUtf8("background-image: url(:/new/icons/resources/arrow-left.png);"));
        pushButton_11 = new QPushButton(groupBox_6);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(10, 60, 21, 21));
        pushButton_11->setStyleSheet(QString::fromUtf8("background-image: url(:/new/icons/resources/arrow-down-left.png);"));
        pushButton_4 = new QPushButton(groupBox_6);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(30, 20, 21, 21));
        pushButton_4->setStyleSheet(QString::fromUtf8("background-image: url(:/new/icons/resources/arrow-up-double.png);"));
        pushButton_9 = new QPushButton(groupBox_6);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(50, 20, 21, 21));
        pushButton_9->setStyleSheet(QString::fromUtf8("background-image: url(:/new/icons/resources/arrow-up-right.png);"));
        pushButton_10 = new QPushButton(groupBox_6);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(50, 60, 21, 21));
        pushButton_10->setStyleSheet(QString::fromUtf8("background-image: url(:/new/icons/resources/arrow-down-right.png);"));
        pushButton_5 = new QPushButton(groupBox_6);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(30, 60, 21, 21));
        pushButton_5->setStyleSheet(QString::fromUtf8("background-image: url(:/new/icons/resources/arrow-down-double.png);"));
        pushButton_6 = new QPushButton(groupBox_6);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(30, 40, 21, 21));
        comboBox_4 = new QComboBox(groupBox_6);
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        comboBox_4->setGeometry(QRect(80, 50, 71, 31));
        label_18 = new QLabel(groupBox_6);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(10, 0, 101, 21));
        label_18->setFont(font);
        comboBox_6 = new QComboBox(groupBox_6);
        comboBox_6->setObjectName(QString::fromUtf8("comboBox_6"));
        comboBox_6->setGeometry(QRect(80, 20, 71, 31));
        comboBox_5 = new QComboBox(centralWidget);
        comboBox_5->setObjectName(QString::fromUtf8("comboBox_5"));
        comboBox_5->setGeometry(QRect(850, 370, 161, 31));
        cmbportselector = new QComboBox(centralWidget);
        cmbportselector->setObjectName(QString::fromUtf8("cmbportselector"));
        cmbportselector->setGeometry(QRect(10, 10, 141, 27));
        frame_8 = new QFrame(centralWidget);
        frame_8->setObjectName(QString::fromUtf8("frame_8"));
        frame_8->setGeometry(QRect(10, 340, 211, 61));
        frame_8->setFrameShape(QFrame::StyledPanel);
        frame_8->setFrameShadow(QFrame::Raised);
        groupBox_7 = new QGroupBox(frame_8);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(0, 0, 211, 61));
        btnRadioReset = new QPushButton(groupBox_7);
        btnRadioReset->setObjectName(QString::fromUtf8("btnRadioReset"));
        btnRadioReset->setGeometry(QRect(50, 20, 111, 31));
        btnRadioReset->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        label_20 = new QLabel(groupBox_7);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(8, 0, 101, 21));
        label_20->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Central Control Unit Client 0.1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        MainWindow->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        lblStatus->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnConnect->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btnConnect->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btnConnect->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_ACCESSIBILITY
        btnConnect->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        btnConnect->setText(QString());
        btnDisconnect->setText(QString());
        groupBox_2->setTitle(QString());
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Robot", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "all", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8)
        );
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Speed", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Min", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Med", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Max", 0, QApplication::UnicodeUTF8)
        );
        pushButton_2->setText(QApplication::translate("MainWindow", "Send!", 0, QApplication::UnicodeUTF8));
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8)
        );
        label_17->setText(QApplication::translate("MainWindow", " Send Remote Control Command", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QString());
        label->setText(QApplication::translate("MainWindow", "Sender:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Receiver:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Type:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Speed:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Goto:", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("MainWindow", " Last decoded datagram", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Pos:", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QString());
        QTableWidgetItem *___qtablewidgetitem = tblrobot->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Status", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tblrobot->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Pos", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tblrobot->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Speed", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tblrobot->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tblrobot->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "HB#", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tblrobot->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Last seen", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = tblrobot->isSortingEnabled();
        tblrobot->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem6 = tblrobot->item(0, 0);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "ND", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tblrobot->item(0, 4);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tblrobot->item(1, 0);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "ND", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tblrobot->item(1, 4);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tblrobot->item(2, 0);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "ND", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tblrobot->item(2, 4);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        tblrobot->setSortingEnabled(__sortingEnabled);

        label_14->setText(QApplication::translate("MainWindow", " Vehicle Status Table", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        frame_4->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        frame_4->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        frame_4->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_ACCESSIBILITY
        frame_4->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        groupBox_5->setTitle(QString());
        label_7->setText(QApplication::translate("MainWindow", "Sender:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Receiver:", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "Type:", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "Pos:", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "Speed:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Goto:", 0, QApplication::UnicodeUTF8));
        btnSendDgram->setText(QApplication::translate("MainWindow", "Emit!", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", " Datagram Forge", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        label_13->setText(QApplication::translate("MainWindow", "RCVD Datagrams", 0, QApplication::UnicodeUTF8));
        btnTestComm->setText(QApplication::translate("MainWindow", "Clear ", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QString());
        pushButton_12->setText(QString());
        pushButton_7->setText(QString());
        pushButton_8->setText(QString());
        pushButton_11->setText(QString());
        pushButton_4->setText(QString());
        pushButton_4->setShortcut(QApplication::translate("MainWindow", "Left", 0, QApplication::UnicodeUTF8));
        pushButton_9->setText(QString());
        pushButton_10->setText(QString());
        pushButton_5->setText(QString());
        pushButton_5->setShortcut(QApplication::translate("MainWindow", "Right", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("MainWindow", "X", 0, QApplication::UnicodeUTF8));
        pushButton_6->setShortcut(QApplication::translate("MainWindow", "Space", 0, QApplication::UnicodeUTF8));
        comboBox_4->clear();
        comboBox_4->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Robot", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8)
        );
        label_18->setText(QApplication::translate("MainWindow", "Motor control", 0, QApplication::UnicodeUTF8));
        comboBox_6->clear();
        comboBox_6->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Speed", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8)
        );
        comboBox_5->clear();
        comboBox_5->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Status Request", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8)
        );
        groupBox_7->setTitle(QString());
        btnRadioReset->setText(QApplication::translate("MainWindow", "Radio Reset", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("MainWindow", "Radio Control", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
