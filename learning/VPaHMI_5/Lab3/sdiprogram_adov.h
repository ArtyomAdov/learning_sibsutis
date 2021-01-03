#ifndef SDIPROGRAM_ADOV_H
#define SDIPROGRAM_ADOV_H

#include <QMainWindow>
#include "docwindow_adov.h"

class SDIProgramAdov : public QMainWindow
{
    Q_OBJECT

public:
    SDIProgramAdov(QWidget* pwgt = 0):QMainWindow(pwgt){
        QMenu* pmniFile = new QMenu("&File");
        QMenu* pmniHelp = new QMenu("&Help");
        DocWindowAdov* pdoc = new DocWindowAdov;
        pmniFile->addAction("&Open",
                            pdoc,
                            SLOT(slotLoad()),
                            QKeySequence("F9")
                            );
        pmniFile->addAction("&Save",
                            pdoc,
                            SLOT(slotSave()),
                            QKeySequence("F5")
                            );
        pmniFile->addAction("&Save As",
                            pdoc,
                            SLOT(slotSaveAs()),
                            QKeySequence("CTRL+S")
                            );
        pmniFile->addAction("&Color",
                            pdoc,
                            SLOT(slotColor()),
                            QKeySequence("CTRL+C")
                            );
        pmniFile->addSeparator();
        pmniFile->addAction("&Quit",
                            qApp,
                            SLOT(quit()),
                            QKeySequence("ESC")
                            );
        pmniHelp->addAction("&Help",
                            this,
                            SLOT(slotAbout()),
                            QKeySequence("F1")
                            );
        menuBar()->addMenu(pmniFile);
        menuBar()->addMenu(pmniHelp);

        setCentralWidget(pdoc);

        connect(pdoc,
                SIGNAL(changeWindowTitle(const QString&)),
                SLOT(slotChangeWindowTitle(const QString&))
                );
        statusBar()->showMessage("Ready",2000);

    }
public slots:
    void slotAbout(){
        QMessageBox::about(this,"Автор","Имя: Игорь\nФамилия: Адов");
    }
    void  slotChangeWindowTitle(const QString& str){
        setWindowTitle(str);
    }
};

#endif // SDIPROGRAM_ADOV_H
