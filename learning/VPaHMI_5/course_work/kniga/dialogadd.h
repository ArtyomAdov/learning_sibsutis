#ifndef DIALOGADD_H
#define DIALOGADD_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QMessageBox>

#include "database.h"

namespace Ui {
class DialogAdd;
}

class DialogAdd : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAdd(QWidget *parent = 0);
    ~DialogAdd();

signals:
    void signalReady();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();


private:
    Ui::DialogAdd               *ui;
    QSqlTableModel              *model;
    QDataWidgetMapper           *mapper;

private:
    void setupModel();
};

#endif // DIALOGADD_H
