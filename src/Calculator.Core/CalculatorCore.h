#ifndef CALCULATOR_CORE_H
#define CALCULATOR_CORE_H

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT __attribute__((visibility("default")))
#endif

extern "C" {
    // 简单的加法测试接口
    EXPORT double add(double a, double b);
    
    // 计算表达式接口（后续将实现算法）
    EXPORT double calculate(const char* expression, int* errorCode);
}

#endif // CALCULATOR_CORE_H
