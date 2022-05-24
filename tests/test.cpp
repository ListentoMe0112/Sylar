#include "../sylar/log.h"
#include "../sylar/utils.h"
#include <iostream>
#include <thread>


int main(){
    
    sylar::Logger::ptr logger(new sylar::Logger());
    logger->addAppender(sylar::LogAppender::ptr(new sylar::StdoutLogAppender()));
/*
    %m -- 消息体
    %p -- level
    %r -- 启动后时间
    %c -- 日志名称
    %t -- 输出该日志线程的线程名
    %n -- 输出一个回车
    %d -- 时间
    %f -- 文件名
    %l --  行号
    "%d [%p] %f %l %m %n"
    const char* file, int32_t line, uint32_t elapse, uint32_t threadid, uint32_t fiber_id, uint64_t time
*/
    // SYLAR_LOG_DEBUG(logger, "Test Macro");
    sylar::FileLogAppender::ptr file_appender(new sylar::FileLogAppender("./log.txt"));
    logger->addAppender(file_appender);
    SYLAR_LOG_ERROR(logger) << "Hello world1";

    sylar::LogFormatter::ptr fmt(new sylar::LogFormatter("%d%T%m\n"));
    file_appender->setFormatter(fmt);

    file_appender->setLevel(sylar::LogLevel::ERROR);
    SYLAR_LOG_DEBUG(logger) << "Hello world2";
    std::cout << "Finished" << std::endl;

    auto l = sylar::LoggerMgr::GetInstance()->getLogger("xx");
    SYLAR_LOG_INFO(l) << "xxxxx";
    return 0;
}