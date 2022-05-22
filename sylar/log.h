#pragma once
#include <string>
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
};

// 日志事件
class LogEvent {
public:
    using ptr = std::shared_ptr<LogEvent>;
    // typedef std::shared_ptr<LogEvent> ptr;
    LogEvent(const char* file, int32_t line, uint32_t elapse, uint32_t threadid, uint32_t fiber_id, uint64_t time);
    const char* getFile() const {return m_file;};
    int32_t getLine() const {return m_line;};
    uint32_t getElapse() const {return m_elapse;};
    uint32_t getThreadId() const {return m_threadId;};
    uint32_t getFiberId() const {return m_fiberId;};
    uint64_t getTime() const {return m_time;};
    std::string getContent() const {return m_ss.str();};
    std::stringstream& getSS() { return m_ss; };
private:
    const char* m_file = nullptr;   // 文件名
    int32_t m_line = 0;             // 行号
    uint32_t m_elapse;          // 程序起到现在的毫秒数
    int32_t m_threadId;         // 线程号
    uint32_t m_fiberId = 0;         // 协程号
    uint64_t m_time = 0;                // 时间戳
    std::stringstream m_ss;         // 内容
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
private:
    std::string m_pattern;
    std::vector<FormatItem::ptr> m_items;
};

// 日志输出地（目的地）
class LogAppender {
public:
    using ptr = std::shared_ptr<LogAppender>;
    // typedef std::shared_ptr<LogAppender> ptr;
    LogAppender(){};
    virtual ~LogAppender(){};
    virtual void log(std::shared_ptr<sylar::Logger>, LogLevel::Level level, LogEvent::ptr event) = 0;
    void setFormatter(LogFormatter::ptr formatter) {m_formatter = formatter;};
    LogFormatter::ptr getFormatter() const {return m_formatter;};
protected:
    LogLevel::Level m_level;
    LogFormatter::ptr m_formatter;
};

// 日志输出器
class Logger : public std::enable_shared_from_this<Logger>{
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

    LogLevel::Level getLevel() const {return m_level;};
    void setLevel(LogLevel::Level level) {m_level = level;};
    const std::string& getName() const {return m_name;};
private:
    std::string m_name;                         // 日志名称
    std::list<LogAppender::ptr> m_appenders;    // Appender集合
    LogFormatter::ptr m_formatter;
protected:
    LogLevel::Level m_level;                    // 日志级别
};

// 输出到控制台的Appender
class StdoutLogAppender : public LogAppender {
public:
    using ptr = std::shared_ptr<StdoutLogAppender>;
    void log(std::shared_ptr<sylar::Logger> logger, LogLevel::Level level, LogEvent::ptr event) override;
    ~StdoutLogAppender(){};
private:
};

// 输出文件的Appender
class FileLogAppender : public LogAppender {
public:
    using ptr = std::shared_ptr<FileLogAppender>;
    FileLogAppender(const std::string& filename);
    ~FileLogAppender(){};
    void log(std::shared_ptr<sylar::Logger> logger, LogLevel::Level level, LogEvent::ptr event) override;
    bool reopen();
private:  
    std::string m_filename;
    std::ofstream m_filestream;
};

}