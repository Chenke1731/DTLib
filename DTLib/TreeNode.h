#ifndef TREE
#define TREE

#include "Object.h"

namespace DTLib
{

template <typename T>
class TreeNode : public Object
{

protected:
    bool m_flag;

    TreeNode(const TreeNode<T>&);
    TreeNode<T>& operator = (const TreeNode<T>&);

    void *operator new(size_t size) throw()
    {
        return Object::operator new(size); // new重载沿用Object中的new就可以了，保护，不能被外部访问
    }

public:
    T value;
    TreeNode<T> *parent;

    TreeNode()
    {
        m_flag = false;
        parent = NULL;
    }

    bool flag()
    {
        return m_flag;
    }

    virtual ~TreeNode() = 0;
};

template <typename T>
TreeNode<T>::~TreeNode() {}

} // namespace DTLib

#endif // !TREE
