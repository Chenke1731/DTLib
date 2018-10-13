#ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"
#include "Exception.h"

// 顺序表抽象类
namespace DTLib
{

template <typename T>
class SeqList : public List<T>
{
  protected:
    T *m_array;   // 顺序表的存储空间指针，具体值在子类中实现
    int m_length; // 当前顺序表的长度

  public:
    bool insert(int i, const T &e)
    {
        bool ret = ((i >= 0) && (i <= m_length));
        ret = ret && ((m_length + 1) <= capacity());
        if (ret)
        {
            for (int p = m_length - 1; p >= i; p--)
            { // 进行数据元素的挪动
                m_array[p + 1] = m_array[p];
            }
            // 插入元素
            m_array[i] = e;
			m_length++;
        }

        return ret;
    }

    bool insert(const T& e)
    {
        return insert(m_length, e);
    }

    bool remove(int i)
    {
        bool ret = ((i >= 0) && (i <= m_length));
        if (ret)
        {
            for (int p = i; p < m_length - 1; p++)
            {
                m_array[p] = m_array[p + 1];
            }
            m_length--;
        }

        return ret;
    }

    bool set(int i, const T &e)
    {
        bool ret = ((i >= 0) && (i <= m_length));
        if(ret)
        {
            m_array[i] = e;
        }
        return ret;
    }

    bool get(int i, T &e)
    {
        bool ret = ((i >= 0) && (i <= m_length));
        if(ret)
        {
            e = m_array[i];
        }
        return ret;
    }

    int find(const T& e) const
    {
        int ret = -1;
        for(int i = 0; i < m_length; i++)
        {
            if(m_array[i] == e)
            {
                ret = i;
                break;
            }
        }
        return ret;
    }

    int length() const
    {
        return m_length;
    }

    void clear()
    {
        m_length = 0;   // 清空线性表意味着这个线性表没有任何元素
    }

    // 顺序存储线性表的数组访问形式
    T &operator[](int i)
    {
        if((i >= 0) && (i < m_length))
        {
            return m_array[i];
        }
        else
        {// i的位置不合法，抛异常
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
        }
    }

    T operator[](int i) const
    {
        return (const_cast<SeqList<T> &>(*this))[i];
    }

    // 顺序存储空间的容量
    virtual int capacity() const = 0;
};

} // namespace DTLib

#endif // !SEQLIST_H
