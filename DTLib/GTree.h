#ifndef GTREE
#define GTREE

#include "Tree.h"
#include "GTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"

namespace DTLib
{


template <typename T>
class GTree : public Tree<T>
{

protected:
    // 树形结构的遍历采用队列实现
    LinkQueue<GTreeNode<T>*> m_queue;

    GTreeNode<T> * find(GTreeNode<T>* node, const T& value)const
    {
        GTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            if(node->value == value)
                return node;
            else
            {
                //  遍历子树链表指针
                for (node->child.move(0); !node->child.end() && ret == NULL; node->child.next())
                {
                    ret = find(node->child.current(), value); // current()返回当前位置的元素值，即一个GTreeNode指针
                }
            }
        }
        return ret;
    }

    GTreeNode<T> *find(GTreeNode<T> *node, GTreeNode<T> *obj) const
    {
        GTreeNode<T> *ret = NULL;
        if (node == obj)
            return node;
        else
        {
            if (node != NULL)
            {
                for (node->child.move(0); !node->child.end() && ret == NULL; node->child.next())
                {
                    ret = find(node->child.current(), obj);
                }
            }
        }
        return ret;
    }

    void free(GTreeNode<T>* node)   // 根节点
    {
        if(node!= NULL)
        {
            for (node->child.move(0); !node->child.end(); node->child.next())
            {
                free(node->child.current());
            }
			if (node->flag())
			{
				delete node;
			}            
        }
    }

    int count( GTreeNode<T> * node) const
    {
        int ret = 0;
        if(node !=  NULL)
        {
            ret = 1; // 因为node至少有一个结点
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                ret += count((node->child.current()));
            }
        }
        return ret;
    }

    int height(GTreeNode<T>* node) const
    {
        int ret = 0;
        if( node!=NULL )
        {
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                // 遍历子树，得到子树的最大高度
                int h = height(node->child.current());
                if(ret < h)
                    ret = h;
            }
            ret += 1;
        }

        return ret;
    }

    int degree(GTreeNode<T>* node) const
    {
        int ret = 0;
        if( node != NULL)
        {
            // 根节点的度数
            ret = node->child.length();
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                // 遍历子树求度数
                int d = degree(node->child.current());
                if(ret < d)
                    ret =d;
            }
        }

        return ret;
    }

    // 将node为根节点的子树从原来的树中删除
    // ret作为子树返回
    void remove(GTreeNode<T>* node, GTree<T>*& ret)
    {
        ret = new GTree<T>();
        if(ret != NULL)
        {
            if(root() == node)
            {
                this->m_root = NULL;
            }
            else
            {
                // 定义一个引用存放node的父节点中的孩子链表的别名
                LinkList<GTreeNode<T>*>& child = dynamic_cast<GTreeNode<T>*>(node->parent)->child;
                // 从孩子链表中删除node结点
                child.remove(child.find(node));
                node->parent =  NULL;
            }
            ret->m_root = node; // 将要删除的子树node保存下来返回
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree...");
        }
    }



public:
    bool insert(TreeNode<T> *node)
    {
        bool ret = true;

        if(node !=NULL)
        {   
            // 判断当前树是否为空
            if(this->m_root == NULL)
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else
            {
                // 首先取出node的父节点的地址
                GTreeNode<T> *np = find(node->parent);
                if (np != NULL)
                {
                    GTreeNode<T> *n = dynamic_cast<GTreeNode<T> *>(node); // 从父类型转换到子类型
                    // 找一下是否已经存在node
                    if(np->child.find(n) < 0)
                    {
                        np->child.insert(n);
                    }
                    
                }
                else
                {
                    THROW_EXCEPTION(InvalidOperationException, "Invalid parent tree node...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameteException, "Invalid parament tree node");
        }
        return ret;
    }

    bool insert(const T &value, TreeNode<T> *parent)
    {
        bool ret = true;

        // 首先新建一个GTreeNode结点
		GTreeNode<T> *node = GTreeNode<T>::NewNode();
        if(node != NULL)
        {
            node->value = value;
            node->parent = parent;
            insert(node);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memery to creat  new GTreeNode...");
        }

        return ret;
    }

    SharedPointer<Tree<T>> remove(const T &value)
    {
        // 返回要删除的子树
        GTree<T>* ret = NULL;
        GTreeNode<T>* node = find(value);   // 判断是否真的有value值的结点

        if(node != NULL)
        {
            remove(dynamic_cast<GTreeNode<T>*>(node), ret);
            m_queue.clear();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameteException, "Can nor find the node in via paramenter value...");
        }


        return ret;
    }

    // 删除一个结点，后续结点可以全部删除
    // 删除这个结点，并返回这棵树，可以对这颗树进行具体操作
    SharedPointer<Tree<T>> remove(TreeNode<T> *node)
    {
        // 返回要删除的子树
        GTree<T>* ret = NULL;
        node = find(node);   // 也要判断以下node是否存在

        if(node != NULL)
        {
            remove(dynamic_cast<GTreeNode<T>*>(node), ret);
            m_queue.clear();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameteException, "Can nor find the node in via paramenter value...");
        }


        return ret;
    }

    //改成GTreeNode，父子兼容性原则
    //TreeNode<T> *find(const T &value) const
    GTreeNode<T> *find(const T &value) const
    {
        return find(root(), value);
    }

    GTreeNode<T> *find(TreeNode<T> *node) const
    {
        return find(root(), dynamic_cast<GTreeNode<T>*> (node));
    }

    GTreeNode<T> *root() const
    {
        return dynamic_cast<GTreeNode<T> *>(this->m_root);
    }

    int degree() const
    {
        return degree(root());
    }

    int count() const
    {
        return count(root());
    }

    int height() const
    {
        return height(root());
    }

    // 遍历操作成员函数
    bool begin()    // 做队列的初始化工作
    {
        bool ret = (root() != NULL);    // 判断当前结点是否为空
        if( ret )
        {
            // 将根节点压入队中
            m_queue.clear();
            m_queue.add(root());
        }

        return ret;
    }

    bool end()
    {
        return (m_queue.length() == 0);
    }

    bool next()
    {
        // 判断队列中是否还有元素
        bool ret = (m_queue.length() > 0);
        if(ret)
        {
            // 出队操作
            GTreeNode<T>* node = m_queue.front();   // 取出保存队头，方便对头的结点的孩子入队
            m_queue.remove();   // 将对头出队，移动一次游标

            // 遍历node指向的头结点的孩子入队
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                m_queue.add(node->child.current());
            }

        }
        return ret;
    }

    // 返回头结点的元素值
    T current()
    {
        // 判断遍历是否结束
        // 只有在遍历的过程中，才有意义
        if( !end() )
        {
            return m_queue.front()->value;  // 队头即游标指向的元素值
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position...");
        }
    }

    void clear()
    {
        free(root());
        this->m_root = NULL;

        m_queue.clear();
    }

    ~GTree()
    {
        clear();
    }
};

} // namespace DTLib

#endif // !GTREE
