#include "gd_plot.h"
#include<QtGui>
#include<cmath>
#include<QStylePainter>
#include<iostream>
#include<QGridLayout>
#include<iostream>

using namespace std;

gd_plot::gd_plot(QWidget *parent) : QWidget(parent)
{
    this->setBackgroundRole(QPalette::Dark);
    this->setAutoFillBackground(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setFocusPolicy(Qt::StrongFocus);

    this->setMinimumSize(650,550);
    this->setAttribute(Qt::WA_DeleteOnClose);

//    logo
    QString pic_path = QString("D:/UTCN/master/an2/sem2/individual/programare/motorsTestPanel/logo1.png");
    this->setWindowIcon(QIcon(pic_path));

//    pixelmap
    this->pixel_map = new QPixmap(this->size());

//    check box
    this->cb1 = new QCheckBox(this);
    this->cb1->show();
    connect(this->cb1,SIGNAL(stateChanged(int)),this,SLOT(M1_enable(int)));

    this->cb2 = new QCheckBox(this);
    this->cb2->show();
    connect(this->cb2,SIGNAL(stateChanged(int)),this,SLOT(M2_enable(int)));

    this->cb3 = new QCheckBox(this);
    this->cb3->show();
    connect(this->cb3,SIGNAL(stateChanged(int)),this,SLOT(M3_enable(int)));

    this->cb4 = new QCheckBox(this);
    this->cb4->show();
    connect(this->cb4,SIGNAL(stateChanged(int)),this,SLOT(M4_enable(int)));

//  general controls check boxes
    this->acb1 = new QCheckBox(this);
    this->acb1->setCheckable(false);
    this->acb1->show();
    connect(this->acb1,SIGNAL(stateChanged(int)),this,SLOT(AM1_check(int)));

    this->acb2 = new QCheckBox(this);
    this->acb2->setCheckable(false);
    this->acb2->show();
    connect(this->acb2,SIGNAL(stateChanged(int)),this,SLOT(AM2_check(int)));

    this->acb3 = new QCheckBox(this);
    this->acb3->setCheckable(false);
    this->acb3->show();
    connect(this->acb3,SIGNAL(stateChanged(int)),this,SLOT(AM3_check(int)));

    this->acb4 = new QCheckBox(this);
    this->acb4->setCheckable(false);
    this->acb4->show();
    connect(this->acb4,SIGNAL(stateChanged(int)),this,SLOT(AM4_check(int)));

    this->acb_sl = new QCheckBox(this);
    this->acb_sl->show();
    connect(this->acb_sl,SIGNAL(stateChanged(int)),this,SLOT(AM_SL_check(int)));

    connect(this->cb1,SIGNAL(stateChanged(int)),this,SLOT(updateStrSummary()));
    connect(this->cb2,SIGNAL(stateChanged(int)),this,SLOT(updateStrSummary()));
    connect(this->cb3,SIGNAL(stateChanged(int)),this,SLOT(updateStrSummary()));
    connect(this->cb4,SIGNAL(stateChanged(int)),this,SLOT(updateStrSummary()));

    connect(this->acb1,SIGNAL(stateChanged(int)),this,SLOT(updateStrSummary()));
    connect(this->acb2,SIGNAL(stateChanged(int)),this,SLOT(updateStrSummary()));
    connect(this->acb3,SIGNAL(stateChanged(int)),this,SLOT(updateStrSummary()));
    connect(this->acb4,SIGNAL(stateChanged(int)),this,SLOT(updateStrSummary()));

//    sliders
    this->sl1 = new QSlider(Qt::Vertical, this);
    this->sl1->setEnabled(false);
    this->sl1->show();
    this->sl1->setTickPosition(QSlider::TicksLeft);
    connect(this->sl1,SIGNAL(sliderReleased()),this,SLOT(setM1_ref()));

    this->sl2 = new QSlider(Qt::Vertical, this);
    this->sl2->setEnabled(false);
    this->sl2->show();
    this->sl2->setTickPosition(QSlider::TicksLeft);
    connect(this->sl2,SIGNAL(sliderReleased()),this,SLOT(setM2_ref()));

    this->sl3 = new QSlider(Qt::Vertical, this);
    this->sl3->setEnabled(false);
    this->sl3->show();
    this->sl3->setTickPosition(QSlider::TicksLeft);
    connect(this->sl3,SIGNAL(sliderReleased()),this,SLOT(setM3_ref()));

    this->sl4 = new QSlider(Qt::Vertical, this);
    this->sl4->setEnabled(false);
    this->sl4->show();
    this->sl4->setTickPosition(QSlider::TicksLeft);
    connect(this->sl4,SIGNAL(sliderReleased()),this,SLOT(setM4_ref()));

    this->asl = new QSlider(Qt::Vertical, this);
    this->asl->setEnabled(false);
    this->asl->show();
    this->asl->setTickPosition(QSlider::TicksLeft);
    connect(this->asl,SIGNAL(sliderReleased()),this,SLOT(setAM_ref()));

//    progress bars
    this->pb1 = new QProgressBar(this);
    this->pb1->setOrientation(Qt::Vertical);
    this->pb1->show();
    this->pb1->setValue(0);

    this->pb2 = new QProgressBar(this);
    this->pb2->setOrientation(Qt::Vertical);
    this->pb2->show();
    this->pb2->setValue(0);

    this->pb3 = new QProgressBar(this);
    this->pb3->setOrientation(Qt::Vertical);
    this->pb3->show();
    this->pb3->setValue(0);

    this->pb4 = new QProgressBar(this);
    this->pb4->setOrientation(Qt::Vertical);
    this->pb4->show();
    this->pb4->setValue(0);

    connect(this->pb1,SIGNAL(valueChanged(int)),this,SLOT(updateStrSummary()));
    connect(this->pb2,SIGNAL(valueChanged(int)),this,SLOT(updateStrSummary()));
    connect(this->pb3,SIGNAL(valueChanged(int)),this,SLOT(updateStrSummary()));
    connect(this->pb4,SIGNAL(valueChanged(int)),this,SLOT(updateStrSummary()));

//    this->strSummary = QString(tr("%1,%2,%3,%4,%5,%6,%7,%8") .arg(QString))

    this->apb = new QProgressBar(this);
    this->apb->setOrientation(Qt::Vertical);
    this->apb->setEnabled(false);
    this->apb->show();
    this->apb->setValue(0);

//    labels
    this->l1 = new QLabel(this);
    this->l1->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    this->l1->show();
    this->l1->setText(QString("--"));

    this->l2 = new QLabel(this);
    this->l2->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    this->l2->show();
    this->l2->setText(QString("--"));

    this->l3 = new QLabel(this);
    this->l3->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    this->l3->show();
    this->l3->setText(QString("--"));

    this->l4 = new QLabel(this);
    this->l4->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    this->l4->show();
    this->l4->setText(QString("--"));

    this->alla = new QLabel(this);
    this->alla->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    this->alla->show();
    this->alla->setText(QString("--"));

    this->baud_info = new QLabel(this);
//    this->baud_info->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    this->baud_info->show();
    this->baud_info->setText(QString("--"));

    this->dataB_info = new QLabel(this);
//    this->dataB_info->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    this->dataB_info->show();
    this->dataB_info->setText(QString("--"));

    this->pol_info = new QLabel(this);
//    this->pol_info->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    this->pol_info->show();
    this->pol_info->setText(QString("--"));

    this->sBits_info = new QLabel(this);
//    this->sBits_info->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    this->sBits_info->show();
    this->sBits_info->setText(QString("--"));

    this->flowCon_info = new QLabel(this);
//    this->flowCon_info->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    this->flowCon_info->show();
    this->flowCon_info->setText(QString("--"));

    this->com_info = new QLabel(this);
//    this->com_info->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    this->com_info->show();
    this->com_info->setText(QString("--"));


//    motor colors
    this->M1color = Qt::red;
    this->M2color = Qt::red;
    this->M3color = Qt::red;
    this->M4color = Qt::red;

//    serial color
    this->serialColor = Qt::white;

//    pushbuttons
    this->EMStop = new QPushButton("STOP",this);
    this->EMStop->show();
    connect(this->EMStop,SIGNAL(clicked()),this,SLOT(EMzero()));

    this->conn_ = new QPushButton("connect",this);
    this->conn_->show();
    connect(this->conn_,SIGNAL(clicked()),this,SLOT(CONNslot()));
//    this->conn_->setCheckable(true);

    this->disconn_ = new QPushButton("disconnect",this);
    this->disconn_->show();
    connect(this->disconn_,SIGNAL(clicked()),this,SLOT(DISCONNslot()));
    this->disconn_->setEnabled(false);

//    group box
    this->gb = new QGroupBox(QString("choose"),this);
    this->gb->setCheckable(true);
    this->gb->setChecked(false);

//    radio buttons
    this->auto_b = new QRadioButton(QString("auto"),this);
    this->man_b = new QRadioButton(QString("man"),this);
    this->man_b->setChecked(true);

    this->connInfoRect = QRect();

//    layouts
    QVBoxLayout *vl = new QVBoxLayout();
    vl->addWidget(this->auto_b);
    vl->addWidget(this->man_b);
    this->gb->setLayout(vl);

    this->serial_info = serial_conn_info();

    this->dist = min(this->height(),this->width());
    this->Ctr = QPoint(this->width()/2, this->height()/2);
//    this->connect->show();
//    this->disconnect = new QPushButton("Disconnect",this);
//    this->disconnect->show();

    this->is_conn = false;
    this->zomo_enabled = false;
    this->updateStrSummary();

    this->refreshPixmap();
}

gd_plot::~gd_plot()
{
    delete this->pixel_map;

    delete this->cb1;
    delete this->cb2;
    delete this->cb3;
    delete this->cb4;

    delete this->acb1;
    delete this->acb2;
    delete this->acb3;
    delete this->acb4;
    delete this->acb_sl;

    delete this->sl1;
    delete this->sl2;
    delete this->sl3;
    delete this->sl4;
    delete this->asl;

//    delete &(this->M1color);
//    delete &(this->M2color);
//    delete &(this->M3color);
//    delete &(this->M4color);

    delete this->pb1;
    delete this->pb2;
    delete this->pb3;
    delete this->pb4;
    delete this->apb;

    delete this->l1;
    delete this->l2;
    delete this->l3;
    delete this->l4;
    delete this->alla;

    delete this->baud_info;
    delete this->dataB_info;
    delete this->pol_info;
    delete this->sBits_info;
    delete this->flowCon_info;
    delete this->com_info;

    delete this->EMStop;
}

void gd_plot::updateStrSummary()
{
    int em1 = 0, em2 = 0, em3 = 0, em4 = 0;
    if ((this->cb1->isChecked()) || (this->acb1->isChecked()))
    {
        em1 = 1;
    }

    if ((this->cb2->isChecked()) || (this->acb2->isChecked()))
    {
        em2 = 1;
    }

    if ((this->cb3->isChecked()) || (this->acb3->isChecked()))
    {
        em3 = 1;
    }

    if ((this->cb4->isChecked()) || (this->acb4->isChecked()))
    {
        em4 = 1;
    }
//    form comma separated value (csv) string
    this->strSummary = QString::number(em1);
    this->strSummary.append(QString(","));
    this->strSummary.append(QString::number(em2));
    this->strSummary.append(QString(","));
    this->strSummary.append(QString::number(em3));
    this->strSummary.append(QString(","));
    this->strSummary.append(QString::number(em4));
    this->strSummary.append(QString(","));
    this->strSummary.append(QString::number(this->pb1->value()));
    this->strSummary.append(QString(","));
    this->strSummary.append(QString::number(this->pb2->value()));
    this->strSummary.append(QString(","));
    this->strSummary.append(QString::number(this->pb3->value()));
    this->strSummary.append(QString(","));
    this->strSummary.append(QString::number(this->pb4->value()));
    this->refreshPixmap();

    if (this->is_conn)
    {
        emit strReady(this->strSummary);
    }

}

void gd_plot::CONNslot()
{
    if (serial_connection_status::status_==true)
    {
        this->is_conn = true;
        this->serial_info.com = serial_connection_status::port_;
        this->serial_info.baude = serial_connection_status::baudR;
        this->serial_info.data_bits = serial_connection_status::dataB;
        this->serial_info.stop_bits = serial_connection_status::stopB;
        this->serial_info.parity = serial_connection_status::Parity;
        this->serial_info.flow_ctrl = serial_connection_status::flowCtrl;
        this->serial_info.statusStr = QString("connected");
        this->serialColor = Qt::green;

        this->conn_->setEnabled(false);
        this->disconn_->setEnabled(true);
    }
    this->refreshPixmap();
}

void gd_plot::DISCONNslot()
{
    this->is_conn = false;
    this->serial_info.com = QString("--");
    this->serial_info.baude = QString("--");
    this->serial_info.data_bits = QString("--");
    this->serial_info.stop_bits = QString("--");
    this->serial_info.parity = QString("--");
    this->serial_info.flow_ctrl = QString("--");
    this->serial_info.statusStr = QString("not connected");
    this->serialColor = Qt::white;

    this->conn_->setEnabled(true);
    this->disconn_->setEnabled(false);

    this->refreshPixmap();
}

void gd_plot::EMzero()
{
    this->acb_sl->setChecked(false);
    this->cb1->setChecked(false);
    this->cb2->setChecked(false);
    this->cb3->setChecked(false);
    this->cb4->setChecked(false);

//    this->refreshPixmap();
}

void gd_plot::M1_enable(int state)
{
    if (state == Qt::Unchecked)
    {
        this->sl1->setValue(0);
        this->pb1->setValue(0);
        this->l1->setText(QString("--"));
        this->sl1->setEnabled(false);
        this->M1color = Qt::red;
    }
    else
    {
        this->sl1->setEnabled(true);
        this->sl1->setValue(0);
        this->pb1->setValue(0);
        this->l1->setText(QString::number(0));
        this->M1color = Qt::green;
    }
    this->refreshPixmap();
}

void gd_plot::AM1_check(int state)
{
    if (state == Qt::Unchecked)
    {
        this->sl1->setEnabled(true);
        this->cb1->setEnabled(true);
        this->cb1->setChecked(false);
//        emit something
        this->sl1->setValue(0);
        this->pb1->setValue(0);
        this->l1->setText(QString("--"));
        this->sl1->setEnabled(false);
        this->M1color = Qt::red;
    }
    else
    {
        this->sl1->setEnabled(false);
        this->cb1->setEnabled(false);
        this->sl1->setValue(this->asl->value());
        this->pb1->setValue(this->asl->value());
        this->l1->setText(QString::number(this->asl->value()));
        this->M1color = Qt::cyan;
    }
    this->refreshPixmap();
}

void gd_plot::AM2_check(int state)
{
    if (state == Qt::Unchecked)
    {
        this->sl2->setEnabled(true);
        this->cb2->setEnabled(true);
        this->cb2->setChecked(false);
        this->sl2->setValue(0);
        this->pb2->setValue(0);
        this->l2->setText(QString("--"));
        this->sl2->setEnabled(false);
        this->M2color = Qt::red;
    }
    else
    {
        this->sl2->setEnabled(false);
        this->cb2->setEnabled(false);
        this->sl2->setValue(this->asl->value());
        this->pb2->setValue(this->asl->value());
        this->l2->setText(QString::number(this->asl->value()));
        this->M2color = Qt::cyan;
    }
    this->refreshPixmap();
}

void gd_plot::AM3_check(int state)
{
    if (state == Qt::Unchecked)
    {
        this->sl3->setEnabled(true);
        this->cb3->setEnabled(true);
        this->cb3->setChecked(false);
        this->sl3->setValue(0);
        this->pb3->setValue(0);
        this->l3->setText(QString("--"));
        this->sl3->setEnabled(false);
        this->M3color = Qt::red;
    }
    else
    {
        this->sl3->setEnabled(false);
        this->cb3->setEnabled(false);
        this->sl3->setValue(this->asl->value());
        this->pb3->setValue(this->asl->value());
        this->l3->setText(QString::number(this->asl->value()));
        this->M3color = Qt::cyan;
    }
    this->refreshPixmap();
}

void gd_plot::AM4_check(int state)
{
    if (state == Qt::Unchecked)
    {
        this->sl4->setEnabled(true);
        this->cb4->setEnabled(true);
        this->cb4->setChecked(false);
        this->sl4->setValue(0);
        this->pb4->setValue(0);
        this->l4->setText(QString("--"));
        this->sl4->setEnabled(false);
        this->M4color = Qt::red;
    }
    else
    {
        this->sl4->setEnabled(false);
        this->cb4->setEnabled(false);
        this->sl4->setValue(this->asl->value());
        this->pb4->setValue(this->asl->value());
        this->l4->setText(QString::number(this->asl->value()));
        this->M4color = Qt::cyan;;
    }
    this->refreshPixmap();
}

void gd_plot::AM_SL_check(int state)
{
    if (state == Qt::Unchecked)
    {
        this->asl->setValue(0);
        this->asl->setEnabled(false);

        this->apb->setValue(0);
        this->apb->setEnabled(false);

        this->alla->setText("--");

        this->acb1->setChecked(false);
        this->acb1->setCheckable(false);

        this->acb2->setChecked(false);
        this->acb2->setCheckable(false);

        this->acb3->setChecked(false);
        this->acb3->setCheckable(false);

        this->acb4->setChecked(false);
        this->acb4->setCheckable(false);
    }
    else
    {
        this->acb1->setCheckable(true);
        this->acb2->setCheckable(true);
        this->acb3->setCheckable(true);
        this->acb4->setCheckable(true);
        this->asl->setEnabled(true);
        this->apb->setEnabled(true);

        this->alla->setText(QString::number(this->asl->value()));

    }
    this->refreshPixmap();
}

void gd_plot::M2_enable(int state)
{
    if (state == Qt::Unchecked)
    {
        this->sl2->setValue(0);
        this->pb2->setValue(0);
        this->l2->setText(QString("--"));
        this->sl2->setEnabled(false);
        this->M2color = Qt::red;
    }
    else
    {
        this->sl2->setEnabled(true);
        this->sl2->setValue(10);
        this->pb2->setValue(10);
        this->l2->setText(QString::number(10));
        this->M2color = Qt::green;
    }
    this->refreshPixmap();
}

void gd_plot::M3_enable(int state)
{
    if (state == Qt::Unchecked)
    {
        this->sl3->setValue(0);
        this->pb3->setValue(0);
        this->l3->setText(QString("--"));
        this->sl3->setEnabled(false);
        this->M3color = Qt::red;
    }
    else
    {
        this->sl3->setEnabled(true);
        this->sl3->setValue(10);
        this->pb3->setValue(10);
        this->l3->setText(QString::number(10));
        this->M3color = Qt::green;
    }
    this->refreshPixmap();
}

void gd_plot::M4_enable(int state)
{
    if (state == Qt::Unchecked)
    {
        this->sl4->setValue(0);
        this->pb4->setValue(0);
        this->l4->setText(QString("--"));
        this->sl4->setEnabled(false);
        this->M4color = Qt::red;
    }
    else
    {
        this->sl4->setEnabled(true);
        this->sl4->setValue(10);
        this->pb4->setValue(10);
        this->l4->setText(QString::number(10));
        this->M4color = Qt::green;
    }
    this->refreshPixmap();
}

void gd_plot::closeEvent(QCloseEvent *event)
{
//    emit its_closing_here();
    cout<<"mtp: good bye!"<<endl;
//    event->ignore();
//    delete this;
}

void gd_plot::resizeEvent(QResizeEvent *event)
{
//    this->pixel_map.fill(Qt::black);
    delete this->pixel_map;
    this->pixel_map = new QPixmap(this->size());

//    this->dist = min(this->width(),this->height())*10/11;
    this->Ctr = QPoint(this->width()/2,this->height()/2);
    this->refreshPixmap();

//    this->refreshPixmap();
//    event->ignore();
}

void gd_plot::mousePressEvent(QMouseEvent *event)
{
    if (this->zomo_enabled)
    {
        this->cP = event->pos();
        this->shwCtr = this->Ctr;
    }
    else
        event->ignore();
}

void gd_plot::mouseMoveEvent(QMouseEvent *event)
{

    if (this->zomo_enabled)
    {
        QPointF ve = QPointF(event->pos().rx()-this->cP.rx(),
                             event->pos().ry()-this->cP.ry());
        this->Ctr = QPoint(ve.rx()+this->shwCtr.rx(),
                                     ve.ry()+this->shwCtr.ry());

        this->refreshPixmap();
    }
    else
        event->ignore();
}

void gd_plot::mouseReleaseEvent(QMouseEvent *event)
{
    event->ignore();
}

void gd_plot::wheelEvent(QWheelEvent *event)
{
//    event->ignore();
    if (this->zomo_enabled)
    {
        int l  = this->dist + event->angleDelta().ry()/8;
        if (l > 500)
        {
            this->dist = l;
            this->refreshPixmap();
        }
    }
    else
        event->ignore();
}

void gd_plot::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_R:
        {
            this->zomo_enabled = true;
        } break;
        case Qt::Key_T:
        {
            this->zomo_enabled = false;
        }break;
    case Qt::Key_C:
    {
        if (this->zomo_enabled)
        {
            this->dist = 500;
            this->Ctr = QPoint(this->width()/2,this->height()/2);
            this->refreshPixmap();
        }
    }break;
        default:
        {
            // some default
        }
    }

    this->refreshPixmap();
}

