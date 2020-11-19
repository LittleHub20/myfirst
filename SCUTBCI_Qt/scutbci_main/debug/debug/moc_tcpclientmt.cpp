/****************************************************************************
** Meta object code from reading C++ file 'tcpclientmt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tcpclientmt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpclientmt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TCPWorker_t {
    QByteArrayData data[24];
    char stringdata0[219];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TCPWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TCPWorker_t qt_meta_stringdata_TCPWorker = {
    {
QT_MOC_LITERAL(0, 0, 9), // "TCPWorker"
QT_MOC_LITERAL(1, 10, 9), // "connected"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 12), // "disconnected"
QT_MOC_LITERAL(4, 34, 8), // "received"
QT_MOC_LITERAL(5, 43, 9), // "IOBuffer*"
QT_MOC_LITERAL(6, 53, 4), // "buff"
QT_MOC_LITERAL(7, 58, 4), // "sent"
QT_MOC_LITERAL(8, 63, 5), // "bytes"
QT_MOC_LITERAL(9, 69, 5), // "error"
QT_MOC_LITERAL(10, 75, 7), // "errorno"
QT_MOC_LITERAL(11, 83, 8), // "errorstr"
QT_MOC_LITERAL(12, 92, 9), // "onConnect"
QT_MOC_LITERAL(13, 102, 4), // "host"
QT_MOC_LITERAL(14, 107, 4), // "port"
QT_MOC_LITERAL(15, 112, 12), // "onDisconnect"
QT_MOC_LITERAL(16, 125, 6), // "onSend"
QT_MOC_LITERAL(17, 132, 4), // "data"
QT_MOC_LITERAL(18, 137, 11), // "onConnected"
QT_MOC_LITERAL(19, 149, 14), // "onDisconnected"
QT_MOC_LITERAL(20, 164, 10), // "onReceived"
QT_MOC_LITERAL(21, 175, 6), // "onSent"
QT_MOC_LITERAL(22, 182, 7), // "onError"
QT_MOC_LITERAL(23, 190, 28) // "QAbstractSocket::SocketError"

    },
    "TCPWorker\0connected\0\0disconnected\0"
    "received\0IOBuffer*\0buff\0sent\0bytes\0"
    "error\0errorno\0errorstr\0onConnect\0host\0"
    "port\0onDisconnect\0onSend\0data\0onConnected\0"
    "onDisconnected\0onReceived\0onSent\0"
    "onError\0QAbstractSocket::SocketError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TCPWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    0,   80,    2, 0x06 /* Public */,
       4,    1,   81,    2, 0x06 /* Public */,
       7,    1,   84,    2, 0x06 /* Public */,
       9,    2,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    2,   92,    2, 0x0a /* Public */,
      15,    0,   97,    2, 0x0a /* Public */,
      16,    1,   98,    2, 0x0a /* Public */,
      18,    0,  101,    2, 0x0a /* Public */,
      19,    0,  102,    2, 0x0a /* Public */,
      20,    0,  103,    2, 0x0a /* Public */,
      21,    1,  104,    2, 0x0a /* Public */,
      22,    1,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::Long,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   10,   11,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Long,   13,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void, 0x80000000 | 23,    2,

       0        // eod
};

void TCPWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TCPWorker *_t = static_cast<TCPWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->received((*reinterpret_cast< IOBuffer*(*)>(_a[1]))); break;
        case 3: _t->sent((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 4: _t->error((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->onConnect((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const long(*)>(_a[2]))); break;
        case 6: _t->onDisconnect(); break;
        case 7: _t->onSend((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 8: _t->onConnected(); break;
        case 9: _t->onDisconnected(); break;
        case 10: _t->onReceived(); break;
        case 11: _t->onSent((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 12: _t->onError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< IOBuffer* >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TCPWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TCPWorker::connected)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TCPWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TCPWorker::disconnected)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TCPWorker::*_t)(IOBuffer * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TCPWorker::received)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TCPWorker::*_t)(long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TCPWorker::sent)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (TCPWorker::*_t)(int , const QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TCPWorker::error)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject TCPWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TCPWorker.data,
      qt_meta_data_TCPWorker,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TCPWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TCPWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TCPWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TCPWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void TCPWorker::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TCPWorker::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TCPWorker::received(IOBuffer * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TCPWorker::sent(long _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TCPWorker::error(int _t1, const QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
struct qt_meta_stringdata_TCPClientMT_t {
    QByteArrayData data[15];
    char stringdata0[140];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TCPClientMT_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TCPClientMT_t qt_meta_stringdata_TCPClientMT = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TCPClientMT"
QT_MOC_LITERAL(1, 12, 9), // "doConnect"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 12), // "doDisconnect"
QT_MOC_LITERAL(4, 36, 6), // "doSend"
QT_MOC_LITERAL(5, 43, 11), // "const char*"
QT_MOC_LITERAL(6, 55, 11), // "onConnected"
QT_MOC_LITERAL(7, 67, 14), // "onDisconnected"
QT_MOC_LITERAL(8, 82, 10), // "onReceived"
QT_MOC_LITERAL(9, 93, 9), // "IOBuffer*"
QT_MOC_LITERAL(10, 103, 4), // "data"
QT_MOC_LITERAL(11, 108, 6), // "onSent"
QT_MOC_LITERAL(12, 115, 7), // "onError"
QT_MOC_LITERAL(13, 123, 7), // "errorno"
QT_MOC_LITERAL(14, 131, 8) // "errorstr"

    },
    "TCPClientMT\0doConnect\0\0doDisconnect\0"
    "doSend\0const char*\0onConnected\0"
    "onDisconnected\0onReceived\0IOBuffer*\0"
    "data\0onSent\0onError\0errorno\0errorstr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TCPClientMT[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       3,    0,   64,    2, 0x06 /* Public */,
       4,    2,   65,    2, 0x06 /* Public */,
       4,    1,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   73,    2, 0x0a /* Public */,
       7,    0,   74,    2, 0x0a /* Public */,
       8,    1,   75,    2, 0x0a /* Public */,
      11,    1,   78,    2, 0x0a /* Public */,
      12,    2,   81,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Long,    2,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Long,    2,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::Long,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   13,   14,

       0        // eod
};

void TCPClientMT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TCPClientMT *_t = static_cast<TCPClientMT *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->doConnect((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2]))); break;
        case 1: _t->doDisconnect(); break;
        case 2: _t->doSend((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2]))); break;
        case 3: _t->doSend((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->onConnected(); break;
        case 5: _t->onDisconnected(); break;
        case 6: _t->onReceived((*reinterpret_cast< IOBuffer*(*)>(_a[1]))); break;
        case 7: _t->onSent((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 8: _t->onError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
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
            typedef void (TCPClientMT::*_t)(QString , long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TCPClientMT::doConnect)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TCPClientMT::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TCPClientMT::doDisconnect)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TCPClientMT::*_t)(const char * , long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TCPClientMT::doSend)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TCPClientMT::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TCPClientMT::doSend)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject TCPClientMT::staticMetaObject = {
    { &SocketHandler::staticMetaObject, qt_meta_stringdata_TCPClientMT.data,
      qt_meta_data_TCPClientMT,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TCPClientMT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TCPClientMT::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TCPClientMT.stringdata0))
        return static_cast<void*>(this);
    return SocketHandler::qt_metacast(_clname);
}

int TCPClientMT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SocketHandler::qt_metacall(_c, _id, _a);
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
void TCPClientMT::doConnect(QString _t1, long _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TCPClientMT::doDisconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TCPClientMT::doSend(const char * _t1, long _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TCPClientMT::doSend(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
