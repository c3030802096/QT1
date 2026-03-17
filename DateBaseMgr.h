#ifndef DATEBASEMGR_H
#define DATEBASEMGR_H

#include <QObject>
#include "singleton.h"
#include <QSqlDatabase>
#include <QtSql>
#include <QSqlQuery>

class DateBaseMgr : public QObject, public Singleton<DateBaseMgr>
                    ,public std::enable_shared_from_this<DateBaseMgr>
{
    Q_OBJECT
public:
    DateBaseMgr();

    QSqlDatabase db;

signals:
};

#endif // DATEBASEMGR_H