void gd_plot::setM1_ref()
{
    this->pb1->setValue(this->sl1->value());
    this->l1->setText(QString::number(this->sl1->value()));
}

void gd_plot::setM2_ref()
{
    this->pb2->setValue(this->sl2->value());
    this->l2->setText(QString::number(this->sl2->value()));
}

void gd_plot::setM3_ref()
{
    this->pb3->setValue(this->sl3->value());
    this->l3->setText(QString::number(this->sl3->value()));
}

void gd_plot::setM4_ref()
{
    this->pb4->setValue(this->sl4->value());
    this->l4->setText(QString::number(this->sl4->value()));
}

void gd_plot::setAM_ref()
{
    this->apb->setValue(this->asl->value());
    this->alla->setText(QString::number(this->asl->value()));
//    M1
    if (this->acb1->isChecked())
    {
        this->pb1->setValue(this->asl->value());
        this->sl1->setValue(this->asl->value());
        this->l1->setText(QString::number(this->asl->value()));
    }

//    M2
    if (this->acb2->isChecked())
    {
    this->pb2->setValue(this->asl->value());
    this->sl2->setValue(this->asl->value());
    this->l2->setText(QString::number(this->asl->value()));
    }

//    M3
    if (this->acb3->isChecked())
    {
    this->pb3->setValue(this->asl->value());
    this->sl3->setValue(this->asl->value());
    this->l3->setText(QString::number(this->asl->value()));
    }

//    M4
    if (this->acb4->isChecked())
    {
        this->pb4->setValue(this->asl->value());
        this->sl4->setValue(this->asl->value());
        this->l4->setText(QString::number(this->asl->value()));
    }

}

