# Sylar
## 项目路径
# 日志系统
1)
    Logger （定义日志类别）
       |
       |--------Formatter（日志格式）
       |
    Appender（日志输出地）

## 配置系统

Config --> Yaml
```cpp
yamp-cpp: github 

YAML::Node node = YAML::LoadFile
node.IsMap() 
for (auto it = node.begin(); it != node.end(); it ++){
    it->first, it->second
}

node.IsSequence()
for (size_t i = 0; i < node.size(); i++){

}

node.IsScalar()
```
```cpp
// 配置系统原则：约定优先于配置
template<T, FromStr, ToStr>
class ConfigVar;


template<F, T>
LexicalCast;

// 容器偏特化, 目前支持vector, set, unordered_set, 
// map, unordered_map 支持key = std::string
// 自定义类型可与模板类结合
```

配置事件机制，当配置发生更改时，程序可以感知

## 日志系统整合配置系统
```yaml
logs:
    - name: 唯一标识 root
      level: （debug, info, warn, error, fatal）
      formatter: '%d%T%p%T'
      appender: 
        - type: StdoutLogAppender, FileLogAppender
          level: （debug, info, warn, error, fatal）只接受level等级及以上log
          file: /logs/xxx.log
```
```cpp
    sylar::Logger g_logger = sylar::LoggerMgr::GetInstance()->getLogger(name);
    SYLAR_LOG_INFO(g_logger) << "xxx log";
```

```cpp
static Logger::ptr g_log = SYLAR_LOG_NAME("system");
// m_root, m_system -> m_root 当logger的appenders为空，使用root写logger
```

```cpp
// 定义LogDefine LogAppenderDefine, 偏特化 LexicalCast
// 实现了日志配置解析
```

```cpp

```