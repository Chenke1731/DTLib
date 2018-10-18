#ifndef BTREE_H
#define BTREE_H

#include "BTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"
#include "Tree.h"
namespace DTLib
{
enum BTNodePos
{
    ANY,
    LEFT,
    RIGHT
};

template <typename T>
class BTree : public Tree<T>
{
protected:
    BTreeNode<T>* find(BTreeNode<T>* node, const T& value) const    // 是否要加虚函数
    {
        BTreeNode<T>* ret = NULL;
        if (node != NULL)
        {    // 判断node是否为空
            if (node->value == value)
            {
                ret = node;
            }
            else
            {
                if (ret == NULL)
                    ret = find(node->left, value);
                if (ret == NULL)    // 左子树找不到就去找右子树
                    ret = find(node->right, value);
            }
        }

        return ret;
    }

    BTreeNode<T>* find(BTreeNode<T>* node, BTreeNode<T>* obj) const
    {
        BTreeNode<T>* ret = NULL;
        if (node != NULL && obj != NULL)
        {
            if (node == obj)
            {    // 根节点与被查找结点相等
                ret = node;
            }
            else
            {
                if (ret == NULL)
                    ret = find(node->left, obj);
                if (ret == NULL)
                    ret = find(node->right, obj);
            }
        }

        return ret;
    }

    bool insert(BTreeNode<T>* n, BTreeNode<T>* np, BTNodePos pos)
    {    // n 新节点， np 目标结点， pos 位置
        bool ret = true;
        switch (pos)
        {
            case ANY:
                if (np->left == NULL)
                    np->left = n;
                else if (np->right == NULL)
                    np->right = n;
                else
                    ret = false;
                break;
            case LEFT:
                if (np->left == NULL)
                    np->left = n;
                else
                    ret = false;
                break;
            case RIGHT:
                if (np->right == NULL)
                    np->right = n;
                else
                    ret = false;
                break;
        }

        return ret;
    }

    void remove(BTreeNode<T>* node, BTree<T>*& ret)
    {
        ret = new BTree<T>();
        if (ret != NULL)
        {
            if (root() == node)
            {
                // 清空根节点
                this->m_root = NULL;
            }
            else
            {    // 断去与父结点之间的联系
                BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);
                if (parent->left == node)
                    parent->left = NULL;
                else if (parent->right == node)
                    parent->right = NULL;
                node->parent = NULL;
            }
            ret->m_root = node;    // 返回子树
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat BTree...");
        }
    }

    void free(BTreeNode<T>* node)    // 根节点
    {
        if (node != NULL)
        {
            free(node->left);
            free(node->right);

            if (node->flag())
                delete node;
        }
    }

    int count(BTreeNode<T>* node) const
    {
        int ret = 0;
        if (node != NULL)
        {
            ret = count(node->left) + count(node->right) + 1;
        }

        return ret;
    }

    int height(BTreeNode<T>* node) const
    {
        int ret = 0;
        if (node != NULL)
        {
            // 求左子树的高度
            int lh = height(node->left);
            int rh = height(node->right);
            ret    = ((lh > rh) ? lh : rh) + 1;
        }

        return ret;
    }

    int degree(BTreeNode<T>* node) const
    {
        int ret = 0;
        if (node != NULL)
        {
            BTreeNode<T>* child[] = {node->left, node->right};
            ret                   = (!!node->left + !!node->right);
            for (int i = 0; (i < 2) && (ret < 2); i++)
            {
                int d = degree(child[i]);
                if (ret < d)
                    ret = d;
            }
        }

        return ret;
    }

public:
    bool insert(TreeNode<T>* node)
    {
        int ret = true;
        ret     = insert(node, ANY);
        return ret;
    }
    bool insert(TreeNode<T>* node, BTNodePos pos)
    {
        int ret = true;
        if (node != NULL)
        {
            if (root() == NULL)
            {    // 当前头结点为空
                this->m_root = node;
            }
            else
            {
                BTreeNode<T>* np = find(node->parent);
                if (np != NULL)
                {
                    ret = insert(dynamic_cast<BTreeNode<T>*>(node), np, pos);
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameteException, "Can not find the node in tree...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameteException, "The paramenter node is invlaide...");
        }
        return ret;
    }

    bool insert(const T& value, TreeNode<T>* parent = NULL)
    {
        int ret = true;
        ret     = insert(value, parent, ANY);
        return ret;
    }
    bool insert(const T& value, TreeNode<T>* parent, BTNodePos pos)
    {
        int ret = true;
        // 新申请一个结点，存放value
        BTreeNode<T>* node = BTreeNode<T>::NewNode();    // 不懂
        if (node != NULL)
        {
            node->value  = value;
            node->parent = parent;
            ret          = insert(node, pos);
            if (!ret)
            {
                delete node;    // 如果插入不成功，释放掉node
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to creat a tree node...");
        }

        return ret;
    }

    SharedPointer<Tree<T>> remove(const T& value)
    {
        BTree<T>*     ret  = NULL;
        BTreeNode<T>* node = find(value);
        if (node != NULL)
        {
            remove(node, ret);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameteException, "Can not find the tree node via value...");
        }

        return ret;
    }

    // 删除一个结点，后续结点可以全部删除
    // 删除这个结点，并返回这棵树，可以对这颗树进行具体操作
    SharedPointer<Tree<T>> remove(TreeNode<T>* node)
    {
        BTree<T>* ret = NULL;
        node          = find(node);    // 注意父子兼容性
        if (node != NULL)
        {
            remove(dynamic_cast<BTreeNode<T>*>(node), ret);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameteException, "Paramenter node is invalid...");
        }

        return ret;
    }

    BTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    BTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(), dynamic_cast<BTreeNode<T>*>(node));
    }

    BTreeNode<T>* root() const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
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

    void clear()
    {
        free(root());
        this->m_root = NULL;
    }

    ~BTree()
    {
        clear();
    }
};

}    // namespace DTLib

#endif    // BTREE_H