void gd_plot::drawSerialInfo(QPainter *painter)
{
    QPen the_pen = QPen(this->serialColor);
//    the_pen.setStyle(Qt::DashLine);
    painter->setPen(the_pen);
//    painter->drawRect(this->connInfoRect);
    QPoint C = QPoint(this->connInfoRect.x()+this->connInfoRect.width()/2,
                      this->connInfoRect.y()+this->connInfoRect.width()/2);
    int diameter = this->connInfoRect.width();

    painter->drawText(QPoint(C.x()-diameter/4, //
                            C.y()-diameter/2),QString("connection info:"));
    painter->drawText(QPoint(C.x()-diameter/4, //
                            C.y()-diameter/2+10),this->serial_info.statusStr);
    painter->drawText(QPoint(C.x()+5-diameter/2, //
                            C.y()-diameter/2+25),QString("Baud: "));
    painter->drawText(QPoint(C.x()+5-diameter/2, //
                            C.y()-diameter/2+35),QString("DataBits: "));
    painter->drawText(QPoint(C.x()+5-diameter/2, //
                            C.y()-diameter/2+45),QString("Parity: "));
    painter->drawText(QPoint(C.x()+5-diameter/2, //
                            C.y()-diameter/2+55),QString("StopBits: "));
    painter->drawText(QPoint(C.x()+5-diameter/2, //
                            C.y()-diameter/2+65),QString("FlowCtrl: "));
    painter->drawText(QPoint(C.x()+5-diameter/2, //
                            C.y()-diameter/2+75),QString("COM: "));

    painter->drawText(C.x()+5, C.y()-diameter/2+25, this->serial_info.baude);
    painter->drawText(C.x()+5, C.y()-diameter/2+35, this->serial_info.data_bits);
    painter->drawText(C.x()+5, C.y()-diameter/2+45, this->serial_info.parity);
    painter->drawText(C.x()+5, C.y()-diameter/2+55, this->serial_info.stop_bits);
    painter->drawText(C.x()+5, C.y()-diameter/2+65, this->serial_info.flow_ctrl);
    painter->drawText(C.x()+5, C.y()-diameter/2+75, this->serial_info.com);

//    painter->drawText(C.x()+5, C.y()-diameter/2+15, serial_connection_status::baudR);
//    painter->drawText(C.x()+5, C.y()-diameter/2+35, serial_connection_status::dataB);
//    painter->drawText(C.x()+5, C.y()-diameter/2+55, serial_connection_status::Parity);
//    painter->drawText(C.x()+5, C.y()-diameter/2+75, serial_connection_status::stopB);
//    painter->drawText(C.x()+5, C.y()-diameter/2+95, serial_connection_status::flowCtrl);
//    painter->drawText(C.x()+5, C.y()-diameter/2+115, serial_connection_status::port_);

}

