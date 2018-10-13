#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include <cstdlib>
#include "Exception.h"
#include "Pointer.h"

namespace DTLib
{

template <typename T>
class SharedPointer : public Pointer<T>
{
  private:
    int *m_ref; // 计数机制成员指针

    void assign(const SharedPointer<T> &obj)
    {
        m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;
        if (m_ref)
        {
            (*m_ref)++;
        }
    }

  public:
    SharedPointer(T *p = NULL) : m_ref(NULL)
    {
        if (p)
        {
            // 在堆空间中创建一个4字节的计数变量
            m_ref = static_cast<int *>(std::malloc(sizeof(int)));
            if (m_ref)
            {                        // 计数变量申请成功
                this->m_pointer = p; // 指针指向堆空间
                *m_ref = 1;          //
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat SharedPointer object...");
            }
        }
    }

    SharedPointer(const SharedPointer<T> &obj)
    {
        /*  m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;
        if (m_ref)
        { // 计数变量合法
            (*m_ref)++;
        } */
        assign(obj);
    }

    SharedPointer<T> &operator=(const SharedPointer<T> &obj)
    {
        if (this != &obj)
        {
            clear();
            /* m_ref = obj.m_ref;
            this->m_pointer = obj.m_pointer;
            if (m_ref)
            { // 计数变量合法
                (*m_ref)++;
            } */
            assign(obj);
        }
        return *this;
    }
    void clear() // 置空当前指针
    {
        T *toDel = this->m_pointer;
        int *ref = m_ref;
        this->m_pointer = NULL;
        m_ref = NULL;
        if (ref)
        {
            (*ref)--;
            if (*ref == 0)
            {
                free(ref);
                delete toDel;
            }
        }
    }

	~SharedPointer()
	{
		clear();
	}
};


template <typename T>
bool operator == (const SharedPointer<T>& l, const SharedPointer<T>& r)
{
	return (l.get() == r.get());
}

template <typename T>
bool operator != (const SharedPointer<T>& l, const SharedPointer<T>& r)
{
	return !(l == r);   // !=操作符重载的实现用上面==操作的实现就可以了
}

} // namespace DTLib



#endif // !SHAREDPOINTER_H
