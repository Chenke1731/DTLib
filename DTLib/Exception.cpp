#define _CRT_SECURE_NO_WARNINGS

#include "Exception.h"
#include <cstring>
#include <cstdlib>

using namespace std;

namespace DTLib
{

void Exception::init(const char *message, const char *file, int line)
{
    // m_message = message 不能直接这样赋值
    // 原因是：message指向的字符串可能位于栈上、堆空间中，还可能是全局数据区
    // 没办法控制message指向的外部字符串的生命周期
    // 所以这样是不安全的
    // 解决办法就是拷贝一份字符串出来
    // strdup将字符串复制到了堆空间中
    m_message = (message ? _strdup(message) : NULL) ;
    if (file != NULL)
    {
        char sl[16] = {0};  // 辅助字符数组
        _itoa(line, sl, 10); // 将行号转换为字符串并存储在s1中

        // 拼接字符串
        m_location = static_cast<char *>(malloc(strlen(file) + strlen(sl) + 2));
        m_location = strcpy(m_location, file);
        m_location = strcat(m_location, ":");
        m_location = strcat(m_location, sl);
    }
    else
    {
        m_location = NULL;
    }
}

Exception::Exception(const char *message)
{
    init(message, NULL, 0);
}
Exception::Exception(const char *file, int line)
{
    init(NULL, file, line);
}
Exception::Exception(const char *message, const char *file, int line)
{
    init(message, file, line);
}

// 该异常类对象在进行初始化和赋值的时候进行的是深拷贝，所以要重载这两个函数

Exception::Exception(const Exception &e)
{
    m_message = _strdup(e.m_message);
    m_location = _strdup(e.m_location);
}

Exception &Exception::operator=(const Exception &e)
{
    if (this != &e)
    {
        free(m_message);
        free(m_location);
        m_message = _strdup(e.m_message);
        m_location = _strdup(e.m_location);
        // 是否需要考虑异常安全
    }
    return *this;
}

const char *Exception::message() const
{
    return m_message;
}
const char *Exception::location() const
{
    return m_location;
}

// 纯虚函数本来是不需要提供实现的，是在子类中去实现
// 但是析构函数例外，C++规定，析构函数不管是否是纯虚函数都需要提供实现
// 原因是：在析构一个对象的是否，最后肯定会调用到父类的析构函数，如果父类的纯虚析构函数没有实现，这一些列的析构调用没法完成
Exception::~Exception()
{
    free(m_message);
    free(m_location);
}

} // namespace DTLib