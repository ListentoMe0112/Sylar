#include "../sylar/log.h"
#include "../sylar/utils.h"
#include "../sylar/config.h"
#include "yaml-cpp/yaml.h"
#include <iostream>
#include <thread>



void testLog(){
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
}

void testConfig(){
    sylar::ConfigVar<int>::ptr g_int_value_config = sylar::Config::Lookup("system.port", (int)8080, "system port");
    sylar::ConfigVar<float>::ptr g_float_value_config = sylar::Config::Lookup("system.value", (float)10.19, "system port");
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_int_value_config->getValue();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_float_value_config->toString();
    YAML::Node root = YAML::LoadFile("D:\\Programming\\sylar\\bin\\conf\\log.yml");
    sylar::Config::LoadFromYaml(root);
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_int_value_config->getValue();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_float_value_config->toString();
}

void print_yaml(const YAML::Node& node, int level){
    if (node.IsScalar()){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ') << node.Scalar() << " - " << node.Type() << " - " << level;
    }else if (node.IsNull()){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ') <<"NULL" << " - " << node.Type() << " - " << level;
    }else if (node.IsMap()){
        for (auto it = node.begin(); it != node.end(); it++){
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ') << it->first << " - " << it->second.Type() << " - " << level;
            print_yaml(it->second, level + 1);
        }
    }else if (node.IsSequence()){
        for (size_t i = 0; i < node.size(); i++){
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ') << i << " - " << node[i].Type() << " - " << level;
            print_yaml(node[i], level + 1);
        }
    }
}

void testyaml(){
    YAML::Node root = YAML::LoadFile("D:\\Programming\\sylar\\bin\\conf\\log.yml");
    
    print_yaml(root, 0);
}

int main(){
    testConfig();
    // testyaml();
    return 0;
}