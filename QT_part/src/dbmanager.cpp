#include "dbmanager.h"

DbManager::DbManager()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("WM_DB");

    if(!m_db.open()) {
        qDebug() << m_db.lastError().text();
    } else qDebug() << "db OK!";

    QSqlQuery m_query(m_db);

    if(!m_query.exec(
                "CREATE TABLE measurements("
                "id INT,"
                "date  DATETIME NOT NULL,"
                "temp INT NOT NULL,"
                "hum INT NOT NULL"
                ")"
    )) {
        qDebug() << m_db.lastError().text();
    }
}

DbManager::~DbManager()
{
    m_db.close();
}

void DbManager::addMeasurement(int temp, int hum)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();

    QSqlQuery m_query(m_db);

    m_query.prepare("INSERT INTO measurements (date, temp, hum)"
                    "VALUES (:date, :temp, :hum)");
    m_query.bindValue(":date", currentDateTime);
    m_query.bindValue(":temp", temp);
    m_query.bindValue(":hum", hum);
    m_query.exec();
}

QVector<QString> DbManager::getDate()
{
    QSqlQuery m_query(m_db);
    // Берем последние 10 записей
    m_query.prepare("SELECT * FROM measurements ORDER BY date DESC LIMIT 10");
    m_query.exec();

    int idDate = m_query.record().indexOf("date");

    m_date.clear();
    while(m_query.next())
    {
        m_date.append(m_query.value(idDate).toString());
    }

    return m_date;
}

QVector<double> DbManager::getTemp()
{
    QSqlQuery m_query(m_db);
    // Берем последние 10 записей
    m_query.prepare("SELECT * FROM measurements ORDER BY temp DESC LIMIT 10");
    m_query.exec();

    int idTemp = m_query.record().indexOf("temp");

    m_temp.clear();
    while(m_query.next())
    {
        m_temp.append(m_query.value(idTemp).toInt());
    }

    return m_temp;
}

QVector<double> DbManager::getHum()
{
    QSqlQuery m_query(m_db);
    // Берем последние 10 записей
    m_query.prepare("SELECT * FROM measurements ORDER BY hum DESC LIMIT 10");
    m_query.exec();

    int idHum = m_query.record().indexOf("hum");

    m_hum.clear();
    while(m_query.next())
    {
        m_hum.append(m_query.value(idHum).toInt());
    }

    return m_hum;
}

void DbManager::viewDb()
{
    QSqlQuery m_query(m_db);
    m_query.prepare("SELECT * FROM measurements");
    m_query.exec();

    int idDate = m_query.record().indexOf("date");
    int idTemp = m_query.record().indexOf("temp");
    int idHum = m_query.record().indexOf("hum");

    while(m_query.next())
    {
       QString date = m_query.value(idDate).toString();
       QString temp = m_query.value(idTemp).toString();
       QString hum = m_query.value(idHum).toString();

       qDebug() << date << " " << temp << " " << hum;
    }
}

void DbManager::clearDb()
{
    QSqlQuery m_query(m_db);
    m_query.prepare("DELETE FROM measurements");
    m_query.exec();
}
