#include "docwindow_adov.h"

DocWindowAdov::DocWindowAdov(QWidget* pwgt): QTextEdit (pwgt)
{

}

void DocWindowAdov::slotLoad(){
    QString str = QFileDialog::getOpenFileName();
    if(str.isEmpty()){
        return;
    }
    QFile file(str);
    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream (&file);
        setPlainText(stream.readAll());
        file.close();

        m_strFileName = str;
        emit changeWindowTitle(QFileInfo(m_strFileName).fileName()+" - Блокнот");
    }
}

void DocWindowAdov::slotSaveAs(){
    QString str = QFileDialog::getSaveFileName(0,m_strFileName);
    if(!str.isEmpty()){
        m_strFileName = str;
        slotSave();
    }
}

void DocWindowAdov::slotSave(){
    if(m_strFileName.isEmpty()){
        slotSaveAs();
        return;
    }

    QFile file(m_strFileName);

    if(file.open(QIODevice::WriteOnly)){
        QTextStream(&file)<<toPlainText();
    }
    QMessageBox::about(this,"Оповещение","Файл успешно сохранен");
    file.close();
    emit changeWindowTitle(QFileInfo(m_strFileName).fileName()+" - Блокнот");
}

void DocWindowAdov::slotColor(){
    QColor color = QColorDialog::getColor();
    if(!color.isValid()){
        return;
    }
    this->setTextColor(color);
}

