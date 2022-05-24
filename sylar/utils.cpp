#include "utils.h"
#include "windows.h"
namespace sylar{
uint32_t GetThreadId(){
    return (uint32_t)GetCurrentThreadId();
}

uint32_t GetFiberId(){
    return 0;
}
}