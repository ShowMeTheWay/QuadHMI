#include "gd_chart.h"
#include<QPainter>
#include<QIcon>
#include<math.h>
#include<iostream>
//#include<algorithm>

using namespace std;

gd_chart::gd_chart(QWidget *parent):QWidget(parent)
{
    this->setBackgroundRole(QPalette::Dark);
    this->setAutoFillBackground(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setFocusPolicy(Qt::StrongFocus);

    this->setMinimumSize(650,550);
    this->setAttribute(Qt::WA_DeleteOnClose);

    this->setWindowTitle(QString("accelerometer readings"));
//    logo
    QString pic_path = QString("D:/UTCN/master/an2/sem2/individual/programare/motorsTestPanel/logo1.png");
    this->setWindowIcon(QIcon(pic_path));

    this->pixel_map = new QPixmap(this->size());

    this->chart_accx = new chart_settings();
    this->chart_accy = new chart_settings();
    this->chart_accz = new chart_settings();

    this->numPoints = 100;
    this->data_accx = QVector<QPointF>(this->numPoints);

    this->serial_info = serial_conn_info();

    this->connInfoRect = QRect();

//    simulate some initial data
    double t,x;
    QVector<QPointF> data_x = QVector<QPointF>(this->numPoints);
    QVector<QPointF> data_y = QVector<QPointF>(this->numPoints);
    QVector<QPointF> data_z = QVector<QPointF>(this->numPoints);
    QPointF pt;
    for (int i=0;i<this->numPoints;i++)
    {
        t = i*0.1;
        x = sin(5*t);
        pt = QPointF(t,x);
        data_x[i] = pt;

        x = cos(5*t);
        pt = QPointF(t,x);
        data_y[i] = pt;

        x = 10*sin(5*t)*cos(3*t);
        pt = QPointF(t,x);
        data_z[i] = pt;

    }

    this->set_data_accx(data_x);
    this->set_data_accy(data_y);
    this->set_data_accz(data_z);

    this->refreshPixmap();
}

gd_chart::~gd_chart()
{
    delete this->pixel_map;
    delete this->chart_accx;
    delete this->chart_accy;
    delete this->chart_accz;
}

void gd_chart::closeEvent(QCloseEvent *event)
{
//    emit its_closing_here();
    cout<<"acc: good bye!"<<endl;
//    delete this;
}

void gd_chart::paintEvent(QPaintEvent *event)
{
    QPainter painter1(this);
    painter1.drawPixmap(0,0, this->pixel_map->scaled(this->width(),this->height()));
      return;
}

void gd_chart::set_data_accx(QVector<QPointF> datax)
{
    this->data_accx = datax;
}

void gd_chart::set_data_accy(QVector<QPointF> datay)
{
    this->data_accy = datay;
//    this->refreshPixmap();
}

void gd_chart::set_data_accz(QVector<QPointF> dataz)
{
    this->data_accz = dataz;
//    this->refreshPixmap();
}

void gd_chart::refreshPixmap()
{
    this->pixel_map->fill(Qt::black);

    int Len = this->width()-this->margin2-this->margin2;
    int Hei = this->height()-1*this->margin2;
    int len = Len, hei = (int)(Hei-3*this->margin1)/3;

    this->rect_accx = QRect(this->margin2, this->margin1,len,hei);
    this->rect_accy = QRect(this->margin2,
                            2*this->margin1+hei,len,hei);
    this->rect_accz = QRect(this->margin2,
                            3*this->margin1+2*hei,len,hei);

    QPen the_pen = QPen(Qt::white);
    QPainter *painter = new QPainter(this->pixel_map);
    painter->setPen(the_pen);

    painter->drawRect(this->rect_accx);
    painter->drawRect(this->rect_accy);
    painter->drawRect(this->rect_accz);

    this->drawCurve_chart(this->rect_accx,painter,this->chart_accx,
                          this->data_accx);
    this->drawCurve_chart(this->rect_accy,painter,this->chart_accy,
                          this->data_accy);
    this->drawCurve_chart(this->rect_accz,painter,this->chart_accz,
                          this->data_accz);

    this->drawGrid_chart(this->rect_accx, painter,
                         this->chart_accx);
    this->drawGrid_chart(this->rect_accy, painter,
                         this->chart_accy);
    this->drawGrid_chart(this->rect_accz, painter,
                         this->chart_accz);

    the_pen.setColor(Qt::white);
    painter->setPen(the_pen);
    painter->drawText(this->rect_accx.x() + len-30,
                      this->rect_accx.y()-5,QString("acc x"));
    painter->drawText(this->rect_accy.x() + len-30,
                      this->rect_accy.y()-5,QString("acc y"));
    painter->drawText(this->rect_accz.x() + len-30,
                      this->rect_accz.y()-5,QString("acc z"));

//    connection info
    painter->drawText(this->rect_accx.x(),
                      this->rect_accz.y()+hei+this->margin1,
                      QString("connection info:"));
    painter->drawText(this->rect_accx.x()+100,
                      this->rect_accz.y()+hei+this->margin1,
                      QString("Baude:"));
    painter->drawText(this->rect_accx.x()+100,
                      this->rect_accz.y()+
                      hei+this->margin1+10,
                      QString("DataBits:"));
    painter->drawText(this->rect_accx.x()+100,
                      this->rect_accz.y()+
                      hei+this->margin1+20,
                      QString("Parity:"));
    painter->drawText(this->rect_accx.x()+200,
                      this->rect_accz.y()+hei+this->margin1,
                      QString("StopBits:"));
    painter->drawText(this->rect_accx.x()+200,
                      this->rect_accz.y()+
                      hei+this->margin1+10,
                      QString("FlowCtrl:"));
    painter->drawText(this->rect_accx.x()+200,
                      this->rect_accz.y()+
                      hei+this->margin1+20,
                      QString("COM:"));
    this->connInfoRect = QRect(this->rect_accx.x()-5,
                                   this->rect_accz.y()+hei
                                   +this->margin1-15,300,40);
    painter->drawRect(this->connInfoRect);

    this->drawSerialInfo(painter);

    painter->end();

    this->update();
}

void gd_chart::drawSerialInfo(QPainter *painter)
{
    painter->drawText(this->connInfoRect.x()+155,
                      this->connInfoRect.y()+15,
                      this->serial_info.baude);
    painter->drawText(this->connInfoRect.x()+155,
                      this->connInfoRect.y()+25,
                      this->serial_info.data_bits);
    painter->drawText(this->connInfoRect.x()+155,
                      this->connInfoRect.y()+35,
                      this->serial_info.parity);
    painter->drawText(this->connInfoRect.x()+255,
                      this->connInfoRect.y()+15,
                      this->serial_info.stop_bits);
    painter->drawText(this->connInfoRect.x()+255,
                      this->connInfoRect.y()+25,
                      this->serial_info.flow_ctrl);
    painter->drawText(this->connInfoRect.x()+255,
                      this->connInfoRect.y()+35,
                      this->serial_info.com);
}

void gd_chart::drawCurve_chart(QRect rect, QPainter *painter,
                               chart_settings *chrs,
                               QVector<QPointF> data_acc)
{
    int wi = rect.width(), he = rect.height();
    int rx = rect.x(), ry = rect.y(), lx = 0, ly = 0;

    QPolygonF polyline = QPolygonF(data_acc.length());
    QVector<double> vy = QVector<double>(data_acc.length());
    QPointF pt;

//    get min and max for y axis
    double minY = data_acc[1].y(), maxY = minY;
    for (int i = 0; i<data_acc.length(); i++)
    {
        pt = data_acc.at(i);
        vy[i] = pt.y();
        if (vy[i]<minY)
        {
            minY = vy[i];
        }
        if(vy[i]>maxY)
        {
            maxY = vy[i];
        }
    }

    chrs->maxY = maxY;
    chrs->minY = minY;

    double step_x = wi/data_acc.length();
    double step_y = he/chrs->spanY();
    int xpos = 0, ypos = 0;
    QPen the_pen = QPen(Qt::cyan);
//    the_pen.setStyle(Qt::DashLine);
    painter->setPen(the_pen);
    int rr = 4;
//    draw the curve
    for (int i = 0; i < data_acc.length(); i++)
    {
        xpos = rx + i*step_x;
        ypos = (ry + he) - (vy.at(i)-chrs->minY)*step_y;
        painter->drawEllipse(xpos-2,ypos-2,rr,rr);
//        painter->drawRect(xpos-rr/2,ypos-rr/2,rr,rr);
        polyline[i] = QPointF(xpos,ypos);
    }

    painter->drawPolyline(polyline);

//    cout<<"max y = "<<this->chart_accx->maxY<<endl;

}

void gd_chart::drawGrid_chart(QRect rect, QPainter *painter,
                             chart_settings *chrs)
{
    QPen the_pen = QPen(Qt::white);
    painter->setPen(the_pen);

    int wi = rect.width(), he = rect.height();
    int rx = rect.x(), ry = rect.y(), lx = 0, ly = 0;

    double stepx = wi/(chrs->num_ticks_X-1);
    double stepx_re = chrs->spanX()/(chrs->num_ticks_X-1);

    double stepy = he/(chrs->num_ticks_Y-1);
    double stepy_re = chrs->spanY()/(chrs->num_ticks_Y-1);

    double lx_re = 0, ly_re = 0;
    QLine line;

    painter->drawText(rx,ry+he+15,
                      QString::number(chrs->minX,'e',2));
    painter->drawText(rx+wi,ry+he+15,
                      QString::number(chrs->maxX,'e',2));

    painter->drawText(rx-this->margin2+15,ry+5,
                      QString::number(chrs->maxY,'e',2));
    painter->drawText(rx-this->margin2+15,ry+he,
                      QString::number(chrs->minY,'e',2));

    the_pen.setColor(Qt::gray);
    the_pen.setStyle(Qt::DashDotDotLine);
    painter->setPen(the_pen);

    for (int i = 0; i<chrs->num_ticks_X-2; i++)
    {
        lx = rx + (i+1)*stepx;
        ly = ry;
        line = QLine(lx,ly,lx,ly+he);
        painter->drawLine(line);

        lx_re = chrs->minX+(i+1)*stepx_re;
        painter->drawText(lx,ly+he+15,QString::number(lx_re,'e',2));
    }

    for (int i = 0; i<chrs->num_ticks_Y-2; i++)
    {
        lx = rx;
        ly = ry + (i+1)*stepy;
        line = QLine(lx,ly,lx+wi,ly);
        painter->drawLine(line);

        ly_re = chrs->maxY-(i+1)*stepy_re;
        painter->drawText(lx-this->margin2+15,ly,QString::number(ly_re,'e',2));
    }
}

