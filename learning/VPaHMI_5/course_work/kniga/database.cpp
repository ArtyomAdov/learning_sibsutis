#include "database.h"

database::database(QObject *parent) :
    QObject(parent)
{
}

void database::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */
    if(!QFile("C:" DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        qDebug()<<"q";
        this->openDataBase();
    }
}


bool database::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTable()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "restore Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

/* Метод для открытия базы данных
 * */
bool database::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("C:" DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

/* Методы закрытия базы данных
 * */
void database::closeDataBase()
{
    db.close();
}

/* Метод для создания таблицы в базе данных
 * */
bool database::createTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE " ( "
                                                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                                TABLE_NAME      " VARCHAR(255)            NOT NULL,"
                                                TABLE_KITCHEN   " VARCHAR(255)            NOT NULL,"
                                                TABLE_TYPE      " VARCHAR(255)            NOT NULL,"
                                                TABLE_DATE      " DATE    NOT NULL,"
                                                TABLE_DATECOOK  " DATE NOT NULL,"
                                                TABLE_FAVORITES " CHAR (3) NOT NULL,"
                                                TABLE_RECIPE    " VARCHAR(255)            NOT NULL"
                        " )"
                    )){
        qDebug() << "create table DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

/* Метод для вставки записи в базу данных
 * */
bool database::inserIntoTable(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO " TABLE " ( " TABLE_NAME ", "
                  TABLE_KITCHEN ", "
                  TABLE_TYPE ", "
                  TABLE_DATE ", "
                  TABLE_DATECOOK ", "
                  TABLE_FAVORITES ", "
                  TABLE_RECIPE " ) "
"VALUES (:Name, :Kitchen, :Type, :Date, :DateCook, :Favorites, :Recipe )");
query.bindValue(":Name",     data[0].toString());
query.bindValue(":Kitchen",        data[1].toString());
query.bindValue(":Type",      data[2].toString());
query.bindValue(":Date",     data[3].toDate());
query.bindValue(":DateCook",     data[4].toDate());
query.bindValue(":Favorites",     data[5].toInt());
query.bindValue(":Recipe",     data[6].toString());
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "insert error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}


