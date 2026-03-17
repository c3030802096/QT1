#ifndef USERMGR_H
#define USERMGR_H

#include <QObject>
#include "singleton.h"

class UserMgr: public QObject, public Singleton<UserMgr>
                ,public std::enable_shared_from_this<UserMgr>
{
public:
    UserMgr();


    QString user_id;
    QString user_permission;

};

#endif // USERMGR_H
