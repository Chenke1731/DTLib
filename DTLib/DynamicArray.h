#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"
#include "Exception.h"

namespace DTLib
{
template <typename T>
class DynamicArray : public Array<T>
{
  public:
    int m_length;

    void init(T* array, int length)
    {
        if(array != NULL)
        {
            this->m_array = array;
            this->m_length = length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat DynamicArray object...");
        }
    }

    T* copy(T* array, int len, int newlen)
    {
        T *ret = new T[newlen];
        if(ret != NULL)
        {
            int size = (len < newlen) ? len : newlen;
            for(int i = 0; i < size; i++)
            {
                ret[i] = array[i];
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to copy DynamicArray object...");
        }
        return ret;
    }

    void update(T* array, int length)
    {
        if(array != NULL)
        {
            T *temp = this->m_array;
            this->m_array = array;
            this->m_length = length;
            delete[] temp;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to update DynamicArray object...");
        }
    }

  public:
    DynamicArray(int length)
    {
/*         // 在堆空间中申请内存
        this->m_array = new T[length];
        if (this->m_array != NULL)
        {
            this->m_length = length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat DynamicArray object...");
        } */
        init(new T[length], length);
    }

    DynamicArray(const DynamicArray<T> &obj)
    {
/*         // 数组长度以参数对象的长度为准
        this->m_array = new T[obj.m_length];
        if (this->m_array != NULL)
        {
            cout << "DynamicArray(const DynamicArray<T>& obj)" << endl;
            // 长度设置
            this->m_length = obj.m_length;
            // 进行值的拷贝
            for (int i = 0; i < obj.m_length; i++)
            {
                this->m_array[i] = obj.m_array[i];
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat DynamicArray object...");
        } */

        init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
    }

    DynamicArray<T> &operator=(const DynamicArray<T> &obj)
    {/* 
        if (this != &obj)
        {
            T *array = new T[obj.m_length];
            if (array != NULL)
            {
                for (int i = 0; i < obj.m_length; i++)
                {
                    array[i] = obj.m_array[i];
                }

                // 拷贝完就设置
                T *temp = this->m_array;
                this->m_array = array;
                this->m_length = obj.m_length;

                delete[] temp;
                // 保证异常安全
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to copy DynamicArray object...");
            }
        } */

        update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);

        return *this;
    }

    int length() const
    {
        return m_length;
    }

    void resize(int length) // 动态重置数组的长度
    {
/*         if (length != m_length)
        {
            T *array = new T[length];
            if (array != NULL)
            {
                int size = (length < m_length) ? length : m_length;

                for (int i = 0; i < size; i++)
                {
                    array[i] = this->m_array[i];
                }

                T *temp = this->m_array;
                this->m_array = array;
                this->m_length = length;

                delete[] temp;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to resize DynamicArray object...");
            }
        } */

        update(copy(this->m_array, this->m_length, length), length);
    }

    ~DynamicArray()
    {
        delete[] this->m_array;
    }
};
} // namespace DTLib

#endif // !DYNAMICARRAY_H
