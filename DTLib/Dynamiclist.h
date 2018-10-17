#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "Exception.h"
#include "SeqList.h"

namespace DTLib
{
template <typename T>
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity;    // 顺序存储空间的大小

public:
    DynamicList (int capacity)    // 申请空间，构造函数参数作为大小
    {
        this->m_array = new T[capacity];

        if (this->m_array != NULL)
        {    // 堆空间申请成功
            this->m_length   = 0;
            this->m_capacity = capacity;
        }
        else
        {    // 抛异常
            THROW_EXCEPTION (NoEnoughMemoryException, "No memory to creat DynamicList object...");
        }
    }

    int capacity () const
    {
        return this->m_capacity;
    }

    // 动态特性体现
    // 重新设置顺序存储空间的大小
    void resizes (int capacity)
    {
        if (capacity != m_capacity)
        {    // 保证异常安全性
            T *array = new T[capacity];
            if (array != NULL)
            {
                // 重新定义长度
                int length = (this->m_length < capacity ? this->m_length : capacity);
                for (int i = 0; i < length; i++)
                {
                    array[i] = this->m_array[i];
                }

                // 移动m_array指向新的堆空间，销毁m_array指向的原来的堆空间
                // 注意异常安全性
                T *temp          = this->m_array;
                this->m_array    = array;
                this->m_length   = length;
                this->m_capacity = capacity;
                delete[] temp;
            }
            else
            {
                THROW_EXCEPTION (NoEnoughMemoryException, "No memory to resize DynamicList object...");
            }
        }
    }
    ~DynamicList ()
    {
        delete[] this->m_array;
    }
};

}    // namespace DTLib

#endif    // !DYNAMICLIST_H
