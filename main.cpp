#include "main_window.h"
#include <QApplication>
#include"gd_plot.h"
#include<QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    main_window *mw = new main_window;
    mw->show();

    return a.exec();
}
