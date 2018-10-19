﻿#include <windows.h>
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

    // SharedPointer<Tree<int>> sp = bt.remove(3);

    cout << "Old tree " << endl;
    for (int i = 0; i < 5; i++)
    {
        TreeNode<int>* node = bt.find(a[i]);
        while (node)
        {
            cout << node->value << " ";
            node = node->parent;
        }
        cout << endl;
    }
    //    for (bt.begin(); !bt.end(); bt.next())
    //    {
    //        cout << bt.current() << endl;
    //    }

    BTree<int> nbt;
    nbt.insert(0);
    n = nbt.find(0);
    nbt.insert(6, n);
    nbt.insert(2, n);
    n = nbt.find(2);
    nbt.insert(7, n);
    nbt.insert(8, n);

    SharedPointer<BTree<int>> r = bt.add(nbt);

    SharedPointer<Array<int>> sp1 = r->tranversal(PreOrder);
    for (int i = 0; i < (*sp1).length(); i++)
    {
        cout << (*sp1)[i] << " ";
    }

    cout << endl;
    return 0;
}
