#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include <cstdlib>
#include <iostream>
#include "Pointer.h"

namespace DTLib
{

template <typename T>
class SmartPointer : public Pointer<T>
{

  public:
    SmartPointer(T *p = NULL) : Pointer<T>(p)
    {
    }

    // 拷贝构造函数
    SmartPointer(const SmartPointer<T> &obj)
    {
        this->m_pointer = obj.m_pointer;
        const_cast<SmartPointer<T> &>(obj).m_pointer = NULL;
    }

    // 赋值操作符重载
    SmartPointer<T> &operator=(const SmartPointer<T> &obj)
    {
        // 非自赋值
        if (this != &obj)
        {
            /* delete m_pointer;   // 
            m_pointer = obj.m_pointer;
            const_cast<SmartPointer<T> &>(obj).m_pointer = NULL; */

            // 考虑异常安全性
            T *temp = this->m_pointer;
            this->m_pointer = obj.m_pointer;
            const_cast<SmartPointer<T> &>(obj).m_pointer = NULL;
            delete temp;
        }

        return *this;
    }


    ~SmartPointer()
    {
        delete this->m_pointer;
    }
};

} // namespace DTLib

#endif // !SMARTPOINTER_H
