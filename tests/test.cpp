#include "../sylar/log.h"
#include <iostream>

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

    sylar::LogEvent::ptr event(new sylar::LogEvent(__FILE__, __LINE__, 0, 1, 2, time(0)));
    event->getSS() << "Hello Sylar";
    logger->log(sylar::LogLevel::DEBUG, event);
    std::cout << "Finished" << std::endl;
    return 0;
}