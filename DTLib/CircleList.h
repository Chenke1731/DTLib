#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include "LinkList.h"

namespace DTLib
{
template <typename T>
class CircleList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;

    int mod (int i) const
    {
        return (this->m_length == 0) ? 0 : (i % this->m_length);
    }

    Node *last () const    // 获得指向最后一个结点的指针
    {
        return this->position (this->m_length - 1)->next;
    }
    void last_to_first ()
    {
        last ()->next = this->m_header->next;
    }

public:
    bool insert (const T &e)
    {
        return insert (this->m_length, e);
    }
    bool insert (int i, const T &e)
    {
        bool ret = true;

        i   = i % (this->m_length + 1);      // 对i进行归一化处理
        ret = LinkList<T>::insert (i, e);    // 用父类的insert函数来实现

        // 注意首尾相连
        if (ret && (i == 0))
        {
            last_to_first ();
        }

        return ret;
    }

    bool remove (int i)
    {
        bool ret = true;

        i = mod (i);
        if (i == 0)
        {
            Node *toDel = this->m_header->next;
            if (toDel != NULL)
            {
                this->m_header->next = toDel->next;
                this->m_length--;
                if (this->m_length > 0)    // 在还有元素的时候挪动
                {
                    last_to_first ();
                    if (this->m_current == toDel)
                    {
                        this->m_current = toDel->next;
                    }
                }
                else
                {
                    this->m_header->next = NULL;
                    this->m_current      = NULL;
                }
                this->destroy (toDel);
            }
            else
            {
                ret = false;
            }
        }
        else
        {    // 删除非首结点
            ret = LinkList<T>::remove (i);
        }

        return ret;
    }

    bool set (int i, const T &e)
    {
        return LinkList<T>::set (mod (i), e);
    }

    T get (int i) const
    {
        return LinkList<T>::get (mod (i));
    }

    bool get (int i, const T &e) const
    {
        return LinkList<T>::get (mod (i), e);
    }

    int find (const T &e) const
    {
        int ret = -1;
        // last()->next = NULL;
        // 将尾结点的next指针置空，循环链表变成了单链表
        // ret = LinkList<T>::find(e);
        // last_to_first();
        // 但是这样就改变了循环链表的状态，不能这样干，因为find里面可能发生异常，循环链表就变成单链表了
        // 不是异常安全的
        // 需要重新实现find函数

        Node *slider = this->m_header->next;
        for (int i = 0; i < this->m_length; i++)
        {
            if (slider->value == e)
            {
                ret = i;
                break;
            }
            slider = slider->next;
        }
        // 异常安全，比较的时候就算发生异常，也不会造成循环链表的状态改变

        return ret;
    }

    void clear ()
    {
        if (this->m_length > 0)
        {
            // last()->next = NULL;
            // LinkList<T>::clear();
            // 同样的问题，clear里面如果发生异常，不能保证异常安全性
            while (this->m_length > 1)
            {
                remove (1);    // 只要当前结点的长度大于1，就将结点1删除，直到所有元素删除
                // 不用remove(0)的原因是：考虑到效率问题
                // 每次remove(0)都会调用last_to_first等一大批操作
                // 删除非首结点就快很多
                // 所以选择删除结点1，这样最后就只会剩下结点0和首结点，再单独处理
            }
            if (this->m_length == 1)
            {
                Node *toDel          = this->m_header->next;
                this->m_header->next = NULL;
                this->m_length       = 0;
                this->m_current      = NULL;
                this->destroy (toDel);
            }
        }
    }

    // 重新实现遍历操作
    bool move (int i, int step)
    {
        return LinkList<T>::move (mod (i), step);
    }

    bool end ()
    {
        return (this->m_length == 0) || (this->m_current == NULL);
    }

    ~CircleList ()
    {
        clear ();
    }
};

}    // namespace DTLib

#endif    // CIRCLELIST_H
