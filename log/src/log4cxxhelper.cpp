#include "log4cxxhelper.h"
#include "log4cxx/propertyconfigurator.h"


/************************************************
 * 功能：初始化，主要是对log4cxx进行配置文件的配置
 * 输入参数：
 *      strPropertyFilePath：日志配置文件路径，缺省值为log4cxx.properties
 *      iRefreshMillSecond：配置文件修改后动态生效时间，单位为ms，缺省值为60000
 * ***********************************************/
void Log4cxxHelper::init(std::string strPropertyFilePath, int iRefreshMillSecond)
{
    //log4cxx::PropertyConfigurator::configure(strPropertyFilePath); // 加载配置文件
    log4cxx::PropertyConfigurator::configureAndWatch(strPropertyFilePath, iRefreshMillSecond); // 加载配置文件，并设置为修改后动态更新

    return;
}
