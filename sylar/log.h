#pragma once
#include <cstring>
#include <stdint.h>
#include <memory>
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <tuple>
#include <ctime>
#include <cstdio>
#include <cstring>
#include "utils.h"
#include <stdarg.h>
#include <map>
#include "singleton.h"


// 构建临时对象logeventwrap并借由析构函数实现触发log
#define SYLAR_LOG_LEVEL(logger, level) \
    if (logger->getLevel() <= level) \
        sylar::LogEventWrap(sylar::LogEvent::ptr(new sylar::LogEvent(logger, __FILE__, __LINE__, 0, sylar::GetThreadId(),\
                    sylar::GetFiberId(), time(0), level))).getSS()


#define SYLAR_LOG_DEBUG(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::DEBUG)
#define SYLAR_LOG_INFO(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::INFO)
#define SYLAR_LOG_WARN(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::WARN)
#define SYLAR_LOG_ERROR(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::ERROR)
#define SYLAR_LOG_FATAL(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::FATAL)

#define SYLAR_LOG_ROOT() sylar::LoggerMgr::GetInstance()->getRoot()
#define SYLAR_LOG_NAME(name) sylar::LoggerMgr::GetInstance()->getLogger(name)

namespace sylar{

class Logger;
// 日志级别
class LogLevel {
public:
    enum Level{
        UNKNOWN = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5,
    };
    static const char* ToString(LogLevel::Level level);
    static LogLevel::Level FromString(const std::string& str);
};

// 日志事件
class LogEvent {
public:
    using ptr = std::shared_ptr<LogEvent>;
    // typedef std::shared_ptr<LogEvent> ptr;
    LogEvent(std::shared_ptr<Logger> logger, const char* file, int32_t line, 
            uint32_t elapse, uint32_t threadid, uint32_t fiber_id, uint64_t time, LogLevel::Level level);
    const char* getFile() const {return m_file;};
    int32_t getLine() const {return m_line;};
    uint32_t getElapse() const {return m_elapse;};
    uint32_t getThreadId() const {return m_threadId;};
    uint32_t getFiberId() const {return m_fiberId;};
    uint64_t getTime() const {return m_time;};
    std::string getContent() const {return m_ss.str();};
    std::stringstream& getSS() { return m_ss; };
    std::shared_ptr<Logger> getLogger() const {return m_logger;};
    LogLevel::Level getLevel() const {return m_level;};
private:
    std::shared_ptr<Logger> m_logger;
    const char* m_file = nullptr;   // 文件名
    int32_t m_line = 0;             // 行号
    uint32_t m_elapse = 0;          // 程序起到现在的毫秒数
    int32_t m_threadId = 0;         // 线程号
    uint32_t m_fiberId = 0;         // 协程号
    uint64_t m_time = 0;                // 时间戳
    std::stringstream m_ss;         // 内容
    LogLevel::Level m_level;
};

class LogEventWrap{
public:
    LogEventWrap(LogEvent::ptr event);
    LogEvent::ptr getEvent() const { return m_event;}
    ~LogEventWrap();
    std::stringstream& getSS();
private:
    LogEvent::ptr m_event;
};

// 日志格式器
class LogFormatter {
public:
    using ptr = std::shared_ptr<LogFormatter>;
    // typedef std::shared_ptr<LogFormatter> ptr;
    std::string format(std::shared_ptr<sylar::Logger>, LogLevel::Level level, LogEvent::ptr event);
    LogFormatter(const std::string& pattern);
public:
    class FormatItem {
    public:
        using ptr = std::shared_ptr<FormatItem>;
        FormatItem(const std::string& fmt = ""){};
        virtual ~FormatItem(){};
        virtual void format(std::shared_ptr<sylar::Logger>, LogLevel::Level level, std::ostream& os, LogEvent::ptr event) = 0;
    };

    void init();
    bool isError()const {return m_error;};
    const std::string getPattern() const {return m_pattern;}
private:
    std::string m_pattern;
    std::vector<FormatItem::ptr> m_items;
    bool m_error = false;
};

// 日志输出地（目的地）
class LogAppender {
public:
    using ptr = std::shared_ptr<LogAppender>;
    // typedef std::shared_ptr<LogAppender> ptr;
    virtual void log(std::shared_ptr<sylar::Logger>, LogLevel::Level level, LogEvent::ptr event) = 0;
    void setFormatter(LogFormatter::ptr formatter) {m_formatter = formatter;};
    LogFormatter::ptr getFormatter() const {return m_formatter;};
    void setLevel(LogLevel::Level level) {m_level = level;};
    LogLevel::Level getLevel() const {return m_level;};
    virtual ~LogAppender(){};
    virtual std::string toYamlString() = 0;
protected:
    LogLevel::Level m_level;
    LogFormatter::ptr m_formatter;
};

// 日志输出器
class LoggerManager;
class Logger : public std::enable_shared_from_this<Logger>{
friend  class LoggerManager;
public:
    using ptr = std::shared_ptr<Logger>;
    // typedef std::shared_ptr<Logger> ptr;
    Logger(const std::string& name = "root");

    void log(LogLevel::Level level, LogEvent::ptr event);
    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);
    void error(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    void clearAppenders();

    LogLevel::Level getLevel() const {return m_level;};
    void setLevel(LogLevel::Level level) {m_level = level;};
    const std::string& getName() const {return m_name;};

    void setFormatter(LogFormatter::ptr val);
    void setFormatter(const std::string& val);
    LogFormatter::ptr getFormatter();
    std::string toYamlString();

private:
    std::string m_name;                         // 日志名称
    std::list<LogAppender::ptr> m_appenders;    // Appender集合
    LogFormatter::ptr m_formatter;
    Logger::ptr m_root;
protected:
    LogLevel::Level m_level;                    // 日志级别
};

// 输出到控制台的Appender
class StdoutLogAppender : public LogAppender {
public:
    using ptr = std::shared_ptr<StdoutLogAppender>;
    void log(std::shared_ptr<sylar::Logger> logger, LogLevel::Level level, LogEvent::ptr event) override;
    std::string toYamlString() override;
private:
};

// 输出文件的Appender
class FileLogAppender : public LogAppender {
public:
    using ptr = std::shared_ptr<FileLogAppender>;
    FileLogAppender(const std::string& filename);
    void log(std::shared_ptr<sylar::Logger> logger, LogLevel::Level level, LogEvent::ptr event) override;
    std::string toYamlString() override;
    bool reopen();
private:  
    std::string m_filename;
    std::ofstream m_filestream;
};


class LoggerManager {
public:
    Logger::ptr getLogger(const std::string& name);
    LoggerManager();

    void init();
    Logger::ptr getRoot() const {return m_root;};
    std::string toYamlString();
private:
    std::map<std::string, Logger::ptr> m_loggers;
    Logger::ptr m_root;
};

using LoggerMgr = sylar::Singleton<LoggerManager>;

}