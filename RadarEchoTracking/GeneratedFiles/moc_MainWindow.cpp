/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../MainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MySlaveThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   15,   14,   14, 0x05,
      58,   50,   14,   14, 0x05,
      86,   14,   14,   14, 0x05,
     105,   15,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_MySlaveThread[] = {
    "MySlaveThread\0\0doneFile\0"
    "signal_TrackDone(QString)\0preFile\0"
    "signal_ToDeleteOld(QString)\0"
    "signal_StopTrack()\0signal_Replay(QString)\0"
};

void MySlaveThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MySlaveThread *_t = static_cast<MySlaveThread *>(_o);
        switch (_id) {
        case 0: _t->signal_TrackDone((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->signal_ToDeleteOld((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->signal_StopTrack(); break;
        case 3: _t->signal_Replay((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MySlaveThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MySlaveThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_MySlaveThread,
      qt_meta_data_MySlaveThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MySlaveThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MySlaveThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MySlaveThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MySlaveThread))
        return static_cast<void*>(const_cast< MySlaveThread*>(this));
    return QThread::qt_metacast(_clname);
}

int MySlaveThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MySlaveThread::signal_TrackDone(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MySlaveThread::signal_ToDeleteOld(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MySlaveThread::signal_StopTrack()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MySlaveThread::signal_Replay(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   12,   11,   11, 0x05,
      58,   48,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      97,   90,   11,   11, 0x0a,
     157,  128,   11,   11, 0x0a,
     221,  212,   11,   11, 0x0a,
     253,  245,   11,   11, 0x0a,
     279,   12,   11,   11, 0x0a,
     310,  304,   11,   11, 0x0a,
     332,  304,   11,   11, 0x0a,
     364,  304,   11,   11, 0x0a,
     398,  304,   11,   11, 0x0a,
     433,   11,   11,   11, 0x0a,
     450,   11,   11,   11, 0x0a,
     471,   11,   11,   11, 0x0a,
     489,   11,   11,   11, 0x0a,
     510,  212,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0fileBase\0signal_InsertFile(QString)\0"
    "fileNames\0signal_SelectFiles(QStringList)\0"
    "action\0slot_ActionTriggered(QAction*)\0"
    "fileList,strCubeName,pOutMap\0"
    "slot_TrecDone(QStringList&,QString&,P_TREC_NC_MAP_OUT)\0"
    "doneFile\0slot_TrackDone(QString)\0"
    "preFile\0slot_ToDeleteOld(QString)\0"
    "slot_InsertFile(QString)\0index\0"
    "slot_SelectLayer(int)\0"
    "slot_doubleClicked(QModelIndex)\0"
    "slot_NameListClicked(QModelIndex)\0"
    "slot_TrackListClicked(QModelIndex)\0"
    "slot_StopTrack()\0slot_DeleteBox(bool)\0"
    "slot_AddBox(bool)\0slot_ModifyBox(bool)\0"
    "slot_Replay(QString)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->signal_InsertFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->signal_SelectFiles((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 2: _t->slot_ActionTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 3: _t->slot_TrecDone((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< P_TREC_NC_MAP_OUT(*)>(_a[3]))); break;
        case 4: _t->slot_TrackDone((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->slot_ToDeleteOld((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->slot_InsertFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->slot_SelectLayer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->slot_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 9: _t->slot_NameListClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 10: _t->slot_TrackListClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 11: _t->slot_StopTrack(); break;
        case 12: _t->slot_DeleteBox((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->slot_AddBox((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->slot_ModifyBox((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->slot_Replay((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
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
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::signal_InsertFile(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::signal_SelectFiles(const QStringList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
