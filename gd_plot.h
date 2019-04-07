#ifndef GD_PLOT_H
#define GD_PLOT_H
#include<QWidget>
#include<QPainter>
#include<QMap>
#include<QPixmap>
#include<QPushButton>
#include<QSlider>
#include<QProgressBar>
#include<QLabel>
#include<QAbstractButton>
#include<QCheckBox>
#include<QColor>
#include<QMenuBar>
#include<QMenu>
#include<QGroupBox>
#include<QRadioButton>
#include<serial_conn_info.h>
#include"serial_connection_status.h"

class gd_plot : public QWidget
{
    Q_OBJECT

public:
    gd_plot(QWidget *parent = 0);
    ~gd_plot();
//    gd_plot(QWidget *parent);

protected slots:
    void M1_enable(int state);
    void M2_enable(int state);
    void M3_enable(int state);
    void M4_enable(int state);

    void AM1_check(int state);
    void AM2_check(int state);
    void AM3_check(int state);
    void AM4_check(int state);
    void AM_SL_check(int state);

    void setM1_ref();
    void setM2_ref();
    void setM3_ref();
    void setM4_ref();

    void setAM_ref();
    void EMzero();

    void CONNslot();
    void DISCONNslot();

    void updateStrSummary();

signals:
    void strReady(QString strSummary);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void resizeEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void refreshPixmap();
    void drawSerialInfo(QPainter *painter);

private:
    QPixmap *pixel_map;

    QCheckBox *cb1;
    QCheckBox *cb2;
    QCheckBox *cb3;
    QCheckBox *cb4;

    QCheckBox *acb1;
    QCheckBox *acb2;
    QCheckBox *acb3;
    QCheckBox *acb4;
    QCheckBox *acb_sl;

    QSlider *sl1;
    QSlider *sl2;
    QSlider *sl3;
    QSlider *sl4;
    QSlider *asl;

    QColor M1color;
    QColor M2color;
    QColor M3color;
    QColor M4color;
    QColor serialColor;

    QProgressBar *pb1;
    QProgressBar *pb2;
    QProgressBar *pb3;
    QProgressBar *pb4;
    QProgressBar *apb;

    QLabel *l1;
    QLabel *l2;
    QLabel *l3;
    QLabel *l4;

    QLabel *alla;

    QLabel *baud_info;
    QLabel *dataB_info;
    QLabel *pol_info;
    QLabel *sBits_info;
    QLabel *flowCon_info;
    QLabel *com_info;

    QPushButton *EMStop;
    QPushButton *conn_;
    QPushButton *disconn_;

    QGroupBox *gb;
    QRadioButton *auto_b;
    QRadioButton *man_b;

    serial_conn_info serial_info;

    QRect connInfoRect;

    QString strSummary;

    bool is_conn;
    bool zomo_enabled;
    int dist;
    QPoint Ctr;
    QPoint cP;
    QPoint shwCtr;



};

#endif // GD_PLOT_H
