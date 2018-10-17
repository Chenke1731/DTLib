#ifndef GTREENODE
#define GTREENODE

#include "LinkList.h"
#include "Tree.h"
#include "TreeNode.h"

namespace DTLib
{
template <typename T>
class GTreeNode : public TreeNode<T>
{
public:
    LinkList<GTreeNode<T> *> child;

    // 提供工厂方法
    static GTreeNode<T> *NewNode ()
    {
        GTreeNode<T> *ret = new GTreeNode<T> ();
        if (ret != NULL)
        {
            ret->m_flag = true;    // 创建成功，进行标记
        }
        return ret;
    }
};

}    // namespace DTLib
#endif    // !GTREENODE
