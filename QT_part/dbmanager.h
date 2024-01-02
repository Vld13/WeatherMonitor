#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDateTime>

class DbManager
{
    private:
        QSqlDatabase m_db;
        QSqlQuery m_query;

    public:
        DbManager();
        ~DbManager();
        void addMeasurement(int, int);
        void viewDb();
        void clearDb();
};

#endif // DBMANAGER_H
