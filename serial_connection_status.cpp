#include "serial_connection_status.h"

bool serial_connection_status::status_ = false;
QString serial_connection_status::port_ = QString("--");
QString serial_connection_status::baudR = QString("--");
QString serial_connection_status::dataB = QString("--");
QString serial_connection_status::Parity = QString("--");
QString serial_connection_status::stopB = QString("--");
QString serial_connection_status::flowCtrl = QString("--");

serial_connection_status::serial_connection_status()
{
//    this->status_ = false;
//    this->port_ = QString("--");
//    this->baudR = QString("--");
//    this->dataB = QString("--");
//    this->Parity = QString("--");
//    this->stopB = QString("--");
//    this->flowCtrl = QString("--");
}

//void serial_connection_status::setConnection(QString com_, QString baudR_,
//                                    QString dataB_, QString Parity_,
//                                     QString stopB_, QString flowCtrl_)
//{
//    serial_connection_status::status_ = true;
//    serial_connection_status::port_ = com_;
//    serial_connection_status::baudR = baudR_;
//    serial_connection_status::dataB = dataB_;
//    serial_connection_status::Parity = Parity_;
//    serial_connection_status::stopB = stopB_;
//    serial_connection_status::flowCtrl = flowCtrl_;
//}

void serial_connection_status::resetConnection()
{
    serial_connection_status::status_ = false;
    serial_connection_status::port_ = QString("--");
    serial_connection_status::baudR = QString("--");
    serial_connection_status::dataB = QString("--");
    serial_connection_status::Parity = QString("--");
    serial_connection_status::stopB = QString("--");
    serial_connection_status::flowCtrl = QString("--");
}
