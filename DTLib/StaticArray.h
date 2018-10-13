#ifndef STATICARRAY_H
#define STATICARRAY_H

#include "Array.h"

namespace DTLib
{

template <typename T, int N>
class StaticArray : public Array<T>
{
  protected:
    T m_space[N];

  public:
    StaticArray()
    {
        this->m_array = m_space;
    }
    StaticArray(const StaticArray<T, N> &obj)
    {
        // 空间指向自己的空间，内容赋值obj的内容
        this->m_array = m_space;
        for (int i = 0; i < N; i++)
        {
            m_space[i] = obj.m_space[i];
            // this->m_array[i] =  obj.m_space[i]
        }
    }
    StaticArray<T, N> &operator=(const StaticArray<T, N> &obj)
    {
        if (this != &obj)
        {
            for (int i = 0; i < N; i++)
            {
                m_space[i] = obj.m_space[i];
            }
        }
        return *this;
    }

    int length() const
    {
        return N;
    }
};

} // namespace DTLib

#endif // !STATICARRAY_H
