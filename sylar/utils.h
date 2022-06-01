#pragma once
#include <stdint.h>
#include <typeinfo>
namespace sylar{

uint32_t GetThreadId();
uint32_t GetFiberId();
template<class T>
const char* TypeToName() {
    static const char* s_name = typeid(T).name();
    return s_name;
}
}
