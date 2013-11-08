/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Thu Jul 29 08:02:27 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      35,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      37,   32,   11,   11, 0x05,
      66,   63,   11,   11, 0x05,
     103,   93,   11,   11, 0x05,
     138,  136,   11,   11, 0x05,
     167,   11,   11,   11, 0x05,
     192,   11,   11,   11, 0x05,
     211,  136,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     241,   11,   11,   11, 0x08,
     267,   11,   11,   11, 0x08,
     300,   11,   11,   11, 0x08,
     333,   11,   11,   11, 0x08,
     364,   11,   11,   11, 0x08,
     397,   11,   11,   11, 0x08,
     424,   11,   11,   11, 0x08,
     451,   11,   11,   11, 0x08,
     484,  478,   11,   11, 0x08,
     523,   11,   11,   11, 0x08,
     549,   11,   11,   11, 0x08,
     575,   11,   11,   11, 0x08,
     601,   11,   11,   11, 0x08,
     627,   11,   11,   11, 0x08,
     653,   11,   11,   11, 0x08,
     679,   11,   11,   11, 0x08,
     704,   11,   11,   11, 0x08,
     731,   11,   11,   11, 0x08,
     757,   11,   11,   11, 0x08,
     784,   11,   11,   11, 0x08,
     808,  136,   11,   11, 0x08,
     834,  136,   11,   11, 0x08,
     869,   11,   11,   11, 0x08,
     897,   11,   11,   11, 0x08,
     924,  917,   11,   11, 0x0a,
     955,  947,   11,   11, 0x0a,
     989,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0close_serial_port()\0port\0"
    "open_serial_port(QString)\0in\0"
    "write_serial_port(QString)\0robot,pos\0"
    "change_scene_pos_signal(int,int)\0,\0"
    "datagram_in_struct(int,bool)\0"
    "decode_datagram(QString)\0decode_hb(QString)\0"
    "Motorcommand(QString,QString)\0"
    "on_pushButton_2_clicked()\0"
    "on_comboBox_3_activated(QString)\0"
    "on_comboBox_2_activated(QString)\0"
    "on_comboBox_activated(QString)\0"
    "on_comboBox_6_activated(QString)\0"
    "on_pushButton_10_clicked()\0"
    "on_pushButton_11_clicked()\0"
    "on_pushButton_12_clicked()\0index\0"
    "on_comboBox_4_currentIndexChanged(int)\0"
    "on_pushButton_7_clicked()\0"
    "on_pushButton_9_clicked()\0"
    "on_pushButton_8_clicked()\0"
    "on_pushButton_6_clicked()\0"
    "on_pushButton_5_clicked()\0"
    "on_pushButton_4_clicked()\0"
    "on_btnTestComm_clicked()\0"
    "on_btnRadioReset_clicked()\0"
    "on_btnSendDgram_clicked()\0"
    "on_btnDisconnect_clicked()\0"
    "on_btnConnect_clicked()\0"
    "change_scene_pos(int,int)\0"
    "display_datagram_content(int,bool)\0"
    "packet_to_datagram(QString)\0"
    "process_hb(QString)\0string\0"
    "DisplayString(QString)\0mov,dir\0"
    "sendMotorcommand(QString,QString)\0"
    "refresh_table()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: close_serial_port(); break;
        case 1: open_serial_port((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: write_serial_port((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: change_scene_pos_signal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: datagram_in_struct((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: decode_datagram((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: decode_hb((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: Motorcommand((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: on_pushButton_2_clicked(); break;
        case 9: on_comboBox_3_activated((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: on_comboBox_2_activated((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: on_comboBox_activated((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: on_comboBox_6_activated((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: on_pushButton_10_clicked(); break;
        case 14: on_pushButton_11_clicked(); break;
        case 15: on_pushButton_12_clicked(); break;
        case 16: on_comboBox_4_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: on_pushButton_7_clicked(); break;
        case 18: on_pushButton_9_clicked(); break;
        case 19: on_pushButton_8_clicked(); break;
        case 20: on_pushButton_6_clicked(); break;
        case 21: on_pushButton_5_clicked(); break;
        case 22: on_pushButton_4_clicked(); break;
        case 23: on_btnTestComm_clicked(); break;
        case 24: on_btnRadioReset_clicked(); break;
        case 25: on_btnSendDgram_clicked(); break;
        case 26: on_btnDisconnect_clicked(); break;
        case 27: on_btnConnect_clicked(); break;
        case 28: change_scene_pos((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 29: display_datagram_content((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 30: packet_to_datagram((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 31: process_hb((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 32: DisplayString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 33: sendMotorcommand((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 34: refresh_table(); break;
        default: ;
        }
        _id -= 35;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::close_serial_port()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MainWindow::open_serial_port(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::write_serial_port(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::change_scene_pos_signal(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::datagram_in_struct(int _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::decode_datagram(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MainWindow::decode_hb(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MainWindow::Motorcommand(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
