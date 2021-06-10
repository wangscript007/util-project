/*
* Copyright (c) 2021.06
* All rights reserved.
*
* 文件节点：mongoclientdriverutil.h
*
* 初始版本：1.0
* 作者：张浪
* 创建日期：2021年6月10日
* 摘要：对Mongodb的客户端driver封装的工具类
*
*/

#ifndef MONGO_CLIENT_DRIVER_UTIL_H
#define MONGO_CLIENT_DRIVER_UTIL_H

#include <memory.h>
#include <string>
#include <vector>
#include <map>
#include "mongocxx/instance.hpp"
#include "mongocxx/client.hpp"


#ifdef _WIN32
#   define MONGO_CLIENT_DRIVER_LIB __declspec(dllexport)
#else
#   define MONGO_CLIENT_DRIVER_LIB __attribute__((visibility("default")))
#endif


namespace MongoClientDriver
{

class MONGO_CLIENT_DRIVER_LIB MongoClientDriverUtil
{
public:
    /***********************************************************
     * 功能：构造函数
     * **********************************************************/
    explicit MongoClientDriverUtil();

    /***********************************************************
     * 功能：析构函数
     * **********************************************************/
    ~MongoClientDriverUtil();

    /***********************************************************
     * 功能：连接数据库服务
     * 输入参数：
     *      strSrvUri：数据库服务的uri
     * 返回值：
     *      bool：操作结果，true -- 成功，false -- 失败
     * **********************************************************/
    bool connectDBServer(const std::string &strSrvUri);

    /***********************************************************
     * 功能：采用JSON格式插入记录
     * 输入参数：
     *      strDatabaseName：数据库名称
     *      strCollectionName：集合名称
     *      strJsonRecord：JSON记录信息
     * 返回值：
     *      bool：操作结果，true -- 成功，false -- 失败
     * **********************************************************/
    bool addRecordByJson(const std::string &strDatabaseName
                         , const std::string &strCollectionName
                         , const std::string &strJsonRecord);

    /***********************************************************
     * 功能：采用map格式插入记录
     * 输入参数：
     *      strDatabaseName：数据库名称
     *      strCollectionName：集合名称
     *      mp4Records：map格式的记录信息，key和value暂未string格式
     * 返回值：
     *      bool：操作结果，true -- 成功，false -- 失败
     * **********************************************************/
    bool addRecordByMap(const std::string &strDatabaseName
                        , const std::string &strCollectionName
                        , const std::map<std::string, std::string> &mp4Records);

    /***********************************************************
     * 功能：查询记录
     * 输入参数：
     *      strDatabaseName：数据库名称
     *      strCollectionName：集合名称
     *      strKey：查询条件的key
     *      strValue：查询条件的value
     *      vtRetKeys：查询结果的key的集合
     * 输出参数：
     *      vtRecords：查询结果
     * 返回值：
     *      bool：操作结果，true -- 成功，false -- 失败
     * **********************************************************/
    bool queryRecords(const std::string &strDatabaseName
                      , const std::string &strCollectionName
                      , const std::string &strKey
                      , const std::string &strValue
                      , const std::vector<std::string> &vtRetKeys
                      , std::vector<std::string> &vtRecords);

    /***********************************************************
     * 功能：查询记录
     * 输入参数：
     *      strDatabaseName：数据库名称
     *      strCollectionName：集合名称
     *      strKey：查询条件的key
     *      strValue：查询条件的value
     *      strUpdateKey：更新信息的key
     *      strUpdateValue：更新信息的value
     * 返回值：
     *      bool：操作结果，true -- 成功，false -- 失败
     * **********************************************************/
    bool updateRecord(const std::string &strDatabaseName
                      , const std::string &strCollectionName
                      , const std::string &strKey
                      , const std::string &strValue
                      , const std::string &strUpdateKey
                      , const std::string &strUpdateValue);

    /***********************************************************
     * 功能：删除集合
     * 输入参数：
     *      strDatabaseName：数据库名称
     *      strCollectionName：集合名称
     * 返回值：
     *      bool：操作结果，true -- 成功，false -- 失败
     * **********************************************************/
    bool dropCollection(const std::string &strDatabaseName, const std::string &strCollectionName);

private:
    std::shared_ptr<mongocxx::instance> m_spMongoInstance; // mongocxx::instance客户端智能指针
    std::shared_ptr<mongocxx::client> m_spMongoClient; // mongocxx::client客户端智能指针

};

} // namespace MongoClientDriver


#endif // MONGO_CLIENT_DRIVER_UTIL_H
