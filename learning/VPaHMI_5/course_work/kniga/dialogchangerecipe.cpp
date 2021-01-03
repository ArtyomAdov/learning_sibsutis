#include "dialogchangerecipe.h"
#include "ui_dialogchangerecipe.h"

DialogchangeRecipe::DialogchangeRecipe(QString str, int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogchangeRecipe)
{
    ui->setupUi(this);
    setupModel();
    mapper->setCurrentModelIndex(model->index(row,0));
}

DialogchangeRecipe::~DialogchangeRecipe()
{
    delete ui;
}

void DialogchangeRecipe::setupModel()
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
    mapper->addMapping(ui->textEdit, 7);
    /* Ручное подтверждение изменения данных
     * через mapper
     * */
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

}

void DialogchangeRecipe::on_buttonBox_accepted()
{
    mapper->submit();
    model->submitAll();
    qDebug() << model->lastError();
    emit signalReady();
    this->close();
}

/* Метод изменения состояния активности кнопок пролистывания
 * */

void DialogchangeRecipe::on_buttonBox_rejected()
{
    this->close();
}
