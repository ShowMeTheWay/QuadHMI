#ifndef GD_CHART_H
#define GD_CHART_H

#include<QWidget>
#include<iostream>
#include"chart_settings.h"
#include<QLabel>
#include<QVector>
#include"serial_conn_info.h"
#include <QRect>

using namespace std;

class gd_chart: public QWidget
{
    Q_OBJECT
public:
    gd_chart(QWidget *parent = 0);
    void set_chart_settings_accx(chart_settings ch_st);
    void set_chart_settings_accy(chart_settings ch_st);
    void set_chart_settings_accz(chart_settings ch_st);
    void set_data_accx(QVector<QPointF> datax);
    void set_data_accy(QVector<QPointF> datay);
    void set_data_accz(QVector<QPointF> dataz);

    ~gd_chart();
protected:
    void refreshPixmap();
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);

    void drawGrid_chart(QRect rect, QPainter *painter,
                       chart_settings *chrs);
    void drawCurve_chart(QRect rect, QPainter *painter,
                        chart_settings *chrs,
                        QVector<QPointF> data_acc);
    void drawSerialInfo(QPainter *painter);

private:
    QPixmap *pixel_map;
    chart_settings *chart_accx;
    chart_settings *chart_accy;
    chart_settings *chart_accz;
    enum {margin1 = 40, margin2 = 70};
    int numPoints;
    QRect rect_accx;
    QRect rect_accy;
    QRect rect_accz;

    QVector<QPointF> data_accx;
    QVector<QPointF> data_accy;
    QVector<QPointF> data_accz;
    serial_conn_info serial_info;

    QRect connInfoRect;

};

#endif // GD_CHART_H
