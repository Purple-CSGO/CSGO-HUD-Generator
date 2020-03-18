#include "mainwindow.h"
#include <QApplication>
#pragma execution_character_set("utf-8")

const QString appName = "CSGO HUD Generator";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle( appName );    //设置标题   + " - " + "0.1"

    w.show();
    return a.exec();
}
