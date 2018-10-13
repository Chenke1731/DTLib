#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "Object.h"

namespace DTLib
{

#define THROW_EXCEPTION(e, m) (throw e(m, __FILE__, __LINE__))

class Exception : public Object
{
  protected:
    /* data */
    char *m_message;
    char *m_location;

    void init(const char *message, const char *file, int line);

  public:
    Exception(const char *message);
    Exception(const char *file, int line);
    Exception(const char *message, const char *file, int line);

    Exception(const Exception &e);
    Exception &operator=(const Exception &e);

    virtual const char *message() const;
    virtual const char *location() const;

    virtual ~Exception() = 0;
};

// 计算异常
class ArithmeticException : public Exception
{
  public:
    ArithmeticException() : Exception(0) {}
    ArithmeticException(const char *message) : Exception(message) {}
    ArithmeticException(const char *file, int line) : Exception(file, line) {}
    ArithmeticException(const char *message, const char *file, int line) : Exception(message, file, line) {}

    // 形参是Exception父类类型，传入的实参是子类类型
    ArithmeticException(const ArithmeticException &e) : Exception(e) {}
    ArithmeticException &operator=(const ArithmeticException &e)
    {
        Exception::operator=(e);
        return *this;
    }
};

// 空指针异常
class NullPointerException : public Exception
{
  public:
    NullPointerException() : Exception(0) {}
    NullPointerException(const char *message) : Exception(message) {}
    NullPointerException(const char *file, int line) : Exception(file, line) {}
    NullPointerException(const char *message, const char *file, int line) : Exception(message, file, line) {}

    NullPointerException(const NullPointerException &e) : Exception(e) {}
    NullPointerException &operator=(const NullPointerException &e)
    {
        Exception::operator=(e);
        return *this;
    }
};

// 越界异常
class IndexOutOfBoundsException : public Exception
{
  public:
    IndexOutOfBoundsException() : Exception(0) {}
    IndexOutOfBoundsException(const char *message) : Exception(message) {}
    IndexOutOfBoundsException(const char *file, int line) : Exception(file, line) {}
    IndexOutOfBoundsException(const char *message, const char *file, int line) : Exception(message, file, line) {}

    IndexOutOfBoundsException(const IndexOutOfBoundsException &e) : Exception(e) {}
    IndexOutOfBoundsException &operator=(const IndexOutOfBoundsException &e)
    {
        Exception::operator=(e);
        return *this;
    }
};

// 内存不足异常
class NoEnoughMemoryException : public Exception
{
  public:
    NoEnoughMemoryException() : Exception(0) {}
    NoEnoughMemoryException(const char *message) : Exception(message) {}
    NoEnoughMemoryException(const char *file, int line) : Exception(file, line) {}
    NoEnoughMemoryException(const char *message, const char *file, int line) : Exception(message, file, line) {}

    NoEnoughMemoryException(const NoEnoughMemoryException &e) : Exception(e) {}
    NoEnoughMemoryException &operator=(const NoEnoughMemoryException &e)
    {
        Exception::operator=(e);
        return *this;
    }
};

// 参数错误异常
class InvalidParameteException : public Exception
{
  public:
    InvalidParameteException() : Exception(0) {}
    InvalidParameteException(const char *message) : Exception(message) {}
    InvalidParameteException(const char *file, int line) : Exception(file, line) {}
    InvalidParameteException(const char *message, const char *file, int line) : Exception(message, file, line) {}

    InvalidParameteException(const InvalidParameteException &e) : Exception(e) {}
    InvalidParameteException &operator=(const InvalidParameteException &e)
    {
        Exception::operator=(e);
        return *this;
    }
};

// 非法操作异常
class InvalidOperationException : public Exception
{
  public:
    InvalidOperationException() : Exception(0) {}
    InvalidOperationException(const char *message) : Exception(message) {}
    InvalidOperationException(const char *file, int line) : Exception(file, line) {}
    InvalidOperationException(const char *message, const char *file, int line) : Exception(message, file, line) {}

    InvalidOperationException(const InvalidOperationException &e) : Exception(e) {}
    InvalidOperationException &operator=(const InvalidOperationException &e)
    {
        Exception::operator=(e);
        return *this;
    }
};

} // namespace DTLib

#endif // !EXCEPTION_H
