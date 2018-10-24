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

#ifdef v
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

    //    cout << "Old tree " << endl;
    //    for (int i = 0; i < 5; i++)
    //    {
    //        TreeNode<int>* node = bt.find(a[i]);
    //        while (node)
    //        {
    //            cout << node->value << " ";
    //            node = node->parent;
    //        }
    //        cout << endl;
    //    }
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

    // SharedPointer<Array<int>> sp1 = r->traversal(LevelOrder);
    SharedPointer<Array<int>> sp1 = bt.traversal(LevelOrder);
    //    for (bt.begin(); !bt.end(); bt.next())
    //    {
    //        cout << bt.current() << endl;
    //    }
    for (int i = 0; i < (*sp1).length(); i++)
    {
        cout << (*sp1)[i] << " ";
    }
    cout << endl;

    cout << "thread..." << endl;
    BTreeNode<int>* head = bt.thread(LevelOrder);
    while (head->right != NULL)
    {
        head = head->right;
    }
    while (head != NULL)
    {
        cout << head->value << " ";
        head = head->left;
    }
    cout << endl;

    cout << endl;
    return 0;
}
#endif

template <typename T>
BTreeNode<T>* createTree()
{
    static BTreeNode<int> ns[9];

    for (int i = 0; i < 9; i++)
    {
        ns[i].value  = i;
        ns[i].parent = nullptr;
        ns[i].left   = nullptr;
        ns[i].right  = nullptr;
    }

    ns[0].left   = &ns[1];
    ns[0].right  = &ns[2];
    ns[1].parent = &ns[0];
    ns[2].parent = &ns[0];

    ns[1].left   = &ns[3];
    ns[1].right  = nullptr;
    ns[3].parent = &ns[1];

    ns[2].left   = &ns[4];
    ns[2].right  = &ns[5];
    ns[4].parent = &ns[2];
    ns[5].parent = &ns[2];

    ns[3].left   = nullptr;
    ns[3].right  = &ns[6];
    ns[6].parent = &ns[3];

    ns[4].left   = &ns[7];
    ns[4].right  = nullptr;
    ns[7].parent = &ns[4];

    ns[5].left   = &ns[8];
    ns[5].right  = nullptr;
    ns[8].parent = &ns[5];

    return ns;
}

template <typename T>
void printInOrder(BTreeNode<T>* node)
{
    if (node != nullptr)
    {
        printInOrder(node->left);

        cout << node->value << " ";

        printInOrder(node->right);
    }
}

template <typename T>
void printDualList(BTreeNode<T>* node)
{
    BTreeNode<T>* g = node;

    cout << "head -> tail: " << endl;

    while (node != nullptr)
    {
        cout << node->value << " ";

        g = node;

        node = node->right;
    }

    cout << endl;

    cout << "tail -> head: " << endl;

    while (g != nullptr)
    {
        cout << g->value << " ";

        g = g->left;
    }

    cout << endl;
}

template <typename T>
BTreeNode<T>* delOdd1(BTreeNode<T>* node)
{
    BTreeNode<T>* ret = nullptr;
    if (node != NULL)
    {
        if (((node->left != nullptr) && (node->right == nullptr)) || ((node->left == nullptr) && (node->right != nullptr)))
        {                                                                                  // 度为1，要么有左孩子，要么有右孩子
            BTreeNode<T>* parent     = dynamic_cast<BTreeNode<T>*>(node->parent);          // 指向父结点
            BTreeNode<T>* node_child = (node->left != NULL) ? node->left : node->right;    // node_child指向node的唯一孩子
            if (parent != NULL)
            {
                // 找到node是parent的哪个指针，然后建立这个指针的引用，指向node_child，断开与node的连接，再建立node_child与parent之间的联系
                BTreeNode<T>*& parent_child = (parent->left == node) ? parent->left : parent->right;
                parent_child                = node_child;
                node_child->parent          = parent;
                if (node->flag())
                    delete node;
            }
            else
            {    // parent为空，node就是根节点，根节点就是单度结点，删除
                node_child->parent = nullptr;
                // node = NULL;
            }
            ret = delOdd1(node_child);
        }
        else
        {    // 度为0 或 2
            delOdd1(node->left);
            delOdd1(node->right);
            ret = node;
        }
    }
    return ret;
}

template <typename T>
void delOdd2(BTreeNode<T>*& node)
{
    if (node != nullptr)
    {
        if (((node->left != nullptr) && (node->right == nullptr)) || ((node->left == nullptr) && (node->right != nullptr)))
        {    // 度为1，要么有左孩子，要么有右孩子

            BTreeNode<T>* node_child = (node->left != nullptr) ? node->left : node->right;    // node_child指向node的唯一孩子

            if (node->flag())
                delete node;

            node = node_child;
            delOdd2(node);
        }
        else
        {    // 度为0 或 2
            delOdd2(node->left);
            delOdd2(node->right);
        }
    }
}

// 中序线索化二叉树1
template <typename T>
void inOdrerThread(BTreeNode<T>* node, BTreeNode<T>* pre)
{
    if (node != nullptr)
    {
        // 线索化左子树
        inOrderThread(node->left, pre);
        node->left = pre;
        if (pre != nullptr)
            pre->right = node;
        pre = node;
        inOrderThread(node->right, pre);
    }
}
template <typename T>
BTreeNode<T>* inOrderThread1(BTreeNode<T>* node)
{
    BTreeNode<T>* pre = nullptr;
    inOrderThread(node, pre);
    // node 指向的不再是根节点，而是双链表中的其中某个结点
    // 找到首结点
    while ((node != nullptr) && (node->left = nullptr))
        node = node->left;
    return node;
}
// 中序线索化二叉树2
template <typename T>
void inOrderThread(BTreeNode<T>* node, BTreeNode<T>*& head, BTreeNode<T>*& tail)
{
    if (node != nullptr)
    {
        BTreeNode<T>* h = nullptr;
        BTreeNode<T>* t = nullptr;
        inOrderThread(node->left, h, t);
        node->left = t;
        if (t != nullptr)
            t->right = node;
        // 确定头结点
        head = (h != nullptr) ? h : node;

        h = nullptr;
        t = nullptr;
        inOrderThread(node->right, h, t);
        node->right = h;
        if (h != nullptr)
            h->left = node;
        // 确定尾结点
        tail = (t != nullptr) ? t : node;
    }
}
template <typename T>
BTreeNode<T>* inOrderThread2(BTreeNode<T>* node)
{
    BTreeNode<T>* head = nullptr;
    BTreeNode<T>* tail = nullptr;
    inOrderThread(node, head, tail);

    return head;
}

int main()
{
    BTreeNode<int>* ns = createTree<int>();

    printInOrder(ns);

    cout << endl;

    //    ns = delOdd1(ns);
    //    printInOrder(ns);
    //    cout << endl;
    //    cout << endl;
    //    int a[] = {6, 7, 8};
    //    for (int i = 0; i < 3; i++)
    //    {
    //        TreeNode<int>* n = ns + a[i];
    //        while (n != nullptr)
    //        {
    //            cout << n->value << " ";
    //            n = n->parent;
    //        }
    //        cout << endl;
    //    }
    //    cout << endl;
    //    delOdd2(ns);
    //    printInOrder(ns);

    //    cout << endl;

    ns = inOrderThread2(ns);
    printDualList(ns);

    return 0;
}