void gd_plot::refreshPixmap()
{
    this->pixel_map->fill(Qt::black);

//    QPen white_color = QPen(QColor(255,255,255,255));
//    QPen red_color = QPen(QColor(200,10,10,255));
//    QPen green_color = QPen(QColor(10,200,10,255));

    QPen the_pen = QPen(Qt::white);

    QPainter painter(this->pixel_map);
    painter.setPen(the_pen);

//    draw the margins
    QPointF P1 = QPointF(10,10);
    QPointF P2 = QPointF(10, (this->height()-10));
    QPointF P3 = QPointF((this->width()-10),10);
    QPointF P4 = QPointF((this->width()-10), (this->height()-10));

    QLineF line1 = QLineF(P1,P2);
    QLineF line2 = QLineF(P1,P3);
    QLineF line3 = QLineF(P2,P4);
    QLineF line4 = QLineF(P3,P4);

    if (this->zomo_enabled)
    {
        the_pen.setStyle(Qt::DashLine);
        painter.setPen(the_pen);
    }

    painter.drawLine(line1);
    painter.drawLine(line2);
    painter.drawLine(line3);
    painter.drawLine(line4);

    the_pen.setStyle(Qt::SolidLine);
    painter.setPen(the_pen);

//    draw the vehicle
    int diameter = 130;
//    int l = (this->height() < this->width())?this->height():this->width();
//    int l_arm = l-40-diameter;
//    int dist = min(this->height(),this->width())/1;
    int l_arm = this->dist-40-diameter;
//    int l_arm = this->height()-40-diameter;


//    QPointF C = QPointF(this->width()/2, this->height()/2);
    QPointF C = QPointF(this->Ctr.rx(),this->Ctr.ry());

    QPointF M1 = QPointF((C.x()+l_arm/2), (C.y()));
    QPointF M2 = QPointF((C.x()), (C.y()-l_arm/2));
    QPointF M3 = QPointF((C.x()-l_arm/2), (C.y()));
    QPointF M4 = QPointF((C.x()), (C.y()+l_arm/2));

    QLineF arm1 = QLineF(M1,M3);
    QLineF arm2 = QLineF(M2,M4);
//  draw arms
    painter.drawLine(arm1);
    painter.drawLine(arm2);

//    serial info rectangle
    QRect qr = QRect(C.x()-diameter/2, C.y()-diameter/2,diameter-1,diameter-1);
    painter.drawRect(qr);
    painter.fillRect(qr.x()+1,qr.y()+1,qr.width()-2,qr.height()-2, //
                     Qt::SolidPattern);
    this->connInfoRect = qr;



//  draw the motors
    the_pen.setColor(this->M1color);
    painter.setPen(the_pen);
    painter.drawEllipse(M1.x()-diameter/2,M1.y()-diameter/2,diameter,diameter);

    the_pen.setColor(this->M2color);
    painter.setPen(the_pen);
    painter.drawEllipse(M2.x()-diameter/2,M2.y()-diameter/2,diameter,diameter);

    the_pen.setColor(this->M3color);
    painter.setPen(the_pen);
    painter.drawEllipse(M3.x()-diameter/2,M3.y()-diameter/2,diameter,diameter);

    the_pen.setColor(this->M4color);
    painter.setPen(the_pen);
    painter.drawEllipse(M4.x()-diameter/2,M4.y()-diameter/2,diameter,diameter);
    painter.setPen(the_pen);

//    draw controls M1
    this->sl1->setGeometry(M1.x()-15,M1.y()+diameter/2+15,30,diameter);
    this->pb1->setGeometry(M1.x()+15,M1.y()+diameter/2+15,15,diameter);
    this->cb1->setGeometry(M1.x()-15, M1.y()+diameter*3/2+20,20,20);
    this->l1->setGeometry(M1.x()+10, M1.y()+diameter*3/2+20, 30,20);

//    draw controls M2
    this->sl2->setGeometry(M2.x()+diameter/2+15,M2.y()-diameter/2+15,30,diameter);
    this->pb2->setGeometry(M2.x()+diameter/2+45,M2.y()-diameter/2+15,15,diameter);
    this->cb2->setGeometry(M2.x()+diameter/2+15,M2.y()+diameter/2+20,20,20);
    this->l2->setGeometry(M2.x()+diameter/2+40,M2.y()+diameter/2+20,30,20);

//    draw controls M3
    this->sl3->setGeometry(M3.x()-15,M3.y()-diameter*3/2-35,30,diameter);
    this->pb3->setGeometry(M3.x()+15,M3.y()-diameter*3/2-35,15,diameter);
    this->cb3->setGeometry(M3.x()-15,M3.y()-diameter/2-30,20,20);
    this->l3->setGeometry(M3.x()+10, M3.y()-diameter/2-30, 30,20);

//    draw controls M4
    this->sl4->setGeometry(M4.x()-diameter/2-45-20,M4.y()-diameter/2-45,30,diameter);
    this->pb4->setGeometry(M4.x()-diameter/2-15-20,M4.y()-diameter/2-45,15,diameter);
    this->cb4->setGeometry(M4.x()-diameter/2-45-20, M4.y()+diameter/2-40,20,20);
    this->l4->setGeometry(M4.x()-diameter/2-15-20, M4.y()+diameter/2-40, 30,20);

//    draw controls AMot check-boxes
    this->acb1->setGeometry(M1.x(), M2.y()-diameter/2+15 ,20,20);
    this->acb2->setGeometry(M1.x(), M2.y()-diameter/2+45 ,20,20);
    this->acb3->setGeometry(M1.x(), M2.y()-diameter/2+75 ,20,20);
    this->acb4->setGeometry(M1.x(), M2.y()-diameter/2+105 ,20,20);

    this->acb_sl->setGeometry(M1.x()+90,M2.y()-diameter/2+15 ,20,20);
    this->alla->setGeometry(M1.x()+90,M2.y()-diameter/2+50, 25,20);

//    draw AMot slider
    this->asl->setGeometry(M1.x()+30, M2.y()-diameter/2+15,30,110);

//    draw AMot progress bar
    this->apb->setGeometry(M1.x()+60, M2.y()-diameter/2+15,15,110);

//    draw text for motors
    the_pen.setColor(Qt::white);
    painter.setPen(the_pen);

    painter.drawText(M1,QString("M1"));
    painter.drawText(M2.x()+5,M2.y(),QString("M2"));
    painter.drawText(M3,QString("M3"));
    painter.drawText(M4,QString("M4"));

//    alx labels
    painter.drawText(QPoint(M1.x()-20, //
                                  M2.y()-diameter/2+105),QString("M4"));
    painter.drawText(QPoint(M1.x()-20, //
                                  M2.y()-diameter/2+75),QString("M3"));
    painter.drawText(QPoint(M1.x()-20, //
                                  M2.y()-diameter/2+45),QString("M2"));
    painter.drawText(QPoint(M1.x()-20, //
                                  M2.y()-diameter/2+15),QString("M1"));

//    painter.drawText(QPoint(M1.x()-20, //
//                                  M2.y()+diameter/2),QString("M4"));
//    painter.drawText(QPoint(M1.x()-20, //
//                                  M2.y()+diameter/2-20),QString("M3"));
//    painter.drawText(QPoint(M1.x()-20, //
//                                  M2.y()+diameter/2-40),QString("M2"));
//    painter.drawText(QPoint(M1.x()-20, //
//                                  M2.y()+diameter/2-60),QString("M1"));

//    emstop button
    this->EMStop->setGeometry(M3.x()-25,M4.y()-25,50,50);

//    connection info
    this->drawSerialInfo(&painter);


//    group box with radio buttons
    QRect gb_rect = QRect(M3.x()-diameter/2-50,M2.y()-50,70,70);
    painter.fillRect(gb_rect,Qt::gray);
    this->gb->setGeometry(M3.x()-diameter/2-50,M2.y()-50,70,70);

//    connect pushbutton
    this->conn_->setGeometry(C.x()-diameter/2+5,C.y()+30,
                             50,25);
    this->disconn_->setGeometry(C.x(),C.y()+30,
                             60,25);

//    draw summary string
    painter.drawText(30,this->height()-20,this->strSummary);

    painter.end();
    this->update();
}

void gd_plot::paintEvent(QPaintEvent *event)
{
    QPainter painter1(this);
    painter1.drawPixmap(0,0, this->pixel_map->scaled(this->width(),this->height()));
    event->ignore();
    return;
}
