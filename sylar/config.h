#pragma once
#include <memory>
#include <sstream>
#include <boost\lexical_cast.hpp>

namespace sylar{
class  ConfigVarBase {
public:
    using ptr = std::shared_ptr<ConfigVarBase>;
    ConfigVarBase(const std::string& name, const std::string& description = "") : m_name(name), m_description(description){}
    virtual ~ConfigVarBase(){}
    const std::string& getName() const {return m_name;};
    const std::string& getDescription() const {return m_description;};
    virtual std::string toString() = 0;
    virtual bool fromString(const std::string& val) = 0;
protected:
    std::string m_name;
    std::string m_description;
};

}