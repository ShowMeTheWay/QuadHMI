#ifndef SERIAL_CONN_INFO_H
#define SERIAL_CONN_INFO_H
#include<QString>

class serial_conn_info
{
public:
    serial_conn_info();
    QString baude;
    QString data_bits;
    QString parity;
    QString stop_bits;
    QString flow_ctrl;
    QString com;
    QString statusStr;
};

#endif // SERIAL_CONN_INFO_H
