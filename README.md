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
