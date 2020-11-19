/****************************************************************************
** Meta object code from reading C++ file 'amptransport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../amptransport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'amptransport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AmpTransport_t {
    QByteArrayData data[17];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AmpTransport_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AmpTransport_t qt_meta_stringdata_AmpTransport = {
    {
QT_MOC_LITERAL(0, 0, 12), // "AmpTransport"
QT_MOC_LITERAL(1, 13, 9), // "connected"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 12), // "disconnected"
QT_MOC_LITERAL(4, 37, 5), // "error"
QT_MOC_LITERAL(5, 43, 7), // "errorno"
QT_MOC_LITERAL(6, 51, 8), // "errorstr"
QT_MOC_LITERAL(7, 60, 10), // "ctrlpacket"
QT_MOC_LITERAL(8, 71, 11), // "AmpMessage*"
QT_MOC_LITERAL(9, 83, 4), // "pMsg"
QT_MOC_LITERAL(10, 88, 10), // "datapacket"
QT_MOC_LITERAL(11, 99, 11), // "onConnected"
QT_MOC_LITERAL(12, 111, 14), // "onDisconnected"
QT_MOC_LITERAL(13, 126, 7), // "onError"
QT_MOC_LITERAL(14, 134, 10), // "onReceived"
QT_MOC_LITERAL(15, 145, 9), // "IOBuffer*"
QT_MOC_LITERAL(16, 155, 4) // "buff"

    },
    "AmpTransport\0connected\0\0disconnected\0"
    "error\0errorno\0errorstr\0ctrlpacket\0"
    "AmpMessage*\0pMsg\0datapacket\0onConnected\0"
    "onDisconnected\0onError\0onReceived\0"
    "IOBuffer*\0buff"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AmpTransport[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    2,   61,    2, 0x06 /* Public */,
       7,    1,   66,    2, 0x06 /* Public */,
      10,    1,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   72,    2, 0x0a /* Public */,
      12,    0,   73,    2, 0x0a /* Public */,
      13,    2,   74,    2, 0x0a /* Public */,
      14,    1,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    5,    6,
    QMetaType::Void, 0x80000000 | 15,   16,

       0        // eod
};

void AmpTransport::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AmpTransport *_t = static_cast<AmpTransport *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->error((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->ctrlpacket((*reinterpret_cast< AmpMessage*(*)>(_a[1]))); break;
        case 4: _t->datapacket((*reinterpret_cast< AmpMessage*(*)>(_a[1]))); break;
        case 5: _t->onConnected(); break;
        case 6: _t->onDisconnected(); break;
        case 7: _t->onError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->onReceived((*reinterpret_cast< IOBuffer*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< IOBuffer* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AmpTransport::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AmpTransport::connected)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (AmpTransport::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AmpTransport::disconnected)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (AmpTransport::*_t)(int , const QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AmpTransport::error)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (AmpTransport::*_t)(AmpMessage * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AmpTransport::ctrlpacket)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (AmpTransport::*_t)(AmpMessage * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AmpTransport::datapacket)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject AmpTransport::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AmpTransport.data,
      qt_meta_data_AmpTransport,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AmpTransport::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AmpTransport::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AmpTransport.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AmpTransport::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void AmpTransport::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AmpTransport::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AmpTransport::error(int _t1, const QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AmpTransport::ctrlpacket(AmpMessage * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AmpTransport::datapacket(AmpMessage * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
