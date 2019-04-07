#ifndef SERIAL_CONNECTION_STATUS_H
#define SERIAL_CONNECTION_STATUS_H
#include<QString>

class serial_connection_status
{
public:
    serial_connection_status();
    static bool status_;
    static QString port_;
    static QString baudR;
    static QString dataB;
    static QString Parity;
    static QString stopB;
    static QString flowCtrl;

    static void resetConnection();
};

#endif // SERIAL_CONNECTION_STATUS_H
