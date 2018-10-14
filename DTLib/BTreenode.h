#ifndef BTREENODE_H
#define BTREENODE_H

#include "TreeNode.h"

namespace DTLib
{


template <typename T>
class BTreeNode : public TreeNode<T>
{
public:
    BTreeNode<T>* left;
    BTreeNode<T>* right;

    BTreeNode()
    {
        left = NULL;
        right = NULL;
    }

    // 工厂方法
    static BTreeNode<T> *NewNode()
    {
        BTreeNode<T> *ret = new BTreeNode<T>();
        if (ret != NULL)
        {
            ret->m_flag = true; // 创建成功，进行标记
        }
        return ret;
    }
};


}


#endif // BTREENODE_H
