/****************************************************************************
** Meta object code from reading C++ file 'network_server.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../server/network_server.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'network_server.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSNetworkServerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSNetworkServerENDCLASS = QtMocHelpers::stringData(
    "NetworkServer",
    "clientConnected",
    "",
    "client_id",
    "ip",
    "port",
    "clientDisconnected",
    "dataReceived",
    "data_type",
    "content",
    "time",
    "logMessage",
    "message",
    "serverStateChanged",
    "is_running",
    "onNewConnection",
    "onReadyRead",
    "onClientDisconnected",
    "startAllClients",
    "stopAllClients",
    "setThresholds",
    "critical_bandwidth",
    "critical_latency",
    "critical_packet_loss",
    "critical_cpu_usage",
    "critical_memory_usage"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSNetworkServerENDCLASS_t {
    uint offsetsAndSizes[52];
    char stringdata0[14];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[10];
    char stringdata4[3];
    char stringdata5[5];
    char stringdata6[19];
    char stringdata7[13];
    char stringdata8[10];
    char stringdata9[8];
    char stringdata10[5];
    char stringdata11[11];
    char stringdata12[8];
    char stringdata13[19];
    char stringdata14[11];
    char stringdata15[16];
    char stringdata16[12];
    char stringdata17[21];
    char stringdata18[16];
    char stringdata19[15];
    char stringdata20[14];
    char stringdata21[19];
    char stringdata22[17];
    char stringdata23[21];
    char stringdata24[19];
    char stringdata25[22];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSNetworkServerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSNetworkServerENDCLASS_t qt_meta_stringdata_CLASSNetworkServerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 13),  // "NetworkServer"
        QT_MOC_LITERAL(14, 15),  // "clientConnected"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 9),  // "client_id"
        QT_MOC_LITERAL(41, 2),  // "ip"
        QT_MOC_LITERAL(44, 4),  // "port"
        QT_MOC_LITERAL(49, 18),  // "clientDisconnected"
        QT_MOC_LITERAL(68, 12),  // "dataReceived"
        QT_MOC_LITERAL(81, 9),  // "data_type"
        QT_MOC_LITERAL(91, 7),  // "content"
        QT_MOC_LITERAL(99, 4),  // "time"
        QT_MOC_LITERAL(104, 10),  // "logMessage"
        QT_MOC_LITERAL(115, 7),  // "message"
        QT_MOC_LITERAL(123, 18),  // "serverStateChanged"
        QT_MOC_LITERAL(142, 10),  // "is_running"
        QT_MOC_LITERAL(153, 15),  // "onNewConnection"
        QT_MOC_LITERAL(169, 11),  // "onReadyRead"
        QT_MOC_LITERAL(181, 20),  // "onClientDisconnected"
        QT_MOC_LITERAL(202, 15),  // "startAllClients"
        QT_MOC_LITERAL(218, 14),  // "stopAllClients"
        QT_MOC_LITERAL(233, 13),  // "setThresholds"
        QT_MOC_LITERAL(247, 18),  // "critical_bandwidth"
        QT_MOC_LITERAL(266, 16),  // "critical_latency"
        QT_MOC_LITERAL(283, 20),  // "critical_packet_loss"
        QT_MOC_LITERAL(304, 18),  // "critical_cpu_usage"
        QT_MOC_LITERAL(323, 21)   // "critical_memory_usage"
    },
    "NetworkServer",
    "clientConnected",
    "",
    "client_id",
    "ip",
    "port",
    "clientDisconnected",
    "dataReceived",
    "data_type",
    "content",
    "time",
    "logMessage",
    "message",
    "serverStateChanged",
    "is_running",
    "onNewConnection",
    "onReadyRead",
    "onClientDisconnected",
    "startAllClients",
    "stopAllClients",
    "setThresholds",
    "critical_bandwidth",
    "critical_latency",
    "critical_packet_loss",
    "critical_cpu_usage",
    "critical_memory_usage"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSNetworkServerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    3,   80,    2, 0x06,    1 /* Public */,
       6,    1,   87,    2, 0x06,    5 /* Public */,
       7,    4,   90,    2, 0x06,    7 /* Public */,
      11,    1,   99,    2, 0x06,   12 /* Public */,
      13,    1,  102,    2, 0x06,   14 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      15,    0,  105,    2, 0x08,   16 /* Private */,
      16,    0,  106,    2, 0x08,   17 /* Private */,
      17,    0,  107,    2, 0x08,   18 /* Private */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      18,    0,  108,    2, 0x02,   19 /* Public */,
      19,    0,  109,    2, 0x02,   20 /* Public */,
      20,    5,  110,    2, 0x02,   21 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::UShort,    3,    4,    5,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QDateTime,    3,    8,    9,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::Bool,   14,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int, QMetaType::Int,   21,   22,   23,   24,   25,

       0        // eod
};

Q_CONSTINIT const QMetaObject NetworkServer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSNetworkServerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSNetworkServerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSNetworkServerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<NetworkServer, std::true_type>,
        // method 'clientConnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint16, std::false_type>,
        // method 'clientDisconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'dataReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QDateTime &, std::false_type>,
        // method 'logMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'serverStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onNewConnection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onReadyRead'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onClientDisconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startAllClients'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stopAllClients'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setThresholds'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void NetworkServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NetworkServer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->clientConnected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<quint16>>(_a[3]))); break;
        case 1: _t->clientDisconnected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->dataReceived((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QDateTime>>(_a[4]))); break;
        case 3: _t->logMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->serverStateChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->onNewConnection(); break;
        case 6: _t->onReadyRead(); break;
        case 7: _t->onClientDisconnected(); break;
        case 8: _t->startAllClients(); break;
        case 9: _t->stopAllClients(); break;
        case 10: _t->setThresholds((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NetworkServer::*)(int , const QString & , quint16 );
            if (_t _q_method = &NetworkServer::clientConnected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NetworkServer::*)(int );
            if (_t _q_method = &NetworkServer::clientDisconnected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NetworkServer::*)(int , const QString & , const QString & , const QDateTime & );
            if (_t _q_method = &NetworkServer::dataReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (NetworkServer::*)(const QString & );
            if (_t _q_method = &NetworkServer::logMessage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (NetworkServer::*)(bool );
            if (_t _q_method = &NetworkServer::serverStateChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *NetworkServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSNetworkServerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NetworkServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void NetworkServer::clientConnected(int _t1, const QString & _t2, quint16 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NetworkServer::clientDisconnected(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NetworkServer::dataReceived(int _t1, const QString & _t2, const QString & _t3, const QDateTime & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void NetworkServer::logMessage(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void NetworkServer::serverStateChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
