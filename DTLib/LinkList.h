#ifndef LINKLIST_H
#define LINKLIST_H

#include <cstdlib>

#include "Exception.h"
#include "List.h"
namespace DTLib
{
template <typename T>
class LinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T     value;    // 数据域
        Node* next;     // 指针域
    };

    /* 	Node header;
    mutable Node *m_header = &header; // 头结点 */

    // 头结点优化，避免使用泛指类型T在库中创建对象
    // 完全模拟头结点的内存分布
    struct : public Object
    {
        char  reserved[sizeof (T)];
        Node* next;
    } header;
    // 转换成指针使用，使头结点是一个头结点指针，看起来统一
    mutable Node* m_header = reinterpret_cast<Node*> (&header);

    int m_length;    // 长度信息

    int   m_step;
    Node* m_current;

    // 抽象出位置定位函数，定位的位置其实是i-1的位置
    Node* position (int i) const
    {
        Node* ret = m_header;
        for (int p = 0; p < i; p++)
        {
            ret = ret->next;
        }
        return ret;
    }

    // 用来在堆空间中创建Node对象
    virtual Node* create ()
    {
        return new Node ();
    }
    // 释放参数指针指向的Node对象
    virtual void destroy (Node* pn)
    {
        delete pn;
    }

public:
    LinkList ()
    {
        header.next = NULL;
        m_length    = 0;
        m_step      = 1;
        m_current   = NULL;
    }

    // 指定位置插入元素
    bool insert (int i, const T& e)
    {
        bool ret = ((i >= 0) && (i <= m_length));
        if (ret)
        {
            // Node *node = new Node();
            Node* node = create ();
            if (node != NULL)
            {
                // current的位置其实是i-1的位置，在current后面位置插入就是i位置了
                /*                 Node *current = m_header;
                for (int p = 0; p < i; p++)
                {
                    current = current->next;
                } */
                Node* current = position (i);
                // 元素插入操作
                node->value   = e;
                node->next    = current->next;
                current->next = node;

                m_length++;
            }
            else
            {
                THROW_EXCEPTION (NoEnoughMemoryException, "No memory to insert new element");
            }
        }
        return ret;
    }

    // 链表末尾插入元素
    bool insert (const T& e)
    {
        return insert (m_length, e);
    }

    // 删除指定位置元素
    bool remove (int i)
    {
        bool ret = ((i >= 0) && (i < m_length));
        if (ret)
        {
            /*             Node *current = m_header;
            for (int p = 0; p < i; p++)
            {
                current = current->next;
            } */
            Node* current = position (i);
            Node* toDel   = current->next;

            if (m_current == toDel)
            {
                m_current = toDel->next;
            }
            current->next = toDel->next;

            m_length--;
            // delete toDel;
            destroy (toDel);
        }
        else
        {
            // 为什么不抛异常
        }

        return ret;
    }

    bool set (int i, const T& e)
    {
        bool ret = ((i >= 0) && (i < m_length));
        if (ret)
        {
            /*             Node *current = m_header->next;
            for (int p = 0; p < i; p++)
            {
                current = current->next;
            } */
            Node* current  = position (i)->next;
            current->value = e;
        }

        return ret;
    }

    bool get (int i, T& e) const
    {
        bool ret = ((i >= 0) && (i < m_length));
        if (ret)
        {
            /* Node *current = m_header->next;
            for (int p = 0; p < i; p++)
            {
                current = current->next;
            } */
            Node* current = position (i)->next;
            e             = current->value;
        }

        return ret;
    }

    // 重载get函数
    T get (int i) const
    {
        T ret;
        if (get (i, ret))
        {
            return ret;
        }
        else
        {
            THROW_EXCEPTION (IndexOutOfBoundsException, "Invalid parameter i to get element...");
        }
    }

    int find (const T& e) const
    {
        int   ret  = -1;
        int   i    = 0;
        Node* node = m_header->next;
        while (node)
        {
            if (node->value == e)    // 这里存在一个问题，e和value均是泛指类型，==操作符需要重载，否则编译不过
            {
                ret = i;
                break;
            }
            else
            {
                node = node->next;
                i++;
            }
        }
        return ret;
    }

    int length () const
    {
        return m_length;
    }

    void clear ()
    {
        // 释放每一个结点
        while (m_header->next)
        {
            Node* toDel    = m_header->next;
            m_header->next = toDel->next;

            m_length--;
            // delete toDel;
            destroy (toDel);
        }
    }

    // 遍历函数的优化设计
    // i 目标位置，step 游标每次从i开始移动结点的数目
    bool move (int i, int step = 1)
    {
        bool ret = ((i >= 0) && (i < m_length) && (step > 0));
        if (ret)
        {    // 将游标定位到目标位置i的地方
            m_current = position (i)->next;
            m_step    = step;
        }
        return ret;
    }

    bool end ()
    {
        return (m_current == NULL);
    }
    T current ()
    {    // 返回当前游标位置的元素值
        if (!end ())
        {
            return m_current->value;
        }
        else
        {
            THROW_EXCEPTION (InvalidOperationException, "No value at current position...");
        }
    }

    bool next ()
    {    // 根据step移动游标
        int i = 0;
        while ((i < m_step) && !end ())
        {
            m_current = m_current->next;
            i++;
        }
        // i和m_step的值是一样的，就表示移动成功
        return (i == m_step);
    }

    ~LinkList ()
    {
        clear ();
    }
};

}    // namespace DTLib

#endif    // !LINKLIST_H
