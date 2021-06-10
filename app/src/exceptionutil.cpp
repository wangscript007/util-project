#include "exceptionutil.h"
#include <signal.h>
#if defined (__linux__)
#include <sys/time.h>
#include <unistd.h>
#include <execinfo.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>
#else
#include <time.h>
#include <windows.h>
#endif


std::string getFormatTime()
{
    time_t stTimeNow = time(NULL);
    char szTmp[32] = {0};
    strftime(szTmp, sizeof(szTmp), "%Y%m%d_%H%M%S", localtime(&stTimeNow));

    int iMillsec = 0;
#if defined (__linux__)
    struct timeval tv;
    gettimeofday(&tv, NULL);
    iMillsec = tv.tv_usec / 1000;
#else
    SYSTEMTIME stSysTime;
    GetLocalTime(&stSysTime);
    iMillsec = stSysTime.wMilliseconds;
#endif
    char szTime[32] = {0};
    sprintf(szTime, "%s.%03d", szTmp, iMillsec);
    std::string strTime(szTime);
    return strTime;
}

std::string getDirectory()
{
    std::string strPath = "";
#if defined (__linux__)
    char szAbsPath[1024] = {0};
    ssize_t iPathLen = readlink("/proc/self/exe", szAbsPath, 1024); // 获取可执行程序的绝对路径
    if(0 < iPathLen && iPathLen < 1024)
    {
        std::string strFullPath(szAbsPath);
        size_t iPos = strFullPath.find_last_of('/');
        if(iPos != std::string::npos)
        {
            strPath = strFullPath.substr(0, iPos); //return the directory without the file name
        }
    }
#endif

    return strPath;
}

static void writeExceptionHandler(int iSigNum)
{
    signal(iSigNum, SIG_DFL);

#if defined (__linux__)
    void *pArray[32];

    int iSize = backtrace(pArray, 32);
    char **pInfos = (char **)backtrace_symbols(pArray, iSize);

    std::string strDumpFolderPath = getDirectory() + "/dump";
    std::string strCoreDumpFilePath = "";
    if (0 != access(strDumpFolderPath.c_str(), 0))
    {
        int iResult = mkdir(strDumpFolderPath.c_str(), S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
        if (0 == iResult)
        {
            strCoreDumpFilePath = strDumpFolderPath + "/";
        }
    }
    else
    {
        strCoreDumpFilePath = strDumpFolderPath + "/";
    }

    strCoreDumpFilePath += "core-" + ExceptionUtil::getExceptionName() + "_" + getFormatTime();
    FILE *pFile = fopen(strCoreDumpFilePath.c_str(), "a+");
    if(pFile)
    {
        fprintf(pFile, "Stack Trace:\n");
        for(int i = 0; i < iSize; ++i)
        {
            fprintf(pFile, "%d %s \n", i, pInfos[i]);
        }

        fclose(pFile);
    }

    free(pInfos);
#endif
    exit(1);

    return;
}

std::string ExceptionUtil::m_strAppName = "default";

ExceptionUtil::ExceptionUtil()
{

}

ExceptionUtil::~ExceptionUtil()
{

}

void ExceptionUtil::setExceptionHandler(const std::string strAppName)
{
    m_strAppName = strAppName;
    signal(SIGSEGV, writeExceptionHandler);
    signal(SIGABRT, writeExceptionHandler);


#if defined (__linux__)
    // 设置生成dump文件
    struct rlimit rlmt;
    rlmt.rlim_cur = (rlim_t)RLIM_SAVED_MAX;
    rlmt.rlim_max  = (rlim_t)RLIM_SAVED_MAX;

    if (setrlimit(RLIMIT_CORE, &rlmt) == -1)
    {
        return;
    }

    printf("After set rlimit CORE dump current is: %d, max is: %d\n", (int)(rlmt.rlim_cur), (int)(rlmt.rlim_max));
#endif

    return;
}

std::string ExceptionUtil::getAppName()
{
    std::string strAppName = "unknown";

#if defined (__linux__)
    char szAbsPath[1024] = {0};
    ssize_t iPathLen = readlink("/proc/self/exe", szAbsPath, 1024); // 获取可执行程序的绝对路径
    if(0 < iPathLen && iPathLen < 1024)
    {
        std::string strFullPath(szAbsPath);
        size_t iPos = strFullPath.find_last_of('/');
        if(iPos != std::string::npos)
        {
            strAppName = strFullPath.substr(iPos + 1);
        }
    }
#else
    //获取应用程序目录
    char szAppPath[MAX_PATH] = {0};
    //memset(szAppPath, 0, MAX_PATH);
    GetModuleFileNameA(NULL, szAppPath, MAX_PATH);

    //获取应用程序名称
    char szExe[MAX_PATH] = "";
    char *pBuf = NULL;
    char *pLine = strtok_s(szAppPath, "\\", &pBuf); // 字符串分割函数
    while(pLine)
    {
        strcpy_s(szExe, pLine);
        pLine = strtok_s(NULL, "\\", &pBuf);
    }

    //删除.exe
    char szAppName[MAX_PATH] = {0};
    strncpy_s(szAppName, szExe, strlen(szExe) - 4);
    strAppName = std::string(szAppName);
#endif

    return strAppName;
}

std::string ExceptionUtil::getAppRunPath()
{
    std::string strPath = "";
#if defined (__linux__)
    strPath = getDirectory();
#else

    char szExeFullPath[MAX_PATH] = {0}; // full path
    GetModuleFileNameA(NULL, szExeFullPath, MAX_PATH);
    strPath = std::string(szExeFullPath);    // get full path of the file

    size_t iPos = strPath.find_last_of('\\', strPath.length());
    if(iPos != std::string::npos)
    {
        strPath = strPath.substr(0, iPos); //return the directory without the file name
    }
#endif

    return strPath;
}


