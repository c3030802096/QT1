// ----------------------------------------------------------------------------
// QtBCrypt
//
// https://github.com/andreybutov/qt-bcrypt
//
// Andrey Butov
// andreybutov@antair.com
//
// ----------------------------------------------------------------------------



#ifndef __QT_BCRYPT_H__
#define __QT_BCRYPT_H__



#include <QString>



class QtBCrypt
{
public:
    static QString generateSalt();
    static QString hashPassword(const QString& password, const QString& salt);
    static bool validatePassword(const QString& inputPassword, const QString& storedHashedPassword); // 添加静态声明

private:
    static void generateRandomBytes(char* outBuffer, int bufferSize);
};



#endif // __QT_BCRYPT_H__
