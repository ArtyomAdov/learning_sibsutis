#ifndef DIALOGCHANGERECIPE_H
#define DIALOGCHANGERECIPE_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QMessageBox>
#include <QModelIndex>

#include "database.h"

namespace Ui {
class DialogchangeRecipe;
}

class DialogchangeRecipe : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogchangeRecipe(QString str, int row, QWidget *parent = 0);
    ~DialogchangeRecipe();

signals:
    void signalReady();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::DialogchangeRecipe *ui;

    QSqlTableModel              *model;
    QDataWidgetMapper           *mapper;

private:
    void setupModel();
};

#endif // DIALOGCHANGERECIPE_H
