#ifndef SCOMDIALOG_H
#define SCOMDIALOG_H

#include <QWidget>
#include<QDialog>
#include<QPlainTextEdit>
#include<QComboBox>
#include<QPushButton>
#include<QLabel>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QSpacerItem>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <QList>
#include"serial_connection_status.h"

class sComDialog : public QDialog
{
    Q_OBJECT
public:
    sComDialog(QWidget *parent = 0);
    struct Setari
    {
        QString comP;

//        QSerialPort::BaudRate baudRate;
        qint32 baudRate;
        QString strBaudeRate;

        QSerialPort::DataBits dataBits;
        QString strDataBits;

        QSerialPort::Parity parity_;
        QString strParity_;

        QSerialPort::StopBits stopBits;
        QString strStopBits;

        QSerialPort::FlowControl flowControl;
        QString strFlowControl;
    };

protected slots:
    void refreshB_SLOT();
    void conn_SLOT();
    void disconn_SLOT();
    void sSend_SLOT();
    void readTheSerial();
    void writeTheSerial(const QByteArray data);
    void sendCommands(QString strSummary);

signals:
    void is_disconnected();

protected:
    void loadActualParam();
    void closeSerialPort();
    int openSerialPort();
    void closeEvent(QCloseEvent *event);

private:
    QPlainTextEdit *s_console;
    QPlainTextEdit *su_console;
    QSerialPort *serialP;

    QComboBox *baude_cob;
    QComboBox *data_b_cob;
    QComboBox *pola_cob;
    QComboBox *stop_b_cob;
    QComboBox *flow_ctr_cob;
    QComboBox *com_cob;

    QLabel *baudL;
    QLabel *dataL;
    QLabel *polaL;
    QLabel *stopBL;
    QLabel *flowCL;
    QLabel *comL;

    QHBoxLayout *hl1;
    QHBoxLayout *hl2;
    QVBoxLayout *vl1;
    QVBoxLayout *vl2;
    QVBoxLayout *vl3;
    QVBoxLayout *vl4;
    QVBoxLayout *vl5;
    QVBoxLayout *vl6;

    QSpacerItem *spa;

    QPushButton *conn;
    QPushButton *disconn;
    QPushButton *sSend;
    QPushButton *refreshB;

    Setari actualParam;
    QLabel *statusL;
    QLabel *sentStatus;

    QByteArray dataS;
};

#endif // SCOMDIALOG_H
