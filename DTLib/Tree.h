#ifndef TREENODE
#define TREENODE

#include "TreeNode.h"
#include "SharedPointer.h"

namespace DTLib
{


template<typename T>
class Tree : public Object
{
protected:
  TreeNode<T> *m_root;

public:
	  Tree() { m_root = NULL; }
    virtual bool insert(TreeNode<T> *node) = 0;
    virtual bool insert(const T &value, TreeNode<T> *parent) = 0;
    virtual SharedPointer<Tree<T>> remove(const T &value) = 0;
    // 删除一个结点，后续结点可以全部删除
    // 删除这个结点，并返回这棵树，可以对这颗树进行具体操作
    virtual SharedPointer<Tree<T>> remove(TreeNode<T> *node) = 0;
    virtual TreeNode<T> *find(const T &value) const = 0;
    virtual TreeNode<T> *find(TreeNode<T> *node) const = 0;
    virtual TreeNode<T> *root() const = 0;
    virtual int degree() const = 0;
    virtual int count() const = 0;
    virtual int height() const = 0;
    virtual void clear() = 0;
};



} // namespace DTLib

#endif // !TREENODE
