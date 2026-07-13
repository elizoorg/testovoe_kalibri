/****************************************************************************
** Meta object code from reading C++ file 'server_window.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../server/server_window.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'server_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSServerWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSServerWindowENDCLASS = QtMocHelpers::stringData(
    "ServerWindow",
    "onToggleServer",
    "",
    "onStartClients",
    "onStopClients",
    "onOpenSettings",
    "onClientConnected",
    "client_id",
    "ip",
    "port",
    "onClientDisconnected",
    "onDataReceived",
    "data_type",
    "content",
    "time",
    "onLogMessage",
    "message",
    "onServerStateChanged",
    "is_running",
    "flushDataBuffer",
    "flushLogBuffer"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSServerWindowENDCLASS_t {
    uint offsetsAndSizes[42];
    char stringdata0[13];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[15];
    char stringdata4[14];
    char stringdata5[15];
    char stringdata6[18];
    char stringdata7[10];
    char stringdata8[3];
    char stringdata9[5];
    char stringdata10[21];
    char stringdata11[15];
    char stringdata12[10];
    char stringdata13[8];
    char stringdata14[5];
    char stringdata15[13];
    char stringdata16[8];
    char stringdata17[21];
    char stringdata18[11];
    char stringdata19[16];
    char stringdata20[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSServerWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSServerWindowENDCLASS_t qt_meta_stringdata_CLASSServerWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "ServerWindow"
        QT_MOC_LITERAL(13, 14),  // "onToggleServer"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 14),  // "onStartClients"
        QT_MOC_LITERAL(44, 13),  // "onStopClients"
        QT_MOC_LITERAL(58, 14),  // "onOpenSettings"
        QT_MOC_LITERAL(73, 17),  // "onClientConnected"
        QT_MOC_LITERAL(91, 9),  // "client_id"
        QT_MOC_LITERAL(101, 2),  // "ip"
        QT_MOC_LITERAL(104, 4),  // "port"
        QT_MOC_LITERAL(109, 20),  // "onClientDisconnected"
        QT_MOC_LITERAL(130, 14),  // "onDataReceived"
        QT_MOC_LITERAL(145, 9),  // "data_type"
        QT_MOC_LITERAL(155, 7),  // "content"
        QT_MOC_LITERAL(163, 4),  // "time"
        QT_MOC_LITERAL(168, 12),  // "onLogMessage"
        QT_MOC_LITERAL(181, 7),  // "message"
        QT_MOC_LITERAL(189, 20),  // "onServerStateChanged"
        QT_MOC_LITERAL(210, 10),  // "is_running"
        QT_MOC_LITERAL(221, 15),  // "flushDataBuffer"
        QT_MOC_LITERAL(237, 14)   // "flushLogBuffer"
    },
    "ServerWindow",
    "onToggleServer",
    "",
    "onStartClients",
    "onStopClients",
    "onOpenSettings",
    "onClientConnected",
    "client_id",
    "ip",
    "port",
    "onClientDisconnected",
    "onDataReceived",
    "data_type",
    "content",
    "time",
    "onLogMessage",
    "message",
    "onServerStateChanged",
    "is_running",
    "flushDataBuffer",
    "flushLogBuffer"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSServerWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x08,    1 /* Private */,
       3,    0,   81,    2, 0x08,    2 /* Private */,
       4,    0,   82,    2, 0x08,    3 /* Private */,
       5,    0,   83,    2, 0x08,    4 /* Private */,
       6,    3,   84,    2, 0x08,    5 /* Private */,
      10,    1,   91,    2, 0x08,    9 /* Private */,
      11,    4,   94,    2, 0x08,   11 /* Private */,
      15,    1,  103,    2, 0x08,   16 /* Private */,
      17,    1,  106,    2, 0x08,   18 /* Private */,
      19,    0,  109,    2, 0x08,   20 /* Private */,
      20,    0,  110,    2, 0x08,   21 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::UShort,    7,    8,    9,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QDateTime,    7,   12,   13,   14,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ServerWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSServerWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSServerWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSServerWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ServerWindow, std::true_type>,
        // method 'onToggleServer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onStartClients'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onStopClients'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onOpenSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onClientConnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint16, std::false_type>,
        // method 'onClientDisconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onDataReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QDateTime &, std::false_type>,
        // method 'onLogMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onServerStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'flushDataBuffer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'flushLogBuffer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ServerWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ServerWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onToggleServer(); break;
        case 1: _t->onStartClients(); break;
        case 2: _t->onStopClients(); break;
        case 3: _t->onOpenSettings(); break;
        case 4: _t->onClientConnected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<quint16>>(_a[3]))); break;
        case 5: _t->onClientDisconnected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->onDataReceived((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QDateTime>>(_a[4]))); break;
        case 7: _t->onLogMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->onServerStateChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 9: _t->flushDataBuffer(); break;
        case 10: _t->flushLogBuffer(); break;
        default: ;
        }
    }
}

const QMetaObject *ServerWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServerWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSServerWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ServerWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
