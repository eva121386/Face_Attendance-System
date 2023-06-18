
#ifndef QSQLITEDB_H
#define QSQLITEDB_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <iostream>
#include <string>
#include <map>

using namespace std;

typedef struct
{
    int id;
    QString name;
    QString time;
}w2dba;

class QSqlitedb
{
public:
    QSqlitedb();
    // �����ݿ�
    bool openDb(void);
    // �������ݱ�
    void createTable(void);
    // �ж����ݱ��Ƿ����
    bool isTableExist(QString& tableName);
    // ��ѯȫ������
    map<int,string> queryTable();
    // ��������
    void singleInsertData(string name,string time); // ���뵥������
    void moreInsertData(QList<w2dba> &moreData); // �����������
    // �޸�����
    void modifyData(int id, QString name, QString time);
    // ɾ������
    void deleteData(int id);
    //ɾ�����ݱ�
    void deleteTable(QString& tableName);
    // �ر����ݿ�
    void closeDb(void);
private:
    QSqlDatabase database;// ���ڽ��������ݿ������
};

#endif // QSQLITEDB_H
