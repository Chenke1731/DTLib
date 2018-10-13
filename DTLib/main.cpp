#include "CircleList.h"
#include "DTString.h"
#include "DualLinkList.h"
#include "DynamicArray.h"
#include "Dynamiclist.h"
#include "Exception.h"
#include "LinkList.h"
#include "LinkQueue.h"
#include "LinkStack.h"
#include "Object.h"
#include "SeqList.h"
#include "SharedPointer.h"
#include "SmartPointer.h"
#include "StaticArray.h"
#include "StaticLinkList.h"
#include "StaticList.h"
#include "StaticQueue.h"
#include "StaticStack.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "Sort.h"
#include <windows.h>
#include "Tree.h"
#include "GTree.h"


using namespace std;
using namespace DTLib;


int main()
{
	GTree<char> t;
	GTreeNode<char>* node = NULL;
	GTreeNode<char> root;	// 这个结点是在栈上定义的
	// 调用clear()函数之后，会有一步delete node，这个时候就会发生delete栈中的局部变量root了
	// 只有堆中的对象需要delete，栈中变量是不能直接被管理的
	// 所以需要处理delete栈中变量的问题
	root.value = 'A';
	root.parent = NULL;	

	const char*s = "KLFGMIJ";
	t.insert(&root);

	//t.insert('A', NULL);
	node = t.find('A');
	t.insert('B', node);
	t.insert('C', node);
	t.insert('D', node);

	node = t.find('B');
	t.insert('E', node);
	t.insert('F', node);
	
	node = t.find('E');
	t.insert('K', node);
	t.insert('L', node);

	node = t.find('C');
	t.insert('G', node);
	
	node = t.find('D');
	t.insert('H', node);
	t.insert('I', node);
	t.insert('J', node);
	
	node = t.find('H');
	t.insert('M', node);

	t.clear();
	
	for (int i = 0; i < 7; i++)
	{
		TreeNode<char>* node = t.find(s[i]);	// 找出叶节点， 可以用子类型对父类类型指针进行复赋值
		// 将叶节点当成链表的起始结点开始遍历
		while (node != NULL)
		{
			cout << node->value << " ";
			node = node->parent;
		}
		cout << endl;
	}
	
	return 0;
}


