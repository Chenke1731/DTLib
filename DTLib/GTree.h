#ifndef GTREE
#define GTREE

#include "Tree.h"
#include "GTreeNode.h"
#include "Exception.h"

namespace DTLib
{


template <typename T>
class GTree : public Tree<T>
{

  protected:
/*     GTreeNode<T> *find(GTreeNode<T> *node, const T &value) const
    {
        GTreeNode<T> *ret = NULL;
        if (node != NULL)
        {
            if (node->value == value)
                return node;
            else
            {
                for (node->child.move(0); !node->child.end() && ret == NULL; node->child.next())
                {
                    ret = find(node->child.current, value);
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameteException, "Parament node is invalid... ");
        }
        return ret;
    } */

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
        return NULL;
    }
    // 删除一个结点，后续结点可以全部删除
    // 删除这个结点，并返回这棵树，可以对这颗树进行具体操作
    SharedPointer<Tree<T>> remove(TreeNode<T> *node)
    {
        return NULL;
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
        return 0;
    }
    int count() const
    {
        return 0;
    }
    int height() const
    {
        return 0;
    }
    void clear()
    {
        free(root());
        this->m_root = NULL;
    }

    ~GTree()
    {
        clear();
    }
};

} // namespace DTLib

#endif // !GTREE
