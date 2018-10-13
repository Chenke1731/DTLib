#ifndef SORT_H
#define SORT_H

#include "Object.h"

namespace DTLib
{
class Sort : public Object
{
  private:
    // 意味着Sort不能产生对象
    Sort();
    Sort(const Sort &);
    Sort &operator=(const Sort &);

    template <typename T>
    static void Swap(T &a, T &b)
    {
        T c(a);
        a = b;
        b = c;
    }

    // 真正的归并操作
    template <typename T>
    static void Merge(T src[], T helper[], int begin, int mid, int end, bool minTomax = true)
    {
        int i = begin;   // 左路起始位置
        int j = mid + 1; // 右路起始位置
        int k = begin;   // 辅助空间起始位置

        while ((i <= mid) && (j <= end))
        {
            if(src[i] < src[j])
            {// 左路小
                helper[k++] = src[i++];
            }
            else
            {// 右路小
                helper[k++] = src[j++];
            }
        }

        while(i <=mid )
        {
            helper[k++] = src[i++];
        }
        while(j <= end)
        {
            helper[k++] = src[j++];
        }
        // 辅助空间就是最后的结果
        for(i = begin; i <= end; i++)
        {
            src[i] = helper[i];
        }
    }

    template <typename T>
    static void Merge(T src[], T helper[], int begin, int end, bool minTomax = true)
    {
        if (begin == end)
        { // 只有一个数据元素
            return;
        }
        else
        { // 划分后，进行二路归并
            int mid = (begin + end) / 2;
            Merge(src, helper, begin, mid, minTomax);
            Merge(src, helper, mid + 1, end, minTomax);
            // 合并
            Merge(src, helper, begin, mid, end, minTomax);
        }
    }

  public:
    // 选择排序
    template <typename T>
    static void Select(T array[], int len, bool minTomax = true)
    {
        for (int i = 0; i < len; i++)
        {
            int min = i;
            for (int j = i + 1; j < len; j++)
            { // 找到当前的最小元素
                if (minTomax ? (array[min] > array[j]) : (array[min] < array[j]))
                {
                    min = j;
                }
            }
            // 判断是否需要进行交换操作
            if (min != i)
            {
                Swap(array[i], array[min]); // 最小元素放在0的位置
            }
        }
    }

    // 插入排序
    template <typename T>
    static void Insert(T array[], int len, bool minTomax = true)
    {
        // 第一个数据元素没必要进行插入操作
        for (int i = 1; i < len; i++)
        {
            int k = i;      // 用来保存可能插入的位置
            T e = array[i]; // 将待插入的元素拿出来
            /* for (int j = i - 1; j >= 0; j--)
            {
                if(array[j] > e)
                {
                    array[j + 1] = array[j];
                    k = j;
                }
                else
                {
                    break;
                }
            } */
            for (int j = i - 1; (j >= 0) && (minTomax ? (array[j] > e) : (array[j] < e)); j--)
            {
                array[j + 1] = array[j];
                k = j;
            }

            if (k != i)
            {
                array[k] = e;
            }
        }
    }

    // 冒泡排序
    template <typename T>
    static void Bubble(T array[], int len, bool minTomax = true)
    {
        bool exchange = true;
        for (int i = 0; (i < len) && exchange; i++)
        {
            exchange = false;
            for (int j = len - 1; j > i; j--)
            {
                if (minTomax ? (array[j] < array[j - 1]) : (array[j] > array[j - 1]))
                {
                    Swap(array[j], array[j - 1]);
                    exchange = true;
                }
            }
        }
    }

    // 希尔排序
    /*     template <typename T>
    static void Shell(T array[], int len, bool minTomax = true)
    {
        int d = len;

        do
        {
            d = d / 3 + 1;
            for (int i = d; i < len; i ++)
            {
                int k = i;      // 用来保存可能插入的位置
                T e = array[i]; // 将待插入的元素取出
                for (int j = i - d; (j >= 0) && (minTomax ? (array[j] > e) : (array[j] < e)); j -= d)
                {
                    array[j + d] = array[j];
                    k = j;
                }
                if (k != i)
                {
                    array[k] = e;
                }
            }
        } while (d > 1);
    } */

    template <typename T>
    static void Merge(T array[], int len, bool minTomax = true)
    {
        T *helper = new T[len];
        if (helper != NULL)
        {
            Merge(array, helper, 0, len-1, minTomax);
        }
    }
};

} // namespace DTLib

#endif // !SORT_H
