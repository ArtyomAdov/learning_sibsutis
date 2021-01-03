#include "mainwindow1.h"
#include "ui_mainwindow1.h"
#include "dialogadd.h"
#include "helper.h"

MainWindow1::MainWindow1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow1)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(), this->geometry().height());
    db = new database();
    db->connectToDataBase();

        /* После чего производим наполнение таблицы базы данных
         * контентом, который будет отображаться в TableView
         * */

        /* Инициализируем модель для представления данных
         * с заданием названий колонок
         * */
        this->setupModel(TABLE,
                         QStringList() << trUtf8("id")
                                       << trUtf8("Название")
                                       << trUtf8("Кухня")
                                       << trUtf8("Тип блюда")
                                       << trUtf8("Дата создания")
                         <<trUtf8("Дата приготовления")
                         <<trUtf8("Избранное")
                         <<trUtf8("Рецепт")
                   );

        /* Инициализируем внешний вид таблицы с данными
         * */
        this->createUI();
}

MainWindow1::~MainWindow1()
{
    delete ui;
}

void MainWindow1::setupModel(const QString &tableName, const QStringList &headers)
{
    /* Производим инициализацию модели представления данных
     * с установкой имени таблицы в базе данных, по которому
     * будет производится обращение в таблице
     * */
    model = new QSqlTableModel(this);
    model->setTable(tableName);

    /* Устанавливаем названия колонок в таблице с сортировкой данных
     * */
    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    // Устанавливаем сортировку по возрастанию данных по нулевой колонке
    model->sort(1, Qt::AscendingOrder);
}

void MainWindow1::createUI()
{
    ui->tableView->setModel(model);     // Устанавливаем модель на TableView
    QString str;
    ui->kitchen_comboBox->addItem("");
    ui->comboBox_2->addItem("");
    for(int i = 0; i < model->rowCount(); i++){
        ui->tableView->setRowHidden(i, false);
        str = model->data(model->index(i, 2)).toString();
        int counter = 0;
        for(int j = 0; j < ui->kitchen_comboBox->count(); j++){
            if (str == ui->kitchen_comboBox->itemText(j)){
                counter++;
            }
        }
        if(counter == 0){
            ui->kitchen_comboBox->addItem(str);
        }
        str = model->data(model->index(i, 3)).toString();
        int counter1 = 0;
        for(int j = 0; j < ui->kitchen_comboBox->count(); j++){
            if (str == ui->comboBox_2->itemText(j)){
                counter1++;
            }
        }
        if(counter1 == 0){
            ui->comboBox_2->addItem(str);
        }
    }
    ui->tableView->setColumnHidden(0, true);    // Скрываем колонку с id записей
    ui->tableView->setColumnHidden(7, true);
    ui->tableView->setColumnHidden(5, true);
    // Разрешаем выделение строк
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    model->select(); // Делаем выборку данных из таблицы
}

