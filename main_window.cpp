#include "main_window.h"
#include "ui_mainwindow.h"
#include <iostream>
#include<QLabel>
#include<QPicture>
#include<QGridLayout>
using namespace std;

main_window::main_window(QWidget *parent):QMainWindow(parent)
{
    this->setBackgroundRole(QPalette::Dark);
    this->setAutoFillBackground(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setFocusPolicy(Qt::StrongFocus);
    this->setMinimumSize(250,300);
    this->setWindowTitle(QString("Drone Control Panel"));
//    logo
    this->logo = new QLabel(this);
    QString pic_path = QString("D:/UTCN/master/an2/sem2/individual/programare/motorsTestPanel/logo1.png");
    QPixmap pic = QPixmap(pic_path);
    pic = pic.scaled(100,100,Qt::KeepAspectRatio);
    this->logo->setPixmap(pic);
    this->setWindowIcon(QIcon(pic_path));

//    main widget
    this->mainWidget = new QLabel(this);
    this->setCentralWidget(this->mainWidget);

//    push buttons
    this->buttonMTP = new QPushButton("motor test panel", this);
    connect(this->buttonMTP,SIGNAL(clicked()),this,SLOT(bMTP_slot()));

    this->buttonCOM = new QPushButton("communication", this);
    connect(this->buttonCOM,SIGNAL(clicked()),this,SLOT(bCOM_slot()));

    this->buttonACC = new QPushButton("accelerometer", this);
    connect(this->buttonACC,SIGNAL(clicked()),this,SLOT(bACC_slot()));

    this->buttonGYRO = new QPushButton("gyroscope", this);
    this->buttonMAG = new QPushButton("magnetometer", this);
    this->buttonGPS = new QPushButton("GPS", this);
    this->buttonSFU = new QPushButton("attitude estimation", this);
    this->buttonBMS = new QPushButton("battery management", this);

//    main box layout
    QBoxLayout *bl = new QBoxLayout(QBoxLayout::TopToBottom);
    bl->insertWidget(1,this->logo);
    bl->setAlignment(this->logo, Qt::AlignCenter);

//    grid layout
    QGridLayout *gl = new QGridLayout();
    gl->addWidget(this->buttonMTP,1,1);
    gl->addWidget(this->buttonCOM,1,2);
    gl->addWidget(this->buttonACC,2,1);
    gl->addWidget(this->buttonGYRO,2,2);
    gl->addWidget(this->buttonMAG,3,1);
    gl->addWidget(this->buttonGPS,3,2);
    gl->addWidget(this->buttonSFU,4,1);
    gl->addWidget(this->buttonBMS,4,2);

    bl->insertLayout(2,gl);
    this->mainWidget->setLayout(bl);

//    this->setGeometry(3,3,100,100);
}

void main_window::closeEvent(QCloseEvent *event)
{
    if (!this->buttonMTP->isEnabled())
    {
        this->motorTestPanel->close();
    }

    if (!this->buttonACC->isEnabled())
    {
        this->accPanel->close();
    }

    if (!this->buttonCOM->isEnabled())
    {
        this->comPanel->close();
    }

    cout<<"DCP: good bye!"<<endl;
//    delete this;
}

void main_window::bMTP_slot()
{
    this->motorTestPanel = new gd_plot();
    this->motorTestPanel->show();
    this->buttonMTP->setEnabled(false);
    connect(this->motorTestPanel, SIGNAL(destroyed()),this, SLOT(treat_mtp_closing()));

    if (!this->buttonCOM->isEnabled())
    {
        connect(this->comPanel, SIGNAL(is_disconnected()),this->motorTestPanel,
            SLOT(DISCONNslot()));
        connect(this->motorTestPanel,SIGNAL(strReady(QString)),this->comPanel,
                SLOT(sendCommands(QString)));
    }
}

void main_window::bACC_slot()
{
    this->accPanel = new gd_chart();
    this->accPanel->show();
    this->buttonACC->setEnabled(false);
    connect(this->accPanel, SIGNAL(destroyed()),this, SLOT(treat_acc_closing()));
}

void main_window::bCOM_slot()
{
    this->comPanel = new sComDialog();
    this->comPanel->show();
    this->buttonCOM->setEnabled(false);
    connect(this->comPanel, SIGNAL(destroyed()),this, SLOT(treat_com_closing()));
    if (!this->buttonMTP->isEnabled())
    {
        connect(this->comPanel, SIGNAL(is_disconnected()),this->motorTestPanel,
            SLOT(DISCONNslot()));
        connect(this->motorTestPanel,SIGNAL(strReady(QString)),this->comPanel,
                SLOT(sendCommands(QString)));
    }
}

void main_window::treat_mtp_closing()
{
    cout<<"mtp has been destroyed"<<endl<<(int)this->motorTestPanel<<endl;
    this->buttonMTP->setEnabled(true);
}

void main_window::treat_acc_closing()
{
    cout<<"acc has been destroyed"<<endl<<(int)this->accPanel<<endl;
    this->buttonACC->setEnabled(true);
}

void main_window::treat_com_closing()
{
    cout<<"com has been destroyed"<<endl<<(int)this->comPanel<<endl;
    this->buttonCOM->setEnabled(true);
}

main_window::~main_window()
{
    delete this->motorTestPanel;
}
