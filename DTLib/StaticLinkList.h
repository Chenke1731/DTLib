#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"

namespace DTLib
{

template <typename T, int N>
class StaticLinkList : public LinkList<T>
{
  protected:
    typedef typename LinkList<T>::Node Node;

    struct SNode : public Node
    {
        // 查看new操作的重载
        void *operator new(size_t size, void *loc)
        {
            (void)size;
            return loc;
        }
    };

    unsigned char m_sapce[sizeof(Node) * N]; // 定义内存空间，用unsigned char ?
    int m_used[N];                           // 状态标记

    // 重写create函数
    Node *create()
    {
        SNode *ret = NULL; // 不会调用Node的构造函数，泛指类型 T value 中，T如果是自定义类类型，就不会调用到构造函数了
        // 分配好内存之后，还需要在指定内存上调用构造函数，需要重载new操作符，通过定义一个新的类型来解决
        //
        for (int i = 0; i < N; i++)
        {
            if (!m_used[i])
            {
                ret = reinterpret_cast<SNode *>(m_sapce) + i;
                ret = new (ret) SNode(); // 在指定的空间ret中，调用构造函数 SNode()
                m_used[i] = 1;
                break;
            }
        }
        return ret;
    }

    void destroy(Node *pn)
    {
        SNode *space = reinterpret_cast<SNode *>(m_sapce);
        SNode *psn = dynamic_cast<SNode *>(pn);
        for (int i = 0; i < N; i++)
        {
            if (psn == (space + i))
            { // 第i号内存单元需要归还
                m_used[i] = 0;
                // 调用析构函数
                psn->~SNode();
                break;
            }
        }
    }

  public:
    StaticLinkList()
    {
        for (int i = 0; i < N; i++)
        {
            m_used[i] = 0;
        }
    }

    int capacity()
    {
        return N;
    }

    ~StaticLinkList()
    {
        this->clear();
    }
};

} // namespace DTLib

#endif // !STATICLINKLIST_H
