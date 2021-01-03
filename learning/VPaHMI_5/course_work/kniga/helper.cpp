#include "helper.h"
#include "ui_helper.h"
#include <QDebug>
#include <QTextCodec>

helper::helper(QString strPath, QString strFileName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::helper)
{
    ui->setupUi(this);
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));
    ui->textBrowser->setSearchPaths(QStringList() << strPath);
    ui->textBrowser->setSource(QString(strFileName));
    str1 = QStringList() << "index.html" << "create.html" << "delete.html" << "search.html" << "sort.html" << "edit.html" << "add.html";
    counter = 0;
    if(ui->textBrowser->source() == QString(strFileName)){
        ui->Back_pushButton->setEnabled(false);
    }
}

helper::~helper()
{
    delete ui;
}

void helper::on_Home_pushButton_2_clicked()
{
    ui->textBrowser->setSource(QString("index.html"));
    counter = 0;
    ui->Back_pushButton->setEnabled(false);
    ui->Forward_pushButton_3->setEnabled(true);
}

void helper::on_Forward_pushButton_3_clicked()
{
    counter++;
    ui->textBrowser->setSource(QString(str1[counter]));
    if(counter == 6){
        ui->Forward_pushButton_3->setEnabled(false);
    }
    ui->Back_pushButton->setEnabled(true);
}

void helper::on_Back_pushButton_clicked()
{
    counter--;
    ui->textBrowser->setSource(QString(str1[counter]));
    if(counter == 0){
        ui->Back_pushButton->setEnabled(false);
    }
    ui->Forward_pushButton_3->setEnabled(true);
}

void helper::on_textBrowser_anchorClicked(const QUrl &arg1)
{
    int i;
    for(i = 0; i < str1.count(); i++){
        if(arg1.toString() == str1[i]) break;
    }
    counter = i;
    if(counter == 0){
        ui->Back_pushButton->setEnabled(false);
        ui->Forward_pushButton_3->setEnabled(true);
    }
    else if(counter == 6){
            ui->Forward_pushButton_3->setEnabled(false);
            ui->Back_pushButton->setEnabled(true);
        }
    else{
        ui->Forward_pushButton_3->setEnabled(true);
        ui->Back_pushButton->setEnabled(true);
    }
}
