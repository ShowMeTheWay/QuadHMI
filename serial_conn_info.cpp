#include "serial_conn_info.h"

serial_conn_info::serial_conn_info()
{
    this->baude = QString("--");
    this->data_bits = QString("--");
    this->parity = QString("--");
    this->stop_bits = QString("--");
    this->flow_ctrl = QString("--");
    this->com = QString("--");
    this->statusStr = QString("not connected");
}
