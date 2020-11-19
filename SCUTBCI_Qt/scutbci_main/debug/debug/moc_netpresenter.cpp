/****************************************************************************
** Meta object code from reading C++ file 'netpresenter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../netpresenter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'netpresenter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NetPresenter_t {
    QByteArrayData data[16];
    char stringdata0[177];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetPresenter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetPresenter_t qt_meta_stringdata_NetPresenter = {
    {
QT_MOC_LITERAL(0, 0, 12), // "NetPresenter"
QT_MOC_LITERAL(1, 13, 14), // "stimulusnumber"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 3), // "num"
QT_MOC_LITERAL(4, 33, 5), // "error"
QT_MOC_LITERAL(5, 39, 7), // "errorno"
QT_MOC_LITERAL(6, 47, 8), // "errorstr"
QT_MOC_LITERAL(7, 56, 21), // "on_btnConnect_clicked"
QT_MOC_LITERAL(8, 78, 18), // "on_btnHide_clicked"
QT_MOC_LITERAL(9, 97, 18), // "on_btnSend_clicked"
QT_MOC_LITERAL(10, 116, 11), // "onConnected"
QT_MOC_LITERAL(11, 128, 14), // "onDisconnected"
QT_MOC_LITERAL(12, 143, 7), // "onError"
QT_MOC_LITERAL(13, 151, 10), // "onReceived"
QT_MOC_LITERAL(14, 162, 9), // "IOBuffer*"
QT_MOC_LITERAL(15, 172, 4) // "buff"

    },
    "NetPresenter\0stimulusnumber\0\0num\0error\0"
    "errorno\0errorstr\0on_btnConnect_clicked\0"
    "on_btnHide_clicked\0on_btnSend_clicked\0"
    "onConnected\0onDisconnected\0onError\0"
    "onReceived\0IOBuffer*\0buff"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetPresenter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    2,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   67,    2, 0x08 /* Private */,
       8,    0,   68,    2, 0x08 /* Private */,
       9,    0,   69,    2, 0x08 /* Private */,
      10,    0,   70,    2, 0x08 /* Private */,
      11,    0,   71,    2, 0x08 /* Private */,
      12,    2,   72,    2, 0x08 /* Private */,
      13,    1,   77,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    5,    6,
    QMetaType::Void, 0x80000000 | 14,   15,

       0        // eod
};

void NetPresenter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NetPresenter *_t = static_cast<NetPresenter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stimulusnumber((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->error((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->on_btnConnect_clicked(); break;
        case 3: _t->on_btnHide_clicked(); break;
        case 4: _t->on_btnSend_clicked(); break;
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
            typedef void (NetPresenter::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NetPresenter::stimulusnumber)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (NetPresenter::*_t)(int , const QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NetPresenter::error)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject NetPresenter::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NetPresenter.data,
      qt_meta_data_NetPresenter,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *NetPresenter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetPresenter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NetPresenter.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int NetPresenter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void NetPresenter::stimulusnumber(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NetPresenter::error(int _t1, const QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
