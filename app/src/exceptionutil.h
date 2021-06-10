#ifndef EXCEPTIONUTIL_H
#define EXCEPTIONUTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string>

class ExceptionUtil
{
public:
    explicit ExceptionUtil();
    ~ExceptionUtil();

    static void setExceptionHandler(const std::string strAppName);

    static std::string getAppName();

    static std::string getAppRunPath();

    static std::string getExceptionName() {return m_strAppName;}

private:
    static std::string m_strAppName;

};

#endif // EXCEPTIONUTIL_H
