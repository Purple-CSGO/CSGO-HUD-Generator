﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QPen>
#include <QPainter>
#include <QSettings>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_generateButton_clicked();

private:
    Ui::MainWindow *ui;

    //定义变量
    int height, width, size, gap, thickness, color;

    void saveSetting();
    void readSetting();
    void multiLanguage();
};
#endif // MAINWINDOW_H
