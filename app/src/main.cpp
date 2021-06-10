#include <iostream>
#include <thread>
#include <chrono>

#include "exceptionutil.h"

#include "log4cxxhelper.h"
#include "evpp/tcp_server.h"
#include "evpp/tcp_client.h"
#include "evpp/buffer.h"
#include "evpp/tcp_conn.h"
#include "evpp/http/http_server.h"
#include "evpp/httpc/conn.h"
#include "evpp/logging.h"


#ifdef _WIN32
//#include <winsock2.h>
//#include <Windows.h>
//#pragma comment(lib, "ws2_32.lib")
#include "evpp/winmain-inl.h"
#include "evpp/windows_port.h"
static OnApp *gs_pObjAPP = nullptr;
#endif

#include "mongoclientdriverutil.h"


void logTest()
{
    Log4cxxHelper::init("log4cxx.properties", 3000);

    LOG4_DEBUG("stdout", "int: %d, double: %f, string: %s", 123, 56.3, "this is test log!!!");
    LOG4_INFO("All", "int: %d, double: %f, string: %s", 189, 16.308, "this is test log!!!");

    /*for (size_t i = 0; i < 500000; ++i)
    {
        LOG4_DEBUG("stdout", "int: %d, double: %f, string: %s", 1 + i, 56.3, "this is test log!!!");
        LOG4_INFO("All", "int: %d, double: %f, string: %s", 1 + i, 16.308, "this is test log!!!");
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }*/

    return;
}

void initNetEnv()
{
#ifdef _WIN32
    // 可以使用evpp的winmain-inl.h中OnApp替代
    if (!gs_pObjAPP)
    {
        gs_pObjAPP = new (std::nothrow) OnApp();
    }

    /*WSADATA wsa;
    if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
    {
        LOG4_DEBUG("stdout", "WSAStartup failed!!!");
    }*/
#endif

    return;
}

void deinitNetEnv()
{
#ifdef _WIN32
    if (gs_pObjAPP)
    {
        delete gs_pObjAPP;
        gs_pObjAPP = nullptr;
    }
#endif

    return;
}

void tcpClientTest()
{
    std::string addr = "172.18.11.126:60001";

    evpp::EventLoop loop;
    evpp::TCPClient client(&loop, addr, "TCPClient");    //构造函数，创造客户端对象
    //消息回调函数
    client.SetMessageCallback([&loop, &client](const evpp::TCPConnPtr& conn, evpp::Buffer* msg) {
        /*evpp::Slice sli = msg->ToSlice();
        unsigned char ch[200];
        for (auto i = 0; i < sli.size(); ++i)
        {
            ch[i] = sli[i];

        }*/
        LOG4_INFO("stdout", "recv: %s, data: %s.", conn->remote_addr().data(), msg->ToString().data());
        msg->Reset();                //清空缓冲区
        conn->Send("I have receive you message.");
    });    //参数由匿名函数对象组成

    //连接回调函数
    client.SetConnectionCallback([](const evpp::TCPConnPtr& conn) {
        if (conn->IsConnected())
        {
            LOG4_INFO("stdout", "connect to: %s.", conn->remote_addr().data());
            conn->Send("hello");
        }
        else
        {
            conn->loop()->Stop();
        }
    });

    client.Connect();
    loop.Run();
    LOG4_INFO("stdout", "1 + 1 = 2.");

    return;
}

