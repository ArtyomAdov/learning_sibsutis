#include "sdiprogram_adov.h"
#include <QApplication>

void LoadModules(QSplashScreen* psplash){
    QTime time;
    time.start();
    for(int i=0;i<100;){
        if(time.elapsed()>40){
            time.start();
            i++;
        }

        psplash->showMessage("Loading modules: "
                             + QString::number(i)+"%",
                             Qt::black
                             );
        qApp->processEvents();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen splash(QPixmap("S.jpg"));
    splash.show();
    SDIProgramUteshev w;
    LoadModules(&splash);
    splash.finish(&w);
    w.show();

    return a.exec();
}
