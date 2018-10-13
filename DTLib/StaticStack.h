#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "Stack.h"
#include "Exception.h"

namespace DTLib
{

template <typename T, int N>
class StaticStack : public Stack<T>
{
  protected:
    T m_sapce[N]; // 栈存储空间
    int m_top;    // 栈顶标识
    int m_size;   // 当前栈的大小

  public:
    StaticStack()   //O(1)
    {
        m_top = -1;
        m_size = 0;
    }
	void push(const T &e) // O(1)
    // void push(const T& e)
    {
        if(m_size < N)
        {
            m_sapce[m_top + 1] = e; // 保证异常安全性，先不移动栈顶标识，就算赋值出问题，也不会影响整个栈的数据
            m_top++;   
            m_size++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current stack...");
        }
    }

    void pop()  // O(1)
    {
        if(m_size > 0)
        {
            m_top--;
            m_size--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack...");
        }
    }

    T top() const // O(1)
    {
        if(m_size > 0)
        {
            return m_sapce[m_top];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack...");
        }
    }

    void clear()    // O(1)
    {
        m_top = -1;
        m_size = 0;
    }

    int size() const // O(1)
    {
        return m_size;
    }

    int capacity() const //O(1)
    {
        return N;
    }
};

} // namespace DTLib

#endif // !STATICSTACK_H