void MainWindow1::on_action_triggered()
{
    DialogAdd *addDeviceDialog = new DialogAdd();
    connect(addDeviceDialog, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    /* Выполняем запуск диалогового окна
     * */
    addDeviceDialog->setWindowTitle(trUtf8("Добавить Рецепт"));

    QString str;
    if(addDeviceDialog->exec() == 1){
        for(int i = 0; i < model->rowCount(); i++){
            ui->tableView->setRowHidden(i, false);
            str = model->data(model->index(i, 2)).toString();
            qDebug()<<str + "=str";
            int counter = 0;
            for(int j = 0; j < ui->kitchen_comboBox->count(); j++){
                if (str == ui->kitchen_comboBox->itemText(j)){
                    counter++;
                }
            }
            if(counter == 0){
                ui->kitchen_comboBox->addItem(str);
            }
            str = model->data(model->index(i, 3)).toString();
            qDebug()<<str + "=str";
            int counter1 = 0;
            for(int j = 0; j < ui->kitchen_comboBox->count(); j++){
                if (str == ui->comboBox_2->itemText(j)){
                    counter1++;
                }
            }
            if(counter1 == 0){
                ui->comboBox_2->addItem(str);
            }
        }
    }
    ui->recipe_textEdit->setEnabled(false);
    ui->date_textEdit->setEnabled(false);
    ui->Favorites_checkBox->setEnabled(false);
    ui->change_recipe_pushButton_2->setEnabled(false);
    ui->date_checkBox->setEnabled(false);
    ui->Name_label_4->setEnabled(false);
}

void MainWindow1::slotUpdateModels()
{
    model->select();
}

void MainWindow1::on_action_2_triggered()
{
    int row;
    QItemSelectionModel    *selectModel;
    QModelIndexList         indexes;
    QModelIndex             index;

        // Узнаем выделенную строку
    selectModel = ui->tableView->selectionModel();
    indexes = selectModel->selectedIndexes();

    foreach(index, indexes){
        QString str;
        row = index.row();
        if (!model->removeRows(row,1))
        {
            str = model->lastError().text();
            qDebug() << str << "\n\r";
            break;
        }
    }
    model->select();
    ui->recipe_textEdit->setEnabled(false);
    ui->date_textEdit->setEnabled(false);
    ui->Favorites_checkBox->setEnabled(false);
    ui->change_recipe_pushButton_2->setEnabled(false);
    ui->date_checkBox->setEnabled(false);
    ui->Name_label_4->setEnabled(false);
}

void MainWindow1::on_action_3_triggered()
{
    this->close();
}

void MainWindow1::on_Favorites_checkBox_clicked()
{
    int row;
    QItemSelectionModel    *selectModel;
    QModelIndexList         indexes;
    QModelIndex             index;

    selectModel = ui->tableView->selectionModel();
    indexes = selectModel->selectedIndexes();
    foreach(index, indexes){
        row = index.row();
        if(ui->Favorites_checkBox->isChecked()){
            model->setData(model->index(row,6),"Да");
        }
        else{
            model->setData(model->index(row,6),"Нет");
        }
    }
    model->submitAll();
    model->select();
    ui->tableView->selectRow(index.row());
}

void MainWindow1::on_date_checkBox_clicked()
{
    int row;
    QItemSelectionModel    *selectModel;
    QModelIndexList         indexes;
    QModelIndex             index;

    selectModel = ui->tableView->selectionModel();
    indexes = selectModel->selectedIndexes();
    foreach(index, indexes){
        row = index.row();
        if(ui->date_checkBox->isChecked()){
            model->setData(model->index(row,5),QDate::currentDate());
        }

        qDebug() <<"index.sibling(index.row(), 5).data().toString()";
        ui->date_textEdit->setText("Дата приготовления \n" + index.sibling(index.row(), 5).data().toString());
    }
    model->submitAll();
    model->select();
    ui->tableView->selectRow(index.row());
}

void MainWindow1::on_change_recipe_pushButton_2_clicked()
{
    QItemSelectionModel    *selectModel;
    QModelIndexList         indexes;
    QModelIndex             index;

    selectModel = ui->tableView->selectionModel();
    indexes = selectModel->selectedIndexes();
    index = indexes.first();
    QString str = index.sibling(index.row(), 7).data().toString();
    DialogchangeRecipe *changeDeviceDialog = new DialogchangeRecipe(str, index.row());

    connect(changeDeviceDialog, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));
    changeDeviceDialog->setWindowTitle(trUtf8("Редактировать рецепт"));
    changeDeviceDialog->exec();
    ui->recipe_textEdit->setText(index.sibling(index.row(), 7).data().toString());
    ui->tableView->selectRow(index.row());


    /* Выполняем запуск диалогового окна
     * */

}

