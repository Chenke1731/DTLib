#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "DynamicArray.h"
#include "Graph.h"

namespace DTLib
{
template <int N, typename V, typename E>
class MatrixGraph : public Graph<V, E>
{
protected:
    V*  m_vertexes[N];
    E*  m_edges[N][N];
    int m_eCount;

public:
    MatrixGraph()
    {
        for (int i = 0; i < vCount(); i++)
        {
            m_vertexes[i] = NULL;
            for (int j = 0; j < vCount(); j++)
            {
                m_edges[i][j] = NULL;
            }
        }
        m_eCount = 0;
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
        int ret = ((i >= 0) && (i < vCount()));
        if (ret)
        {
            // 判断当前顶点是否有对应的数据元素
            if (m_vertexes[i] != NULL)
            {
                value = *(m_vertexes[i]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this vertex...");
            }
        }

        return ret;
    }

    bool setVertex(int i, const V& value)
    {
        int ret = ((i >= 0) && (i < vCount()));
        if (ret)
        {
            // 考虑异常安全
            V* data = m_vertexes[i];
            // 判断顶点是否有数据元素
            if (data == NULL)
            {
                data = new V();
            }
            if (data != NULL)
            {
                *data         = value;
                m_vertexes[i] = data;
            }
        }

        return ret;
    }

    // 获取顶点i相邻的其它顶点，放进数组中
    SharedPointer<Array<int> > getAdjaent(int i)
    {
        DynamicArray<int>* ret = NULL;

        if ((i >= 0) && (i < vCount()))
        {
            // 计数
            int n = 0;
            for (int j = 0; j < vCount(); j++)
            {
                if (m_edges[i][j] != NULL)
                {
                    n++;
                }
            }
            // 堆空间创建数组对象
            ret = new DynamicArray<int>(n);
            if (ret != NULL)
            {
                for (int j = 0, k = 0; j < vCount(); j++)
                {
                    if (m_edges[i][j] != NULL)
                    {
                        ret->set(k++, j);
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat DynamicArray...");
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
        //        bool ret = ((i >= 0) && i < vCount()) && ((j >= 0) && (j < vCount()));
        //        if (ret)
        //        {
        //            ret = (ret) && (m_edges[i][j] != NULL);
        //        }
        //        return ret;
        return ((i >= 0) && i < vCount()) && ((j >= 0) && (j < vCount())) && (m_edges[i][j] != NULL);
    }

    // 边操作
    E getEdge(int i, int j)
    {    // 得到<i, j>边上的权值
        E ret;
        if (!getEdge(i, j, ret))
        {
            THROW_EXCEPTION(InvalidParameteException, "Index <i,j> is invalid...");
        }
        return ret;
    }
    bool getEdge(int i, int j, E& value)
    {
        bool ret = ((i >= 0) && i < vCount()) && ((j >= 0) && (j < vCount()));
        if (ret)
        {
            // 判断是否存在邻接
            if (m_edges[i][j] != NULL)
                value = *(m_edges[i][j]);
            else
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this edge...");
        }
        return ret;
    }

    bool setEdge(int i, int j, const E& value)
    {
        bool ret = ((i >= 0) && i < vCount()) && ((j >= 0) && (j < vCount()));
        if (ret)
        {
            // 异常安全，用中间变量
            E* ne = m_edges[i][j];

            if (ne == NULL)
            {
                ne = new E();
                if (ne != NULL)
                {
                    *ne           = value;
                    m_edges[i][j] = ne;
                    m_eCount++;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat a E Object...");
                }
            }
            else
            {
                *ne = value;
            }
        }

        return ret;
    }
    bool removeEdge(int i, int j)
    {
        bool ret = ((i >= 0) && i < vCount()) && ((j >= 0) && (j < vCount()));
        if (ret)
        {
            E* toDel      = m_edges[i][j];
            m_edges[i][j] = NULL;    // 邻接矩阵置空
            if (toDel != NULL)
            {    // 权值对象确实存在
                m_eCount--;
                delete toDel;    // 释放权值对象
            }
        }

        return ret;
    }

    // 属性操作
    int vCount()
    {
        return N;
    }

    int eCount()
    {
        return m_eCount;
    }
    int OD(int i)
    {    // 顶点出度
        int ret = 0;
        if ((i >= 0) && i < vCount())
        {
            for (int j = 0; j < vCount(); j++)
            {
                if (m_edges[i][j] != NULL)
                    ret++;
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameteException, "Invalid parameter i, j...");
        }

        return ret;
    }
    int ID(int i)
    {    // 顶点入度
        int ret = 0;
        if ((i >= 0) && i < vCount())
        {
            for (int j = 0; j < vCount(); j++)
            {
                if (m_edges[j][i] != NULL)
                    ret++;
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameteException, "Invalid parameter i, j...");
        }

        return ret;
    }

    ~MatrixGraph()
    {
        for (int i = 0; i < vCount(); i++)
        {
            for (int j = 0; j < vCount(); j++)
                delete m_edges[i][j];
            delete m_vertexes[i];
        }
    }
};

}    // namespace DTLib

#endif    // MATRIXGRAPH_H
