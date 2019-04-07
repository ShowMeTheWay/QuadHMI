#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include <QMainWindow>
#include"gd_plot.h"
#include"gd_chart.h"
#include<QPainter>
#include<QPushButton>
#include"scomdialog.h"


class main_window : public QMainWindow
{
    Q_OBJECT

public:
    main_window(QWidget *parent = 0);
    ~main_window();

protected slots:
    void bMTP_slot();
    void bACC_slot();
    void bCOM_slot();

    void treat_mtp_closing();
    void treat_acc_closing();
    void treat_com_closing();

protected:
    void closeEvent(QCloseEvent *event);

private:
    gd_plot *motorTestPanel=NULL;
    gd_chart *accPanel=NULL;
    sComDialog *comPanel = NULL;


    QLabel *logo;
    QLabel *mainWidget;

    QPushButton *buttonMTP;
    QPushButton *buttonCOM;
    QPushButton *buttonACC;
    QPushButton *buttonGYRO;
    QPushButton *buttonMAG;
    QPushButton *buttonGPS;
    QPushButton *buttonSFU;
    QPushButton *buttonBMS;


};

#endif // MAINWINDOW_H
