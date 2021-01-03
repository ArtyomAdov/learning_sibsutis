#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QModelIndex>
#include "database.h"
#include "dialogchangerecipe.h"

namespace Ui {
class MainWindow1;
}

class MainWindow1 : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow1(QWidget *parent = 0);
    ~MainWindow1();
    
private slots:
    void on_action_triggered();
    void slotUpdateModels();

    void on_action_2_triggered();

    void on_action_3_triggered();


    void on_Favorites_checkBox_clicked();

    void on_date_checkBox_clicked();

    void on_change_recipe_pushButton_2_clicked();

    void on_sort_comboBox_currentIndexChanged(int index);

    void on_kitchen_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_action_4_triggered();

private:
    Ui::MainWindow1 *ui;

    database        *db;
    QSqlTableModel  *model;

    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
};

#endif // MAINWINDOW1_H
