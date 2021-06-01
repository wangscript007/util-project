/*
* Copyright (c) 2021.05
* All rights reserved.
*
* 文件节点：log4cxxhelper.h
*
* 初始版本：1.0
* 作者：张浪
* 创建日期：2021年5月31日
* 摘要：对log4cxx封装的帮助类
*
*/

#ifndef LOG4CXX_HELPER_H
#define LOG4CXX_HELPER_H

#include <stdio.h>
#include <string>
#include "log4cxx/logger.h"


#define LOG_TEMP_SIZE   (5 * 1024)

#ifdef _WIN32

#define LOG_TRACE(tag, fmt, ...) \
    do { \
    char szInfo[LOG_TEMP_SIZE] = {0}; \
    snprintf(szInfo, LOG_TEMP_SIZE, fmt, __VA_ARGS__); \
    LOG4CXX_TRACE(log4cxx::Logger::getLogger(tag), szInfo); } while(0)

#define LOG_DEBUG(tag, fmt, ...) \
    do { \
    char szInfo[LOG_TEMP_SIZE] = {0}; \
    snprintf(szInfo, LOG_TEMP_SIZE, fmt, __VA_ARGS__); \
    LOG4CXX_DEBUG(log4cxx::Logger::getLogger(tag), szInfo); } while(0)

#define LOG_INFO(tag, fmt, ...) \
    do { \
    char szInfo[LOG_TEMP_SIZE] = {0}; \
    snprintf(szInfo, LOG_TEMP_SIZE, fmt, __VA_ARGS__); \
    LOG4CXX_INFO(log4cxx::Logger::getLogger(tag), szInfo); } while(0)

#define LOG_WARN(tag, fmt, ...) \
    do { \
    char szInfo[LOG_TEMP_SIZE] = {0}; \
    snprintf(szInfo, LOG_TEMP_SIZE, fmt, __VA_ARGS__); \
    LOG4CXX_WARN(log4cxx::Logger::getLogger(tag), szInfo); } while(0)

#define LOG_ERROR(tag, fmt, ...) \
    do { \
    char szInfo[LOG_TEMP_SIZE] = {0}; \
    snprintf(szInfo, LOG_TEMP_SIZE, fmt, __VA_ARGS__); \
    LOG4CXX_ERROR(log4cxx::Logger::getLogger(tag), szInfo); } while(0)

#define LOG_FATAL(tag, fmt, ...) \
    do { \
    char szInfo[LOG_TEMP_SIZE] = {0}; \
    snprintf(szInfo, LOG_TEMP_SIZE, fmt, __VA_ARGS__); \
    LOG4CXX_FATAL(log4cxx::Logger::getLogger(tag), szInfo); } while(0)

#else

#define LOG_TRACE(tag, fmt, arg...) \
    do { \
    char szInfo[LOG_TEMP_SIZE] = {0}; \
    snprintf(szInfo, LOG_TEMP_SIZE, fmt, ##arg); \
    LOG4CXX_TRACE(log4cxx::Logger::getLogger(tag), szInfo); } while(0)

#define LOG_DEBUG(tag, fmt, arg...) \
    do { \
    char szInfo[LOG_TEMP_SIZE] = {0}; \
    snprintf(szInfo, LOG_TEMP_SIZE, fmt, ##arg); \
    LOG4CXX_DEBUG(log4cxx::Logger::getLogger(tag), szInfo); } while(0)

#define LOG_INFO(tag, fmt, arg...) \
    do { \
    char szInfo[LOG_TEMP_SIZE] = {0}; \
    snprintf(szInfo, LOG_TEMP_SIZE, fmt, ##arg); \
    LOG4CXX_INFO(log4cxx::Logger::getLogger(tag), szInfo); } while(0)

#define LOG_WARN(tag, fmt, arg...) \
    do { \
    char szInfo[LOG_TEMP_SIZE] = {0}; \
    snprintf(szInfo, LOG_TEMP_SIZE, fmt, ##arg); \
    LOG4CXX_WARN(log4cxx::Logger::getLogger(tag), szInfo); } while(0)

#define LOG_ERROR(tag, fmt, arg...) \
    do { \
    char szInfo[LOG_TEMP_SIZE] = {0}; \
    snprintf(szInfo, LOG_TEMP_SIZE, fmt, ##arg); \
    LOG4CXX_ERROR(log4cxx::Logger::getLogger(tag), szInfo); } while(0)

#define LOG_FATAL(tag, fmt, arg...) \
    do { \
    char szInfo[LOG_TEMP_SIZE] = {0}; \
    snprintf(szInfo, LOG_TEMP_SIZE, fmt, ##arg); \
    LOG4CXX_FATAL(log4cxx::Logger::getLogger(tag), szInfo); } while(0)

#endif

#ifdef _WIN32
#   define LOG4CXX_HELPER_LIB __declspec(dllexport)
#else
#   define LOG4CXX_HELPER_LIB __attribute__((visibility("default")))
#endif

class LOG4CXX_HELPER_LIB Log4cxxHelper
{
public:
    /************************************************
     * 功能：初始化，主要是对log4cxx进行配置文件的配置
     * 输入参数：
     *      strPropertyFilePath：日志配置文件路径，缺省值为log4cxx.properties
     *      iRefreshMillSecond：配置文件修改后动态生效时间，单位为ms，缺省值为60000
     * ***********************************************/
    static void init(std::string strPropertyFilePath = "log4cxx.properties", int iRefreshMillSecond = 60000);
};


#endif // LOG4CXX_HELPER_H

