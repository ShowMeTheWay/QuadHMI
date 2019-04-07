#include "scomdialog.h"
//#include<QLabel>
#include<QMessageBox>
#include<QScrollBar>
#include<QTextCursor>
#include<iostream>

using namespace std;

sComDialog::sComDialog(QWidget *parent) : QDialog(parent)
{
    this->setBackgroundRole(QPalette::Dark);
    this->setAutoFillBackground(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setFocusPolicy(Qt::StrongFocus);

    this->setMinimumSize(350,550);
    this->setAttribute(Qt::WA_DeleteOnClose);

    this->setWindowTitle(QString("serial connection panel"));
//    logo
    QString pic_path = QString("D:/UTCN/master/an2/sem2/individual/programare/motorsTestPanel/logo1.png");
    this->setWindowIcon(QIcon(pic_path));

//    push buttons
    this->conn = new QPushButton("connect", this);
    connect(this->conn,SIGNAL(clicked()),this,
            SLOT(conn_SLOT()));
    this->disconn = new QPushButton("disconnect", this);
    connect(this->disconn,SIGNAL(clicked()),this,
            SLOT(disconn_SLOT()));
    this->disconn->setEnabled(false);
    this->sSend = new QPushButton("Send",this);
    connect(this->sSend,SIGNAL(clicked()),this,
            SLOT(sSend_SLOT()));
    this->sSend->setEnabled(false);

    this->refreshB = new QPushButton("refresh",this);
    connect(this->refreshB,SIGNAL(clicked()),this,
            SLOT(refreshB_SLOT()));


//    combo box
    this->baude_cob = new QComboBox(this);
    this->baude_cob->setInsertPolicy(QComboBox::NoInsert);
    this->baude_cob->addItem(QString("9600"),
                             QSerialPort::Baud9600);
    this->baude_cob->addItem(QString("19200"),
                             QSerialPort::Baud19200);
    this->baude_cob->addItem(QString("57600"),
                             QSerialPort::Baud57600);
    this->baude_cob->addItem(QString("115200"),
                             QSerialPort::Baud115200);

    this->data_b_cob = new QComboBox(this);
    this->data_b_cob->setInsertPolicy(QComboBox::NoInsert);
    this->data_b_cob->addItem(QString("8"),
                              QSerialPort::Data8);

    this->pola_cob = new QComboBox(this);
    this->pola_cob->setInsertPolicy(QComboBox::NoInsert);
    this->pola_cob->addItem(QString("None"),
                            QSerialPort::NoParity);

    this->stop_b_cob = new QComboBox(this);
    this->stop_b_cob->setInsertPolicy(QComboBox::NoInsert);
    this->stop_b_cob->addItem(QString("1"),QSerialPort::OneStop);

    this->flow_ctr_cob = new QComboBox(this);
    this->flow_ctr_cob->setInsertPolicy(QComboBox::NoInsert);
    this->flow_ctr_cob->addItem(QString("None"),
                                QSerialPort::NoFlowControl);

    this->com_cob = new QComboBox(this);
    this->com_cob->setInsertPolicy(QComboBox::NoInsert);
    this->com_cob->clear();
    QList<QSerialPortInfo> qli = QSerialPortInfo::availablePorts();
    foreach (QSerialPortInfo info, qli)
    {
        QStringList list;
        list << info.portName()
             << info.description()
             << info.manufacturer()
             << info.systemLocation();
        this->com_cob->addItem(list.first(), list);
    }

//    plain text edit
    this->s_console = new QPlainTextEdit(this);
    this->su_console = new QPlainTextEdit(this);

    QPalette p = this->s_console->palette();
    p.setColor(QPalette::Base, Qt::darkBlue);
    p.setColor(QPalette::Text, Qt::green);
    this->s_console->setPalette(p);
    this->s_console->setReadOnly(true);

    p = this->su_console->palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    this->su_console->setPalette(p);

//    labels
    this->baudL = new QLabel("BaudeRate");
    this->dataL = new QLabel("DataBits");
    this->polaL = new QLabel("Parity");
    this->stopBL = new QLabel("StopBits");
    this->flowCL = new QLabel("FlowCtrl");
    this->comL = new QLabel("COM");
    this->statusL = new QLabel("Status: not connected");
    this->sentStatus = new QLabel("--");


//    layouts
    this->hl1 = new QHBoxLayout();
    this->hl2 = new QHBoxLayout();
    this->vl1 = new QVBoxLayout();
    this->vl2 = new QVBoxLayout();
    this->vl3 = new QVBoxLayout();
    this->vl4 = new QVBoxLayout();
    this->vl5 = new QVBoxLayout();
    this->vl6 = new QVBoxLayout();

    this->spa = new QSpacerItem(1,45,QSizePolicy::Minimum,
                                QSizePolicy::Minimum);

    vl1->addWidget(baudL);
    vl1->addWidget(this->baude_cob);
    vl1->addWidget(dataL);
    vl1->addWidget(this->data_b_cob);

    vl2->addWidget(polaL);
    vl2->addWidget(this->pola_cob);
    vl2->addWidget(stopBL);
    vl2->addWidget(this->stop_b_cob);

    vl3->addWidget(flowCL);
    vl3->addWidget(this->flow_ctr_cob);
    vl3->addWidget(comL);
    vl3->addWidget(this->com_cob);

    vl4->addSpacerItem(spa);
    vl4->addWidget(this->refreshB);
    vl4->addWidget(this->conn);
    vl4->addWidget(this->disconn);
//    vl4->addSpacerItem(spa);

    hl1->addLayout(vl1);
    hl1->addLayout(vl2);
    hl1->addLayout(vl3);
    hl1->addLayout(vl4);

    hl2->addWidget(this->su_console);
    this->vl6->addWidget(this->sentStatus);
    this->vl6->addWidget(this->sSend);
    hl2->addLayout(this->vl6);

    vl5->addWidget(this->statusL);
    vl5->addWidget(this->s_console);
    vl5->addLayout(hl2);
    vl5->addLayout(hl1);

    this->setLayout(vl5);

//    serial port
    this->serialP = new QSerialPort(this);
    connect(this->serialP,SIGNAL(readyRead()),this,
            SLOT(readTheSerial()));
    this->dataS = QByteArray();
}

void sComDialog::readTheSerial()
{
    this->dataS = this->serialP->readAll();
//    QScrollBar *sb = new QScrollBar(
//                this->s_console->verticalScrollBar());
//    sb->setValue(sb->maximum());
    this->s_console->insertPlainText(QString(this->dataS));
    QTextCursor tc = this->s_console->textCursor();
    tc.movePosition(QTextCursor::End);
    this->s_console->setTextCursor(tc);
}

void sComDialog::writeTheSerial(const QByteArray data_)
{
    this->serialP->write(data_);
    this->su_console->clear();
    bool check_ = this->serialP->waitForBytesWritten(100);
    if (check_)
    {
        this->sentStatus->setText("OK: data sent!");
    }
    else
    {
        this->sentStatus->setText("NOK: data NOT sent");
    }
    QTextCursor tc = this->su_console->textCursor();
    tc.movePosition(QTextCursor::End);
    this->su_console->setTextCursor(tc);

}

void sComDialog::conn_SLOT()
{
//    load actual parameters
    this->loadActualParam();

//    open a serial connection
    if (this->openSerialPort())
    {
        this->conn->setEnabled(false);
        this->refreshB->setEnabled(false);
        this->sSend->setEnabled(true);
        this->disconn->setEnabled(true);

        serial_connection_status::status_ = true;
        serial_connection_status::baudR = this->actualParam.strBaudeRate;
        serial_connection_status::dataB = this->actualParam.strDataBits;
        serial_connection_status::Parity = this->actualParam.strParity_;
        serial_connection_status::stopB = this->actualParam.strStopBits;
        serial_connection_status::flowCtrl = this->actualParam.strFlowControl;
        serial_connection_status::port_ = this->actualParam.comP;
    }
}

void sComDialog::disconn_SLOT()
{
    this->disconn->setEnabled(false);
    this->sSend->setEnabled(false);
    this->sentStatus->setText("--");
    this->conn->setEnabled(true);
    this->refreshB->setEnabled(true);

//    close serial connection
    this->closeSerialPort();
    serial_connection_status::status_ = false;
    serial_connection_status::port_ = QString("--");
    serial_connection_status::baudR = QString("--");
    serial_connection_status::dataB = QString("--");
    serial_connection_status::Parity = QString("--");
    serial_connection_status::stopB = QString("--");
    serial_connection_status::flowCtrl = QString("--");
}

void sComDialog::sSend_SLOT()
{
    QByteArray ba = QByteArray();
    ba.append(this->su_console->toPlainText());
    this->writeTheSerial(ba);
}

void sComDialog::refreshB_SLOT()
{
    for (int i = 0; i<this->com_cob->count(); i++)
    {
        this->com_cob->removeItem(i);
    }

    QList<QSerialPortInfo> aP = QSerialPortInfo::availablePorts();

    foreach (QSerialPortInfo info, aP)
    {
        QStringList list;
        list << info.portName()
             << info.description()
             << info.manufacturer()
             << info.systemLocation();
        this->com_cob->addItem(list.first(), list);
    }
}

int sComDialog::openSerialPort()
{
    this->serialP->setPortName(this->actualParam.comP);

    if (this->serialP->open(QIODevice::ReadWrite))
    {
        if (   this->serialP->setBaudRate(this->actualParam.baudRate)
            && this->serialP->setDataBits(this->actualParam.dataBits)
            && this->serialP->setParity(this->actualParam.parity_)
            && this->serialP->setStopBits(this->actualParam.stopBits)
            && this->serialP->setFlowControl(this->actualParam.flowControl))
        {
            QString qs = QString(
                        tr("Status: connected to %1 : %2, %3, %4, %5, %6 ")
                                .arg(this->actualParam.comP)
                                .arg(this->actualParam.strBaudeRate)
                                .arg(this->actualParam.strDataBits)
                                .arg(this->actualParam.strParity_)
                                .arg(this->actualParam.strStopBits)
                                .arg(this->actualParam.strFlowControl));
            this->statusL->setText(qs);
            return 1;
        }
        else
        {
                this->serialP->close();
                QMessageBox::critical(this, "Error",
                                      this->serialP->errorString());

                this->statusL->setText("Open error");
                return 0;
        }
    }
    else
    {
        this->statusL->setText("Status: connections not available");
        return 0;
    }
}

void sComDialog::sendCommands(QString strSummary)
{
    this->su_console->clear();
    this->su_console->insertPlainText(strSummary);
    QByteArray ba = QByteArray();
    ba.append(QString(">"));
    ba.append(this->su_console->toPlainText());
    ba.append(QString("<"));
    this->writeTheSerial(ba);
}

void sComDialog::closeSerialPort()
{
    this->serialP->close();
    this->statusL->setText("Status: connection closed");
    serial_connection_status::resetConnection();
    emit is_disconnected();
}

void sComDialog::closeEvent(QCloseEvent *event)
{
    if (this->serialP->isOpen())
    {
        this->closeSerialPort();
    }

    cout<<"COM: good bye!"<<endl;
}

void sComDialog::loadActualParam()
{
//    get the com name
    this->actualParam.comP = this->com_cob->currentText();

//    get the baud rate
    this->actualParam.baudRate = (this->baude_cob->itemData(this->
             baude_cob->currentIndex()).toInt());
    this->actualParam.strBaudeRate = this->baude_cob->currentText();

//    get the data bits
    this->actualParam.dataBits = static_cast<QSerialPort::DataBits>
            (this->data_b_cob->itemData(this->
             data_b_cob->currentIndex()).toInt());
    this->actualParam.strDataBits = this->data_b_cob->currentText();

//    get the parity
    this->actualParam.parity_ = static_cast<QSerialPort::Parity>
            (this->pola_cob->itemData(this->
             pola_cob->currentIndex()).toInt());
    this->actualParam.strParity_ = this->pola_cob->currentText();

//    stop bits
    this->actualParam.stopBits = static_cast<QSerialPort::StopBits>
            (this->stop_b_cob->itemData(this->
             pola_cob->currentIndex()).toInt());
    this->actualParam.strStopBits = this->stop_b_cob->currentText();

//    get the flow ctrl
    this->actualParam.flowControl = static_cast<QSerialPort::FlowControl>
            (this->flow_ctr_cob->
             itemData(this->flow_ctr_cob->currentIndex()).toInt());
    this->actualParam.strFlowControl = this->
            flow_ctr_cob->currentText();

}


