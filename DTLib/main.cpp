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
#include "Graph.h"
#include "LinkList.h"
#include "LinkQueue.h"
#include "LinkStack.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
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
    //    MatrixGraph<3, int, int> g;
    //    g.setEdge(0, 1, 2);
    //    g.setEdge(1, 0, 1);
    //    g.setEdge(1, 2, 3);
    //    cout << g.vCount() << endl;
    //    cout << g.eCount() << endl;
    //    cout << g.OD(1) << endl;
    //    cout << g.ID(1) << endl;

    //    cout << g.getEdge(0, 1) << endl;
    //    cout << g.getEdge(1, 0) << endl;

    //    cout << "g.getAdjaent(1) : ";
    //    SharedPointer<Array<int>> aj = g.getAdjaent(1);
    //    for (int i = 0; i < aj->length(); i++)
    //    {
    //        cout << (*aj)[i] << "   ";
    //    }

    ListGraph<char, int> g(4);
    g.setVertex(0, 'A');
    g.setVertex(1, 'B');
    g.setVertex(2, 'C');
    g.setVertex(3, 'D');
    for (int i = 0; i < g.vCount(); i++)
    {
        cout << i << " : " << g.getVertex(i) << endl;
    }
    g.setEdge(0, 1, 5);
    g.setEdge(0, 3, 5);
    g.setEdge(1, 2, 8);
    g.setEdge(2, 3, 2);
    g.setEdge(3, 1, 9);

    cout << "W(0, 1) : " << g.getEdge(0, 1) << endl;
    cout << "W(0, 3) : " << g.getEdge(0, 3) << endl;
    cout << "W(1, 2) : " << g.getEdge(1, 2) << endl;
    cout << "W(2, 3) : " << g.getEdge(2, 3) << endl;
    cout << "W(3, 1) : " << g.getEdge(3, 1) << endl;

    SharedPointer<Array<int>> aj = g.getAdjaent(0);
    for (int i = 0; i < aj->length(); i++)
    {
        cout << (*aj)[i] << endl;
    }
    cout << "ID(1) : " << g.ID(1) << endl;
    cout << "OD(1) : " << g.OD(1) << endl;
    cout << "TD(1) : " << g.TD(1) << endl;

    return 0;
}
