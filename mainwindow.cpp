#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPen>
#include <QPainter>
#include <QSettings>
#include <QDebug>
#include <QTranslator>
#pragma execution_character_set("utf-8")

//定义变量
int height, width, size, gap, thickness, color;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->heightlabel->setText( tr("高: ") );
    ui->widthlabel->setText( tr("宽: ") );
    ui->sizelabel->setText( tr("准星长度: ") );
    ui->gaplabel->setText( tr("准星间隙: ") );
    ui->thicknesslabel->setText( tr("准星厚度: ") );
    ui->outlinelabel->setText( tr("准星外轮廓: ") );

    //设置颜色表
    ui->colorBox->clear();
    QStringList strList;
    strList <<tr("绿色")<<tr("红色")<<tr("蓝色")<<tr("白色")<<tr("青色");
    ui->colorBox->addItems(strList);

    //读取设置
    readSetting();
}

MainWindow::~MainWindow()
{
    saveSetting();
    delete ui;
}

//生成按钮槽函数
void MainWindow::on_generateButton_clicked()
{
    //从UI获取信息
    height = ui->heightEdit->text().toInt();
    width = ui->widthEdit->text().toInt();
    size = 2 * ui->sizeEdit->text().toInt();
    gap = 6 + ui->gapEdit->text().toInt();
    thickness = ui->thicknessEdit->text().toInt();
    color = ui->colorBox->currentIndex();

    //height = 1920, width = 1080, length = 6, gap = 5, thickness = 2;
    //cl_crosshairgap "-0.5"
    QImage image(width, height, QImage::Format_ARGB32);
    memset(image.bits(), 0x00, image.byteCount());

    // 绘制图片
    QPainter painter(&image);
    painter.translate(width/2, height/2);

    //设置颜色
    switch(color){
    case 0:
        painter.setPen(QPen(Qt::green, thickness, Qt::SolidLine));break;
    case 1:
        painter.setPen(QPen(Qt::red, thickness, Qt::SolidLine));break;
    case 2:
        painter.setPen(QPen(Qt::blue, thickness, Qt::SolidLine));break;
    case 3:
        painter.setPen(QPen(Qt::white, thickness, Qt::SolidLine));break;
    case 4:
        painter.setPen(QPen(Qt::cyan, thickness, Qt::SolidLine));break;
    }
    //qDebug() << color;

    painter.drawLine(0-gap, 0, 0-gap-size, 0);
    painter.drawLine(0+gap, 0, 0+gap+size, 0);
    painter.drawLine(0, 0-gap, 0, 0-gap-size);
    painter.drawLine(0, 0+gap, 0, 0+gap+size);
    //绘制dot    painter.drawLine(0,0,0,0);
    /*
img0 = QtGui.QImage('\x00'*96,24,24,QtGui.QImage.Format_Mono)   #为什么是96不是72，因为QImage规定每行最小宽度为32
painter = QtGui.QPainter(img0)
painter.setPen(QtGui.QPen(QtCore.Qt.red))
painter.setFont(self.font)
painter.drawText(3,18,text) #将汉字写在一张图片上，然后对图片逐点取样从而得到汉字的字模数据
painter.end()

bits = img0.bits()
bits.setsize(img0.byteCount())
data = ['0x'+hex(x)[2:].upper() if x >= 0x10 else '0x0'+hex(x)[2:].upper() for x in [ord(x) for x in bits.asstring()]]

data = [data[i] for i in range(0,len(data)) if i%4 != 3]    #处理96变回72

return ','.join(data)


//    //QPainter painter(&image); //为这个QImage构造一个QPainter
//    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
//    //设置画刷的组合模式CompositionMode_SourceOut这个模式为目标图像在上。
//    //改变组合模式和上面的填充方式可以画出透明的图片。
//    //改变画笔和字体
//    QPen pen = painter.pen();
//    pen.setColor(Qt::red);
//    QFont font1;
//    font1.setFamily("微软雅黑");
//    QFont font = painter.font();
//    font.setBold(true);//加粗
//    font.setPixelSize(50);//改变字体大小
//    painter.setPen(pen);
//    painter.setFont(font1);
//    painter.drawText(image.rect(),Qt::AlignCenter,"Hello");
*/
    qDebug() << image.save("C:/Users/Purp1e/Desktop/test.png", "PNG");
}

//保存设置
void MainWindow::saveSetting()
{
    //写设置
    QSettings *IniWrite = new QSettings("./config.ini", QSettings::IniFormat);
    IniWrite->setIniCodec("utf-8");     //解决乱码问题

    //读取变量值
    height = ui->heightEdit->text().toInt();
    width = ui->widthEdit->text().toInt();
    size = ui->sizeEdit->text().toInt();
    gap = ui->gapEdit->text().toInt();
    thickness = ui->thicknessEdit->text().toInt();
    color = ui->colorBox->currentIndex();

    //IniWrite->beginGroup("AppInfo");
    IniWrite->setValue("height", height);
    IniWrite->setValue("width", width);
    IniWrite->setValue("size", size);
    IniWrite->setValue("gap", gap);
    IniWrite->setValue("thickness", thickness);
    IniWrite->setValue("color", color);
    //IniWrite->endGroup();

    //写入完成后删除指针
    delete IniWrite;
}

//读取设置
void MainWindow::readSetting()
{
    QSettings *iniRead = new QSettings("./config.ini", QSettings::IniFormat);
    iniRead->setIniCodec("utf-8");     //解决乱码问题
    int t = 0;
    height = 1080, width = 1920, size =3, gap = 1, thickness = 2, color = 0;
    //iniRead->beginGroup("  ");
    t = iniRead->value("height").toInt();
    if( t )    height  = t;
    //else height =666;
    t = iniRead->value("width").toInt();
    if( t )    width  = t;
    t = iniRead->value("size").toInt();
    if( t )    size  = t;
    t = iniRead->value("gap").toInt();
    if( t )    gap = t;
    t = iniRead->value("thickness").toInt();
    if( t )    thickness  = t;
    t  = iniRead->value("color").toInt();
    if( t )    color  = t;
    //iniRead->endGroup();

    //读入完成后删除指针
    delete iniRead;

    //设置值到UI
    ui->heightEdit->setText( QString::number(height) );
    ui->widthEdit->setText( QString::number(width) );
    ui->sizeEdit->setText( QString::number(size) );
    ui->gapEdit->setText( QString::number(gap) );
    ui->thicknessEdit->setText( QString::number(thickness) );
    ui->colorBox->setCurrentIndex( color );

}

//多语言支持
void MainWindow::multiLanguage()
{
//        //增加多语言支持
//        QSystemLocale locale;
//        QVariant val(QLocale::UnitedStates);
//        QString translatorFileName = "";

//        QTranslator *translator = new QTranslator(app);

//      //查询当前国别代码
//        val = locale.query(QSystemLocale::CountryId,val);

//       // QDebug()<< "val.int" << val.Int << ",china=" <<QLocale::China;
//       switch(val.toInt())
//           {
//            case QLocale::China:
//              translatorFileName = "BD4P-zh_CN.qm";
//              break;
//            case QLocale::Taiwan:
//               translatorFileName = "BD4P-zh_TW.qm";
//               break;
//           case QLocale::HongKong:
//              translatorFileName = "BD4P-zh_HK.qm";
//              break;

//           }

//           if (translatorFileName!="")
//           {
//    #ifdef QT_DEBUG
//               translatorFileName = "E:\\QtProject\\Test\\Test\\"+translatorFileName;
//    #endif
//               if (translator->load(translatorFileName))
//               {
//               app->installTranslator(translator);
//               }
//           }
}
