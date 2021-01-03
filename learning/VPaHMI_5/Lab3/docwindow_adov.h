#ifndef DOCWINDOW_ADOV_H
#define DOCWINDOW_ADOV_H

#include <QTextEdit>
#include <QFileDialog>
#include <QTextStream>
#include <QColorDialog>
#include <QtWidgets>

class DocWindow_Adov: public QTextEdit{
    Q_OBJECT
private:
    QString m_strFileName;
public:
    DocWindow_Adov(QWidget* pwgt = 0);
signals:
    void changeWindowTitle(const QString&);

public slots:
    void slotLoad();
    void slotSave();
    void slotSaveAs();
    void slotColor();
};

#endif // DOCWINDOW_ADOV_H
