
#include "qsqlitedb.h"

QSqlitedb::QSqlitedb()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        // ������SQlite���ݿ������
        database = QSqlDatabase::addDatabase("QSQLITE");
        // �������ݿ��ļ�������
        database.setDatabaseName("MyDataBase.db");
    }
    if(openDb()){
        qDebug()<<"open db success";
    }
    QString table_name=QString("signIn");
    if(!isTableExist(table_name)){
        createTable();
    }

}

// �����ݿ�
bool QSqlitedb::openDb()
{
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        // do something
    }

    return true;
}

// �������ݱ�
void QSqlitedb::createTable()
{
    // ����ִ��sql���Ķ���
    QSqlQuery sqlQuery;
    sqlQuery.clear();
    // �����������ݿ��sql����ַ���
    QString createSql = QString("CREATE TABLE IF NOT EXISTS signIn (id INT PRIMARY KEY NOT NULL, name TEXT NOT NULL,time TEXT NOT NULL);");
    sqlQuery.prepare(createSql);
    // ִ��sql���
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to create table. " << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
}

// �ж����ݿ���ĳ�����ݱ��Ƿ����
bool QSqlitedb::isTableExist(QString& tableName)
{
    QSqlDatabase database = QSqlDatabase::database();
    if(database.tables().contains(tableName))
    {
        return true;
    }

    return false;
}

// ��ѯȫ������
map<int,string> QSqlitedb::queryTable()
{
    map<int,string> datadb;
    QSqlQuery sqlQuery;
    sqlQuery.clear();
    sqlQuery.exec("SELECT * FROM signIn;");
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            int id = sqlQuery.value(0).toInt();
            QString name = sqlQuery.value(1).toString();
            QString time = sqlQuery.value(2).toString();
            datadb.insert(map<int,string>::value_type(id,name.toStdString()+" "+time.toStdString()));
        }
    }
    return datadb;
}

// ���뵥������
void QSqlitedb::singleInsertData(string name, string time)
{   int id=0;
    QSqlQuery sqlQuery;
    sqlQuery.clear();
    sqlQuery.prepare("SELECT COUNT(*) FROM signIn;");

    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to insert data. " << sqlQuery.lastError();
    }
    else
    {
        while (sqlQuery.next()) {
            id=sqlQuery.value(0).toInt();
        }
    }

    sqlQuery.clear();
    sqlQuery.prepare("INSERT INTO signIn VALUES(:id,:name,:time);");
    sqlQuery.bindValue(":id", id);
    sqlQuery.bindValue(":name", QString::fromStdString(name));
    sqlQuery.bindValue(":time", QString::fromStdString(time));
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to insert data. " << sqlQuery.lastError();
    }
    else
    {
        // do something
    }
}

// �����������
void QSqlitedb::moreInsertData(QList<w2dba>& moredb)
{
    // ���ж�����ݵĲ���ʱ���������ð󶨽���������
    QSqlQuery sqlQuery;
    sqlQuery.prepare("INSERT INTO student VALUES(?,?,?)");
    QVariantList idList,nameList,timeList;
    for(int i=0; i< moredb.size(); i++)
    {
        idList <<  moredb.at(i).id;
        nameList << moredb.at(i).name;
        timeList << moredb.at(i).time;
    }
    sqlQuery.addBindValue(idList);
    sqlQuery.addBindValue(nameList);
    sqlQuery.addBindValue(timeList);

    if (!sqlQuery.execBatch()) // �������������������������
    {
        qDebug() << sqlQuery.lastError();
    }
}

// �޸�����
void QSqlitedb::modifyData(int id, QString name, QString time)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("UPDATE student SET name=?,time=? WHERE id=?");
    sqlQuery.addBindValue(name);
    sqlQuery.addBindValue(time);
    sqlQuery.addBindValue(id);
    if(!sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "updated data success!";
    }
}

// ɾ������
void QSqlitedb::deleteData(int id)
{
    QSqlQuery sqlQuery;

    sqlQuery.exec(QString("DELETE FROM student WHERE id = %1").arg(id));
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"deleted data success!";
    }
}

//ɾ�����ݱ�
void QSqlitedb::deleteTable(QString& tableName)
{
    QSqlQuery sqlQuery;

    sqlQuery.exec(QString("DROP TABLE %1").arg(tableName));
    if(sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "deleted table success";
    }
}

void QSqlitedb::closeDb(void)
{
    database.close();
}
