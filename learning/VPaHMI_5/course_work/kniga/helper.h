#ifndef HELPER_H
#define HELPER_H

#include <QWidget>

namespace Ui {
class helper;
}

class helper : public QWidget
{
    Q_OBJECT
    
public:
    explicit helper(QString strPath, QString strFileName, QWidget *parent = 0);
    ~helper();
    
private slots:
    void on_Home_pushButton_2_clicked();

    void on_Forward_pushButton_3_clicked();

    void on_Back_pushButton_clicked();

    void on_textBrowser_anchorClicked(const QUrl &arg1);

private:
    Ui::helper *ui;
    QStringList str1;
    int counter;
};

#endif // HELPER_H