void tcpServerTest()
{
    std::string strAddr = "0.0.0.0:60100";
    int iThreadNum = 4;
    evpp::EventLoop loop;
    evpp::TCPServer server(&loop, strAddr, "TCPEchoServer", iThreadNum);
    
    server.SetMessageCallback([](const evpp::TCPConnPtr& conn, evpp::Buffer* msg) {
        LOG4_INFO("stdout", "recv: %s, data: %s.", conn->remote_addr().data(), msg->ToString().data());
        msg->Reset();

        evpp::Buffer tmpMsg;
        std::string strMsg = "I have receive your message.";
        tmpMsg.Append(strMsg.data(), strMsg.length());
        
        conn->Send(&tmpMsg);
    });

    server.SetConnectionCallback([](const evpp::TCPConnPtr& conn) {
        if (conn->IsConnected())
        {
            LOG4_INFO("stdout", "new connection from: %s.", conn->remote_addr().data());
        }
        else
        {
            LOG4_INFO("stdout", "lost the connection from: %s.", conn->remote_addr().data());
        }
    });

    server.Init();
    server.Start();
    loop.Run();

    LOG4_INFO("stdout", "1 + 2 = 3.");

    return;
}

static void defaultHandler(evpp::EventLoop* loop, const evpp::http::ContextPtr& ctx, const evpp::http::HTTPSendResponseCallback& cb) 
{
    LOG4_INFO("stdout", "recv: %s, uri: %s, data: %s.", ctx->remote_ip().data(), ctx->uri().data(), ctx->body().ToString().data());

    cb("welcome!!!");
    return;
}

void httpServerTest()
{
    std::vector<int> ports = { 9009, 23456, 23457 };
    int iThreadNum = 5;
    evpp::http::Server server(iThreadNum);
    server.SetThreadDispatchPolicy(evpp::ThreadDispatchPolicy::kIPAddressHashing);
    server.RegisterDefaultHandler(&defaultHandler); // 这个是必须的，不然要崩溃
    server.RegisterHandler("/echo",
                           [](evpp::EventLoop *loop,
                           const evpp::http::ContextPtr& ctx,
                           const evpp::http::HTTPSendResponseCallback& cb) {
        LOG4_INFO("stdout", "recv: %s, uri: %s, data: %s.", ctx->remote_ip().data(), ctx->uri().data(), ctx->body().ToString().data());
        //cb(ctx->body().ToString());

        cb("welcome, this is test message!!!");
    });
    //server.RegisterHandler("/echo", &defaultHandler);

    //server.Init(ports);
    server.Init(9009);
    server.Start();
    LOG4_INFO("stdout", "1 + 3 = 4.");

    while (!server.IsStopped())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    return;
}

void mongoClientDriverTest()
{
    MongoClientDriver::MongoClientDriverUtil objUtil;
    bool bRet = objUtil.connectDBServer("mongodb://192.168.49.129:27017/?maxPoolSize=10");
    std::cout << "connect ret: " << bRet << std::endl;
    objUtil.addRecordByJson("mongotest", "testdb", "{\"key\":\"this is info again\", \"value\":123, \"extra\":\"test is ok\"}");

    std::map<std::string, std::string> mp4Records;
    mp4Records["name"] = "zhangsan";
    mp4Records["age"] = "24";
    mp4Records["sex"] = "male";
    objUtil.addRecordByMap("mongotest", "testdb", mp4Records);

    std::vector<std::string> vtRetKeys;
    vtRetKeys.clear();
    std::vector<std::string> vtRecords;
    vtRecords.clear();

    objUtil.queryRecords("mongotest", "testdb", "", "", vtRetKeys, vtRecords);
    for(size_t i = 0, iSize = vtRecords.size(); i < iSize; ++i)
    {
        std::cout << vtRecords[i] << std::endl;
    }

    //objUtil.dropCollection("mongotest", "testdb");

    return;
}

int main(int argc, char** argv)
{
    std::cout << "Hello utility!!!" << std::endl;
    ExceptionUtil::setExceptionHandler(ExceptionUtil::getAppName());

    logTest();
    mongoClientDriverTest();

    google::InitGoogleLogging(argv[0]);
    google::SetStderrLogging(google::GLOG_WARNING);
    //initNetEnv();
    //httpServerTest();
    //tcpClientTest();
    //tcpServerTest();

    getchar();
    deinitNetEnv();

    return 0;
}
