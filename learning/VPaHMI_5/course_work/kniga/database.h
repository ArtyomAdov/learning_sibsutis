#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

#define DATABASE_HOSTNAME   "RecipeBook"
#define DATABASE_NAME       "D2.db"

#define TABLE                   "TableExample"
#define TABLE_DATE              "Date"
#define TABLE_DATECOOK              "DateCook"
#define TABLE_KITCHEN           "Kitchen"
#define TABLE_TYPE            "Type"
#define TABLE_NAME              "Name"
#define TABLE_FAVORITES         "Favorites"
#define TABLE_RECIPE            "Recipe"

class database : public QObject
{
    Q_OBJECT
public:
    explicit database(QObject *parent = 0);

    void connectToDataBase();
    bool inserIntoTable(const QVariantList &data);
private:
    QSqlDatabase    db;
    
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTable();


signals:
    
public slots:
    
};

#endif // DATABASE_H
