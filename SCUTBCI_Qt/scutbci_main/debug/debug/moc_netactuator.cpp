/****************************************************************************
** Meta object code from reading C++ file 'netactuator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../netactuator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'netactuator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NetActuator_t {
    QByteArrayData data[10];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetActuator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetActuator_t qt_meta_stringdata_NetActuator = {
    {
QT_MOC_LITERAL(0, 0, 11), // "NetActuator"
QT_MOC_LITERAL(1, 12, 21), // "on_btnConnect_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 18), // "on_btnHide_clicked"
QT_MOC_LITERAL(4, 54, 18), // "on_btnSend_clicked"
QT_MOC_LITERAL(5, 73, 11), // "onConnected"
QT_MOC_LITERAL(6, 85, 14), // "onDisconnected"
QT_MOC_LITERAL(7, 100, 10), // "onReceived"
QT_MOC_LITERAL(8, 111, 9), // "IOBuffer*"
QT_MOC_LITERAL(9, 121, 4) // "buff"

    },
    "NetActuator\0on_btnConnect_clicked\0\0"
    "on_btnHide_clicked\0on_btnSend_clicked\0"
    "onConnected\0onDisconnected\0onReceived\0"
    "IOBuffer*\0buff"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetActuator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    1,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void NetActuator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NetActuator *_t = static_cast<NetActuator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnConnect_clicked(); break;
        case 1: _t->on_btnHide_clicked(); break;
        case 2: _t->on_btnSend_clicked(); break;
        case 3: _t->onConnected(); break;
        case 4: _t->onDisconnected(); break;
        case 5: _t->onReceived((*reinterpret_cast< IOBuffer*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< IOBuffer* >(); break;
            }
            break;
        }
    }
}

const QMetaObject NetActuator::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NetActuator.data,
      qt_meta_data_NetActuator,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *NetActuator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetActuator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NetActuator.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int NetActuator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
