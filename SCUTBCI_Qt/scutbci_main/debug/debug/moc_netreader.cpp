/****************************************************************************
** Meta object code from reading C++ file 'netreader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../netreader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'netreader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NetReader_t {
    QByteArrayData data[13];
    char stringdata0[176];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetReader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetReader_t qt_meta_stringdata_NetReader = {
    {
QT_MOC_LITERAL(0, 0, 9), // "NetReader"
QT_MOC_LITERAL(1, 10, 21), // "on_btnConnect_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 18), // "on_btnHide_clicked"
QT_MOC_LITERAL(4, 52, 28), // "on_spinDuration_valueChanged"
QT_MOC_LITERAL(5, 81, 4), // "arg1"
QT_MOC_LITERAL(6, 86, 25), // "on_spinScale_valueChanged"
QT_MOC_LITERAL(7, 112, 11), // "onConnected"
QT_MOC_LITERAL(8, 124, 14), // "onDisconnected"
QT_MOC_LITERAL(9, 139, 9), // "onCtrlMsg"
QT_MOC_LITERAL(10, 149, 11), // "AmpMessage*"
QT_MOC_LITERAL(11, 161, 4), // "pMsg"
QT_MOC_LITERAL(12, 166, 9) // "onDataMsg"

    },
    "NetReader\0on_btnConnect_clicked\0\0"
    "on_btnHide_clicked\0on_spinDuration_valueChanged\0"
    "arg1\0on_spinScale_valueChanged\0"
    "onConnected\0onDisconnected\0onCtrlMsg\0"
    "AmpMessage*\0pMsg\0onDataMsg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetReader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    1,   56,    2, 0x08 /* Private */,
       6,    1,   59,    2, 0x08 /* Private */,
       7,    0,   62,    2, 0x08 /* Private */,
       8,    0,   63,    2, 0x08 /* Private */,
       9,    1,   64,    2, 0x08 /* Private */,
      12,    1,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,

       0        // eod
};

void NetReader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NetReader *_t = static_cast<NetReader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnConnect_clicked(); break;
        case 1: _t->on_btnHide_clicked(); break;
        case 2: _t->on_spinDuration_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_spinScale_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onConnected(); break;
        case 5: _t->onDisconnected(); break;
        case 6: _t->onCtrlMsg((*reinterpret_cast< AmpMessage*(*)>(_a[1]))); break;
        case 7: _t->onDataMsg((*reinterpret_cast< AmpMessage*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject NetReader::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NetReader.data,
      qt_meta_data_NetReader,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *NetReader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetReader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NetReader.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int NetReader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
