#include "mongoclientdriverutil.h"
#include <iostream>
#include "bsoncxx/builder/stream/document.hpp"
#include "bsoncxx/json.hpp"
#include "mongocxx/instance.hpp"
#include "mongocxx/uri.hpp"



namespace MongoClientDriver
{

/***********************************************************
 * 功能：构造函数
 * **********************************************************/
MongoClientDriverUtil::MongoClientDriverUtil()
{
}

/***********************************************************
 * 功能：析构函数
 * **********************************************************/
MongoClientDriverUtil::~MongoClientDriverUtil()
{
}

/***********************************************************
 * 功能：连接数据库服务
 * 输入参数：
 *      strSrvUri：数据库服务的uri
 * 返回值：
 *      bool：操作结果，true -- 成功，false -- 失败
 * **********************************************************/
bool MongoClientDriverUtil::connectDBServer(const std::string &strSrvUri)
{
    m_spMongoInstance = std::shared_ptr<mongocxx::instance> (new (std::nothrow) mongocxx::instance());
    if(!(m_spMongoInstance.get()))
    {
        std::cout << "MongoClientDriverUtil::connectDBServer, new mongocxx::instance failed." << std::endl;
        return false;
    }

    m_spMongoClient = std::shared_ptr<mongocxx::client> (new (std::nothrow) mongocxx::client(mongocxx::uri(strSrvUri)));
    return m_spMongoClient.get() ? true : false;
}

/***********************************************************
 * 功能：采用JSON格式插入记录
 * 输入参数：
 *      strDatabaseName：数据库名称
 *      strCollectionName：集合名称
 *      strJsonRecord：JSON记录信息
 * 返回值：
 *      bool：操作结果，true -- 成功，false -- 失败
 * **********************************************************/
bool MongoClientDriverUtil::addRecordByJson(const std::string &strDatabaseName
                                            , const std::string &strCollectionName
                                            , const std::string &strJsonRecord)
{
    bool bRet = false;

    if(m_spMongoClient.get())
    {
        // 数据库
        mongocxx::database objDatabase = m_spMongoClient.get()->database(strDatabaseName);

        // 集合
        mongocxx::collection objCollection = objDatabase[strCollectionName];

        try
        {
            auto objBuilder = bsoncxx::from_json(strJsonRecord);
            objCollection.insert_one(objBuilder.view());

            bRet = true;
        }
        catch (const std::exception& e)
        {
            std::cout << "MongoClientDriverUtil::addRecordByJson, add error: " << e.what() << std::endl;
        }
    }

    return bRet;
}

/***********************************************************
 * 功能：采用map格式插入记录
 * 输入参数：
 *      strDatabaseName：数据库名称
 *      strCollectionName：集合名称
 *      mp4Records：map格式的记录信息，key和value暂未string格式
 * 返回值：
 *      bool：操作结果，true -- 成功，false -- 失败
 * **********************************************************/
bool MongoClientDriverUtil::addRecordByMap(const std::string &strDatabaseName
                                           , const std::string &strCollectionName
                                           , const std::map<std::string, std::string> &mp4Records)
{
    bool bRet = false;

    if(m_spMongoClient.get())
    {
        // 数据库
        mongocxx::database objDatabase = m_spMongoClient.get()->database(strDatabaseName);

        // 集合
        mongocxx::collection objCollection = objDatabase[strCollectionName];

        try
        {
            auto objBuilder = bsoncxx::builder::stream::document{};
            for(auto iter = mp4Records.begin(); iter != mp4Records.end(); ++iter)
            {
                objBuilder << iter->first << iter->second;
            }
            objCollection.insert_one(objBuilder.view());

            bRet = true;
        }
        catch (const std::exception& e)
        {
            std::cout << "MongoClientDriverUtil::addRecordByMap, add error: " << e.what() << std::endl;
        }
    }

    return bRet;
}

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
bool MongoClientDriverUtil::queryRecords(const std::string &strDatabaseName
                                         , const std::string &strCollectionName
                                         , const std::string &strKey
                                         , const std::string &strValue
                                         , const std::vector<std::string> &vtRetKeys
                                         , std::vector<std::string> &vtRecords)
{
    bool bRet = false;

    if(m_spMongoClient.get())
    {
        // 数据库
        mongocxx::database objDatabase = m_spMongoClient.get()->database(strDatabaseName);

        // 集合
        mongocxx::collection objCollection = objDatabase[strCollectionName];

        try
        {
            auto objBuilder = bsoncxx::builder::stream::document{};
            if(!(strKey.empty()) && !(strValue.empty()))
            {
                objBuilder << strKey << strValue << bsoncxx::builder::stream::finalize;
            }

            auto objCursor = objCollection.find(objBuilder.view());
            if(objCursor.begin() != objCursor.end())
            {
                for(auto &objDoc : objCursor)
                {
                    if(0 < vtRetKeys.size())
                    {
                        for(size_t i = 0, iSize = vtRetKeys.size(); i < iSize; ++i)
                        {
                            std::string strRetValue = objDoc[vtRetKeys[i]].get_utf8().value.to_string();
                            vtRecords.emplace_back(strRetValue);
                        }
                    }
                    else
                    {
                        vtRecords.emplace_back(bsoncxx::to_json(objDoc));
                    }
                }

                bRet = true;
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "MongoClientDriverUtil::queryRecords, query error: " << e.what() << std::endl;
        }
    }

    return bRet;
}

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
bool MongoClientDriverUtil::updateRecord(const std::string &strDatabaseName
                                         , const std::string &strCollectionName
                                         , const std::string &strKey
                                         , const std::string &strValue
                                         , const std::string &strUpdateKey
                                         , const std::string &strUpdateValue)
{
    bool bRet = false;

    if(m_spMongoClient.get())
    {
        // 数据库
        mongocxx::database objDatabase = m_spMongoClient.get()->database(strDatabaseName);

        // 集合
        mongocxx::collection objCollection = objDatabase[strCollectionName];

        try
        {
            auto objBuilderKey = bsoncxx::builder::stream::document{};
            if(!(strKey.empty()) && !(strValue.empty()))
            {
                objBuilderKey << strKey << strValue << bsoncxx::builder::stream::finalize;
            }

            auto objBuilderUpdate = bsoncxx::builder::stream::document{};
            if(!(strUpdateKey.empty()) && !(strUpdateValue.empty()))
            {
                objBuilderUpdate << "$set" << bsoncxx::builder::stream::open_document
                                 << strUpdateKey << strUpdateValue
                                 << bsoncxx::builder::stream::close_document
                                 << bsoncxx::builder::stream::finalize;
            }

            objCollection.update_one(objBuilderKey.view(), objBuilderUpdate.view());
            bRet = true;
        }
        catch (const std::exception& e)
        {
            std::cout << "MongoClientDriverUtil::updateRecord, query error: " << e.what() << std::endl;
        }
    }

    return bRet;
}

/***********************************************************
 * 功能：删除集合
 * 输入参数：
 *      strDatabaseName：数据库名称
 *      strCollectionName：集合名称
 * 返回值：
 *      bool：操作结果，true -- 成功，false -- 失败
 * **********************************************************/
bool MongoClientDriverUtil::dropCollection(const std::string &strDatabaseName, const std::string &strCollectionName)
{
    bool bRet = false;

    if(m_spMongoClient.get())
    {
        // 数据库
        mongocxx::database objDatabase = m_spMongoClient.get()->database(strDatabaseName);

        // 集合
        mongocxx::collection objCollection = objDatabase[strCollectionName];

        try
        {
            objCollection.drop();
            bRet = true;
        }
        catch (const std::exception& e)
        {
            std::cout << "MongoClientDriverUtil::dropCollection, query error: " << e.what() << std::endl;
        }
    }

    return bRet;
}

} // namespace MongoClientDriver

