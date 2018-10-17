#ifndef BTREE_H
#define BTREE_H

#include "BTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"
#include "Tree.h"

namespace DTLib
{
template <typename T>
class BTree : public Tree<T>
{
public:
    bool insert (TreeNode<T>* node)
    {
        int ret = true;

        return ret;
    }

    bool insert (const T& value, TreeNode<T>* parent)
    {
        int ret = true;

        return ret;
    }

    SharedPointer<Tree<T>> remove (const T& value)
    {
        return NULL;
    }

    // 删除一个结点，后续结点可以全部删除
    // 删除这个结点，并返回这棵树，可以对这颗树进行具体操作
    SharedPointer<Tree<T>> remove (TreeNode<T>* node)
    {
        return NULL;
    }

    BTreeNode<T>* find (const T& value) const
    {
        return NULL;
    }

    BTreeNode<T>* find (TreeNode<T>* node) const
    {
        return NULL;
    }

    BTreeNode<T>* root () const
    {
        return dynamic_cast<BTreeNode<T>*> (this->m_root);
    }

    int degree () const
    {
        return 0;
    }

    int count () const
    {
        return 0;
    }

    int height () const
    {
        return 0;
    }

    void clear ()
    {
        this->m_root = NULL;
    }

    ~BTree ()
    {
        clear ();
    }
};

}    // namespace DTLib

#endif    // BTREE_H
