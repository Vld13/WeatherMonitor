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

        QVector<QString> m_date;
        QVector<double> m_temp;
        QVector<double> m_hum;


    public:
        DbManager();
        ~DbManager();
        void addMeasurement(int, int); // Добавляем записи в БД
        QVector<QString> getDate(); // Берем последние 10 записей
        QVector<double> getTemp();
        QVector<double> getHum();
        void viewDb(); // Просмотр всей БД
        void clearDb(); // Очистка БД
};

#endif // DBMANAGER_H
