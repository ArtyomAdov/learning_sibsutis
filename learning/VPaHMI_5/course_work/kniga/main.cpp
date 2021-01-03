#include "mainwindow1.h"
#include <QApplication>
#include <QSplashScreen>
#include <QThread>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QTextCodec* codec = QTextCodec::codecForName("CP1251");
    //QTextCodec::setCodecForCStrings(codec);
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/splash/splash.jpg"));
    splash->show();
    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->showMessage(QObject::trUtf8("<H1>Создание основного окна...</H1>"), topRight, Qt::black);
    QThread::sleep(10);
    MainWindow1 *w = new MainWindow1;
    w->show();
    splash->finish(w);
    delete splash;
    return a.exec();
}
