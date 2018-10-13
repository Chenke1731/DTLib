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
protected:
  bool m_flag;

  void *operator new(size_t size) throw()
  {
    return Object::operator new(size); // new重载沿用Object中的new就可以了，保护，不能被外部访问
  }

public:
	LinkList<GTreeNode<T> *> child;

	GTreeNode() 
	{ 
		m_flag = false; 
	}

	bool flag() 
	{ 
		return m_flag; 
	}

  // 提供工厂方法
	static GTreeNode<T> *NewNode()
	{
		GTreeNode<T> *ret = new GTreeNode<T>();
		if (ret != NULL)
		{
			ret->m_flag = true; // 创建成功，进行标记
		}
		return ret;
	}
};

} // namespace DTLib
#endif // !GTREENODE