void MainWindow1::on_sort_comboBox_currentIndexChanged(int index)
{
    for(int i = 0; i < model->rowCount(); i++){
        ui->tableView->setRowHidden(i, false);
    }
    switch(index){
        case 0:{
            model->sort(1, Qt::AscendingOrder);
            break;
        }
        case 1:{
            model->sort(1, Qt::DescendingOrder);
            break;
        }
        case 2:{
            model->sort(6, Qt::AscendingOrder);
            break;
        }
        case 3:{
            model->sort(2, Qt::AscendingOrder);
            break;
        }
        case 4:{
            model->sort(2, Qt::DescendingOrder);
            break;
        }
    }
    ui->recipe_textEdit->setEnabled(false);
    ui->date_textEdit->setEnabled(false);
    ui->Favorites_checkBox->setEnabled(false);
    ui->change_recipe_pushButton_2->setEnabled(false);
    ui->date_checkBox->setEnabled(false);
    ui->Name_label_4->setEnabled(false);
}

void MainWindow1::on_kitchen_comboBox_currentIndexChanged(int index)
{
    for(int i = 0; i < model->rowCount(); i++){
        ui->tableView->setRowHidden(i, false);
    }
    ui->comboBox_2->setEnabled(false);
    if(index == 0){
        ui->comboBox_2->setEnabled(true);
        for(int i = 0; i < model->rowCount(); i++){
            ui->tableView->setRowHidden(i, false);
        }
    }
    else{
        QString str = ui->kitchen_comboBox->itemText(index);
        for(int i = 0; i < model->rowCount(); i++){
            if(str == model->data(model->index(i, 2)).toString()){
                ui->tableView->setRowHidden(i, false);
            }
            else{
                ui->tableView->setRowHidden(i, true);
            }
        }
    }
}

void MainWindow1::on_comboBox_2_currentIndexChanged(int index)
{
    for(int i = 0; i < model->rowCount(); i++){
        ui->tableView->setRowHidden(i, false);
    }
    ui->kitchen_comboBox->setEnabled(false);
    if(index == 0){
        ui->kitchen_comboBox->setEnabled(true);
        for(int i = 0; i < model->rowCount(); i++){
            ui->tableView->setRowHidden(i, false);
        }
    }
    else{
        QString str = ui->comboBox_2->itemText(index);
        for(int i = 0; i < model->rowCount(); i++){
            if(str == model->data(model->index(i, 3)).toString()){
                ui->tableView->setRowHidden(i, false);
            }
            else{
                ui->tableView->setRowHidden(i, true);
            }
        }
    }
}

void MainWindow1::on_pushButton_clicked()
{
    QString str = ui->namefind_textEdit->toPlainText();
    if(!str.isEmpty()){
        QString str1;
        for(int i = 0; i < model->rowCount(); i++){
            str1 = model->data(model->index(i,1)).toString();
            if(str1.contains(str, Qt::CaseInsensitive)){
                ui->tableView->setRowHidden(i, false);
            }
            else{
                ui->tableView->setRowHidden(i, true);
            }
        }
    }
}

void MainWindow1::on_pushButton_2_clicked()
{
    for(int i = 0; i < model->rowCount(); i++){
        ui->tableView->setRowHidden(i, false);
    }
}

void MainWindow1::on_tableView_clicked(const QModelIndex &index)
{
    ui->recipe_textEdit->setEnabled(true);
    ui->date_textEdit->setEnabled(true);
    ui->Favorites_checkBox->setEnabled(true);
    ui->change_recipe_pushButton_2->setEnabled(true);
    ui->date_checkBox->setEnabled(true);
    ui->Name_label_4->setEnabled(true);

    ui->Name_label_4->setText(index.sibling(index.row(),1).data().toString());
    ui->date_textEdit->setText("Дата приготовления \n" + index.sibling(index.row(), 5).data().toString());
    ui->date_checkBox->setChecked(false);
    ui->recipe_textEdit->setText(index.sibling(index.row(), 7).data().toString());
    QString str;
    str = index.sibling(index.row(), 6).data().toString();
    if(str == "Да"){
        ui->Favorites_checkBox->setChecked(true);
    }
    else{
        ui->Favorites_checkBox->setChecked(false);
    }
}

void MainWindow1::on_action_4_triggered()
{
    QString str = qApp->applicationDirPath();
    QString str1 = "index.html";
    helper *helpBrowser = new helper(str, str1);
    helpBrowser->show();
}
