#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QPixmap(":/images/appicon.png"));
    w.setIconSize(QSize(32,32));
    w.show();

    return a.exec();
}
