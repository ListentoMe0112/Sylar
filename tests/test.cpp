#include "../sylar/log.h"
#include "../sylar/utils.h"
#include "../sylar/config.h"
#include "yaml-cpp/yaml.h"
#include <iostream>
#include <thread>

/*
    测试基础类型与模板类

*/

/*
    测试key重复错误
*/
    // sylar::ConfigVar<std::unordered_set<int>>::ptr g_unordered_map_string_int_value_config_a = 
    //     sylar::Config::Lookup("system.unordered_map", std::unordered_set<int>{}, "system map");


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
        sylar::ConfigVar<int>::ptr g_int_value_config = 
    sylar::Config::Lookup("system.port", (int)8080, "system port");
sylar::ConfigVar<float>::ptr g_float_value_config = 
    sylar::Config::Lookup("system.value", (float)10.19, "system value");

sylar::ConfigVar<std::vector<int>>::ptr g_vec_int_value_config = 
    sylar::Config::Lookup("system.int_vec", std::vector<int>{1,2,3}, "system int vec");

sylar::ConfigVar<std::list<int>>::ptr g_list_int_value_config = 
    sylar::Config::Lookup("system.int_list", std::list<int>{1,2,3}, "system int list");

sylar::ConfigVar<std::set<int>>::ptr g_set_int_value_config = 
    sylar::Config::Lookup("system.int_set", std::set<int>{1,2,3}, "system set");

sylar::ConfigVar<std::unordered_set<int>>::ptr g_unordered_set_int_value_config = 
    sylar::Config::Lookup("system.unordered_set", std::unordered_set<int>{1,2,3}, "system unordered_set");

sylar::ConfigVar<std::map<std::string, int>>::ptr g_map_string_int_value_config = 
    sylar::Config::Lookup("system.map", std::map<std::string, int>{{"1", 1},{"2", 2},{"3", 3}}, "system map");

sylar::ConfigVar<std::unordered_map<std::string, int>>::ptr g_unordered_map_string_int_value_config = 
    sylar::Config::Lookup("system.unordered_map", std::unordered_map<std::string, int>{{"1", 1},{"2", 2},{"3", 3}}, "system map");
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_int_value_config->getValue();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_float_value_config->toString();
    auto v = g_vec_int_value_config->getValue();
    auto l = g_list_int_value_config->getValue();
    auto s = g_set_int_value_config->getValue();
    auto us = g_unordered_set_int_value_config->getValue();
    auto m = g_map_string_int_value_config->getValue();
    auto um = g_unordered_map_string_int_value_config->getValue();
    
    for (auto& i: v){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "type: int_vec" << "\tval: " << i;
    }

    for (auto& i: l){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "type: int_list" << "\tval: " << i;
    }

    for (auto& i: s){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "type: int_set" << "\tval: " << i;
    }

    for (auto& i : us){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "type: int_unordered_set" << "\tval: " << i;
    }

    for (auto p : m){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "type: map_string_int" << "key: " << p.first << "\tval: " << p.second;
    }

    for (auto p : um){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "type: unordered_map_string_int" << "key: " << p.first << "\tval: " << p.second;
    }

    YAML::Node root = YAML::LoadFile("D:\\Programming\\sylar\\bin\\conf\\log.yml");
    sylar::Config::LoadFromYaml(root);
    
    std::cout << "---------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_int_value_config->getValue();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_float_value_config->toString();
    v = g_vec_int_value_config->getValue();
    for (auto& i: v){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "type: int_vec" << "\tval: " << i;
    }
    l = g_list_int_value_config->getValue();
    for (auto& i: l){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "type: int_list" << "\tval: " << i;
    }
    s = g_set_int_value_config->getValue();
    for (auto& i: s){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "type: set_list" << "\tval: " << i;
    }
    us = g_unordered_set_int_value_config->getValue();
    for (auto& i : us){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "type: int_unordered_set" << "\tval: " << i;
    }

    m = g_map_string_int_value_config->getValue();
    for (auto p : m){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "type: map_string_int" << "key: " << p.first << "\tval: " << p.second;
    }

    um = g_unordered_map_string_int_value_config->getValue();
    for (auto p : um){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "type: unordered_map_string_int" << "key: " << p.first << "\tval: " << p.second;
    }
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

class Person{
public:
    Person(){}
    std::string toString() const {
        std::stringstream ss;
        ss << "[Person name=" << m_name
           << " age=" << m_age
           << " sex=" << m_sex
           << "]";
        return ss.str();
    }

    bool operator==(const Person& other) const{
        return m_name == other.m_name &&
            m_age == other.m_age &&
            m_sex == other.m_sex;
    }
    std::string m_name;
    int m_age = 0;
    bool m_sex = 0;

};

namespace sylar {

template<>
class LexicalCast<std::string, Person> {
public:
    Person operator()(const std::string& v) {
        YAML::Node node = YAML::Load(v);
        Person p;
        p.m_name = node["name"].as<std::string>();
        p.m_age = node["age"].as<int>();
        p.m_sex = node["sex"].as<bool>();
        return p;
    }
};

template<>
class LexicalCast<Person, std::string> {
public:
    std::string operator()(const Person& p) {
        YAML::Node node;
        node["name"] = p.m_name;
        node["age"] = p.m_age;
        node["sex"] = p.m_sex;
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

}


void test_log(){
    static sylar::Logger::ptr system_log = SYLAR_LOG_NAME("system");
    SYLAR_LOG_INFO(system_log) << "hello system" ;
    std::cout << sylar::LoggerMgr::GetInstance()->toYamlString() << std::endl;
    YAML::Node root = YAML::LoadFile("D:\\Programming\\sylar\\bin\\conf\\log.yml");
    // std::cout << "===================" << std::endl;
    sylar::Config::LoadFromYaml(root);
    // std::cout << "===================" << std::endl;
    std::cout << sylar::LoggerMgr::GetInstance()->toYamlString() << std::endl;  
    SYLAR_LOG_INFO(system_log) << "hello system" ;
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "hello system" ;
}

int main(){
    // std::cout << "Main Start Here" << std::endl;
    test_log();
    return 0;
}