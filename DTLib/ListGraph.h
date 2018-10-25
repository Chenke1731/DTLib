#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "DynamicArray.h"
#include "Graph.h"
#include "LinkList.h"
#include "Object.h"

namespace DTLib
{
template <typename V, typename E>
class ListGraph : public Graph<V, E>
{
protected:
    struct Vertex : public Object
    {
        V* data;

        LinkList<Edge<E>> edge;
        Vertex()
        {
            data = NULL;
        }
    };

    LinkList<Vertex*> m_list;

public:
    ListGraph(unsigned int n = 0)
    {
        for (unsigned int i = 0; i < n; i++)
        {
            addVertex();
        }
    }

    int addVertex()
    {
        int ret = -1;    // 返回值为编号

        Vertex* v = new Vertex();
        if (v != NULL)
        {
            m_list.insert(v);
            ret = m_list.length() - 1;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat object...");
        }

        return ret;
    }

    bool setVertex(int i, const V& value)
    {
        bool ret = ((i >= 0) && i < vCount());
        if (ret)
        {
            // 取出i位置的数据元素
            Vertex* vertex = m_list.get(i);
            V*      data   = vertex->data;
            if (data == NULL)
            {    // 没有指向具体的数据元素
                 // 在堆空间中创建一个与顶点数据元素类型相关的对象
                data = new V();
            }
            if (data != NULL)
            {
                *data        = value;
                vertex->data = data;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat new V...");
            }
        }
        return ret;
    }

    V getVertex(int i)
    {
        V ret;
        if (!getVertex(i, ret))
        {
            THROW_EXCEPTION(InvalidParameteException, "Index i is invalid...");
        }
        return ret;
    }
    bool getVertex(int i, V& value)
    {
        bool ret = ((i >= 0) && i < vCount());
        if (ret)
        {
            Vertex* vertex = m_list.get(i);
            if (vertex->data != NULL)
            {
                value = *(vertex->data);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value in this vertex...");
            }
        }

        return ret;
    }

    void removeVertex()
    {
        // 判断顶点是否存在
        if (m_list.length() > 0)
        {
            // 取出编号
            int     index  = m_list.length() - 1;
            Vertex* vertex = m_list.get(index);
            if (m_list.remove(index))
            {    // 从链表中删除成功
                // 删除边
                // 查找是否存在与该结点相邻接的边
                // 遍历查找
                for (int i = (m_list.move(0), 0); !m_list.end(); m_list.next(), i++)
                {
                    int pos = m_list.current()->edge.find(Edge<E>(i, index));
                    if (pos >= 0)
                    {
                        m_list.current()->edge.remove(pos);
                    }
                }
                delete vertex->data;
                delete vertex;
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No vertex in current graph...");
        }
    }

    SharedPointer<Array<int>> getAdjaent(int i)
    {
        // 遍历邻接链表，得到邻接顶点
        DynamicArray<int>* ret = NULL;
        if ((i >= 0) && (i < vCount()))
        {
            // 获取顶点
            Vertex* vertex = m_list.get(i);
            // 创建返回值数组
            ret = new DynamicArray<int>(vertex->edge.length());
            if (ret != NULL)
            {
                // 遍历vertex->edge
                for (int k = (vertex->edge.move(0), 0); !vertex->edge.end(); vertex->edge.next(), k++)
                {
                    ret->set(k, vertex->edge.current().e);
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat new DynamicArray...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameteException, "Index i is invalid...");
        }

        return ret;
    }
    bool isAdjacent(int i, int j)
    {
        return (i >= 0) && (i < vCount()) && (j >= 0) && (j < vCount()) && ((m_list.get(i)->edge.find(Edge<E>(i, j)) >= 0));
    }

    E getEdge(int i, int j)
    {
        E ret;
        if (!getEdge(i, j, ret))
        {
            THROW_EXCEPTION(InvalidParameteException, "Index <i, j> is invalid...");
        }
        return ret;
    }
    bool getEdge(int i, int j, E& value)
    {    // <i, j>的权值
        bool ret = ((i >= 0) && (i < vCount()) && (j >= 0) && (j < vCount()));
        if (ret)
        {
            Vertex* vertex = m_list.get(i);
            int     pos    = vertex->edge.find(Edge<E>(i, j));    // 找到邻接矩阵中的具体位置，然后取出权值
            if (pos >= 0)
            {
                value = vertex->edge.get(pos).data;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this edge...");
            }
        }
        return ret;
    }
    bool setEdge(int i, int j, const E& value)
    {
        bool ret = ((i >= 0) && (i < vCount()) && (j >= 0) && (j < vCount()));
        if (ret)
        {
            Vertex* vertex = m_list.get(i);
            int     pos    = vertex->edge.find(Edge<E>(i, j));
            if (pos >= 0)
            {
                ret = vertex->edge.set(pos, Edge<E>(i, j, value));
            }
            else
            {    // 该边不存在，增加一条边
                ret = vertex->edge.insert(0, Edge<E>(i, j, value));
            }
        }
        return ret;
    }
    bool removeEdge(int i, int j)
    {
        bool ret = ((i >= 0) && (i < vCount()) && (j >= 0) && (j < vCount()));
        if (ret)
        {
            Vertex* vertex = m_list.get(i);
            int     pos    = vertex->edge.find(Edge<E>(i, j));
            if (pos >= 0)
            {
                ret = vertex->edge.remove(pos);
            }
        }
        return ret;
    }

    int vCount()
    {
        return m_list.length();
    }

    int eCount()
    {
        int ret = 0;
        // 遍历链表统计
        for (m_list.move(0); !m_list.end(); m_list.next())
        {
            ret += m_list.current()->edge.length();
        }
        return ret;
    }
    int OD(int i)
    {
        return m_list.get(i)->edge.length();
    }
    int ID(int i)
    {
        int ret = 0;
        if ((i >= 0) && (i < vCount()))
        {
            for (m_list.move(0); !m_list.end(); m_list.next())
            {
                // 当前节点的邻接链表的引用
                LinkList<Edge<E>>& edge = m_list.current()->edge;
                for (edge.move(0); !edge.end(); edge.next())
                {
                    if (edge.current().e == i)
                    {
                        ret++;
                        break;
                    }
                }
            }
        }
        return ret;
    }

    ~ListGraph()
    {
        // 销毁每一个元素
        while (m_list.length() > 0)
        {
            Vertex* toDel = m_list.get(0);
            m_list.remove(0);
            delete toDel->data;
            delete toDel;
        }
    }
};

}    // namespace DTLib

#endif    // LISTGRAPH_H
