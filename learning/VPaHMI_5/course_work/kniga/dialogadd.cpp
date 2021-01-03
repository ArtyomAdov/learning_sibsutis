#include "dialogadd.h"
#include "ui_dialogadd.h"
#include <QDebug>
#include <QDate>

DialogAdd::DialogAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAdd)
{
    ui->setupUi(this);

    /* Метода для инициализации модели,
     * из которой будут транслироваться данные
     * */
    setupModel();
    model->insertRow(model->rowCount(QModelIndex()));
    mapper->toLast();
}

DialogAdd::~DialogAdd()
{
    delete ui;
}

/* Метод настройки модели данных и mapper
 * */
void DialogAdd::setupModel()
{
    /* Инициализируем модель и делаем выборку из неё
     * */
    model = new QSqlTableModel(this);
    model->setTable(TABLE);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    /* Инициализируем mapper и привязываем
     * поля данных к объектам LineEdit
     * */
    mapper = new QDataWidgetMapper();
    mapper->setModel(model);
    mapper->addMapping(ui->Name_lineEdit, 1);
    mapper->addMapping(ui->Kitchen_lineEdit_2, 2);
    mapper->addMapping(ui->Type_lineEdit_3, 3);
    mapper->addMapping(ui->DateEdit, 4);
    mapper->addMapping(ui->Cook_dateEdit_2, 5);
    mapper->addMapping(ui->comboBox, 6);
    mapper->addMapping(ui->Recipe_textEdit, 7);
    /* Ручное подтверждение изменения данных
     * через mapper
     * */
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);



}




void DialogAdd::on_buttonBox_accepted()
{
        mapper->submit();
        qDebug() << model->submitAll();
        qDebug() << model->lastError();
        emit signalReady();
        this->close();

}

/* Метод изменения состояния активности кнопок пролистывания
 * */

void DialogAdd::on_buttonBox_rejected()
{
    this->close();
}
