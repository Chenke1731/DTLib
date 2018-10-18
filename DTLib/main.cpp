#include <windows.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "BTree.h"
#include "CircleList.h"
#include "DTString.h"
#include "DualLinkList.h"
#include "DynamicArray.h"
#include "Dynamiclist.h"
#include "Exception.h"
#include "GTree.h"
#include "LinkList.h"
#include "LinkQueue.h"
#include "LinkStack.h"
#include "Object.h"
#include "SeqList.h"
#include "SharedPointer.h"
#include "SmartPointer.h"
#include "Sort.h"
#include "StaticArray.h"
#include "StaticLinkList.h"
#include "StaticList.h"
#include "StaticQueue.h"
#include "StaticStack.h"
#include "Tree.h"

using namespace std;
using namespace DTLib;

int main()
{
    BTree<int>      bt;
    BTreeNode<int>* n = nullptr;
    bt.insert(1);
    n = bt.find(1);
    bt.insert(2, n);
    bt.insert(3, n);
    n = bt.find(2);
    bt.insert(4, n);
    bt.insert(5, n);
    n = bt.find(4);
    bt.insert(8, n);
    bt.insert(9, n);
    n = bt.find(5);
    bt.insert(10, n);
    n = bt.find(3);
    bt.insert(6, n);
    bt.insert(7, n);

    int a[] = {8, 9, 10, 6, 7};

    SharedPointer<Tree<int>> sp = bt.remove(3);

    for (int i = 0; i < 5; i++)
    {
        TreeNode<int>* node = bt.find(a[i]);
        while (node)
        {
            //cout << node->value << " ";
            node = node->parent;
        }
        //cout << endl;
    }

    return 0;
}
