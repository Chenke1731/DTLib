#ifndef TREE
#define TREE

#include "Object.h"

namespace DTLib
{

template <typename T>
class TreeNode : public Object
{

  public:
    T value;
    TreeNode<T> *parent;

    TreeNode() { parent = NULL; }

    virtual ~TreeNode() = 0;
};

template <typename T>
TreeNode<T>::~TreeNode() {}

} // namespace DTLib

#endif // !TREE
