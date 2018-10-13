#include <cstring>
#include <cstdlib>
#include "DTString.h"
#include "Exception.h"

using namespace std;        

namespace DTLib
{

// 建立指定字符串的部分匹配表PMT
int *String::make_pmt(const char *p)
{
    int len = strlen(p);

    // 返回值指向部分匹配表的指针
    // 部分匹配表是在堆空间中创建
    int *ret = static_cast<int *>(malloc(sizeof(int) * len));
    if (ret != NULL)
    {
        // longest length 前缀和后缀交集元素的最大长度
        int ll = 0;
        ret[0] = 0; // 第0个，即长度为1的， 为0
        for (int i = 1; i < len; i++)
        {
            while ((ll > 0) && (p[ll] != p[i]))
            {
                // 匹配不成功
                // 需要从之前推导出来的部分匹配值中挑一个可用值出来
                ll = ret[ll - 1];
                // 接着尝试扩展，所以不用if用while
                // 找到ll为0， 且比对还是不成功，ll 就为0了
            }
            // 判断假设是否成立
            if (p[ll] == p[i]) // 意味着扩展，在前一个ll的值的基础上进行扩展
            {
                ll++;
            }
            ret[i] = ll; // 在部分匹配表中存储部分匹配值
        }
    }

    return ret;
}

int String::kmp(const char *s, const char *p)
{
    int ret = -1;
    int sl = strlen(s);
    int pl = strlen(p);
    int *pmt = make_pmt(p);

    if ((pmt != NULL) && (pl > 0) && (pl <= sl))
    {

        for (int i = 0, j = 0; i < sl; i++)
        {
            while ((j > 0) && (s[i] != p[j]))
            { // 匹配不成功，查表
                j = pmt[j - 1];
            }

            if (s[i] == p[j])
            {
                j++;
            }

            if (j == pl)
            {
                // i的值停在最后一个匹配的地方，反推开始匹配的位置
                ret = i + 1 - pl;
                break;
            }
        }
    }
    free(pmt);

    return ret;
}

// 使用参数s来具体产生当前字符串对象中的数据
void String::init(const char *s) // 初始化函数
{
    m_str = strdup(s); // 将s复制一份出来
    if (m_str)
    { // 复制成功
        m_length = strlen(m_str);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat String Object...");
    }
}
String::String()
{
    init("");
}

String::String(const char c)
{
    // 字符数组模拟字符串
    // 构造字符串
    char s[] = {c, '\0'};
    init(s);
}
String::String(const char *s)
{
    // 防止s是空指针，空指针转换成空字符串
    init(s ? s : "");
}
String::String(const String &s)
{
    init(s.m_str);
}

int String::length() const
{
    return m_length;
}
const char *String::str() const
{
    return m_str; // 直接返回成员指针
}

bool String::equal(const char *l, const char *r, int len) const
{
    bool ret = true;
    for (int i = 0; i < len && ret; i++) // 但凡有一个字符比对不成功，for循环就直接结束，返回的就是false
    {
        ret = ret && (l[i] == r[i]);
    }
    return ret;
}

// 判断是否以指定字符串开始或结束
bool String::startWith(const char *s) const
{
    bool ret = (s != NULL);
    if (ret)
    {
        int len = strlen(s);
        ret = (len < m_length) && equal(m_str, s, len);
    }

    return ret;
}
bool String::startWith(const String &s) const
{
    return startWith(s.m_str);
}

bool String::endOf(const char *s) const // 定位到最后n个字符的位置
{
    bool ret = (s != NULL);
    if (ret)
    {
        int len = strlen(s);
        // 确定起始位置
        char *str = m_str + (m_length - len); // 得到起始位置后，用m_str做指针运算，使str指向起始位置
        ret = (len < m_length) && equal(str, s, len);
    }

    return ret;
}
bool String::endOf(const String &s) const
{
    return endOf(s.m_str);
}

// 指定位置插入字符串
String &String::insert(int i, const char *s)
{
    if ((i >= 0) && (i <= m_length))
    {
        if ((s != NULL) && (s[0] != '\0'))
        {
            // 堆空间中申请内存，需要知道长度
            int len = strlen(s);
            char *str = reinterpret_cast<char *>(malloc(m_length + len + 1));
            if (str != NULL)
            { // 插入
                strncpy(str, m_str, i);
                strncpy(str + i, s, len);
                strncpy(str + i + len, m_str + i, m_length - i);
                str[m_length + len] = '\0';

                free(m_str);
                m_str = str;
                m_length = m_length + len;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to add String values...");
            }
        }
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
    }
    return *this;
}
String &String::insert(int i, const String &s)
{
    return insert(i, s.m_str);
}

String &String::trim()
{
    int b = 0;
    int e = m_length + 1;
    while (m_str[b] == ' ')
        b++;
    while (m_str[e] == ' ')
        e--;
    if (b == 0)
    {
        m_str[e + 1] = '\0';
        m_length = e + 1;
    }
    else
    {
        for (int i = 0, j = b; j <= e; i++, j++)
        {
            m_str[i] = m_str[j];
        }
        m_str[e - b + 1] = '\0';
        m_length = e - b + 1;
    }
    return *this;
}

int String::indexOf(const char *s) const
{
    return kmp(m_str, s ? s : "");
}
int String::indexOf(const String &s) const
{
    return kmp(m_str, s.m_str);
}

/* String &String::remove(int i, int len)
{ // 和insert类似，返回引用本身

    if ((i >= 0) && (i < m_length))
    {
        int n = i;
        int m = i + len;
        while ((n < m) && (m < m_length))
        {                            // 删除的子串不能在字符串范围外
            m_str[n++] = m_str[m++]; // 直接进行移动
        }
        m_str[n] = '\0';
        m_length = n;
    }

    return *this;
} */

String& String::remove(int i, int len)
{

    if((i >= 0) && ( i < m_length))
    {
         int n = i;
         int m = i + len;
         while(m < m_length)
             m_str[n++] = m_str[m++];
         m_str[n] = '\0';
         m_length = n;
    }

    return *this;
}


String &String::remove(const char *s)
{
    return remove(indexOf(s), s ? strlen(s) : 0);
}
String &String::remove(const String &s)
{
    return remove(indexOf(s), s.length());
}

String &String::replace(const char *s, const char *t)
{
    /*
        1、i=indexOf("bc")
        2、remove("bc")
        3、insert(i, "xyz")
      */
    int index = indexOf(s);
    if (index > 0)
    {
        remove(s);
        insert(index, t);
    }
    return *this;
}

String &String::replace(const String &s, const char *t)
{
    return replace(s.m_str, t);
}
String &String::replace(const char *s, const String &t)
{
    return replace(s, t.m_str);
}
String &String::replace(const String &s, const String &t)
{
    return replace(s.m_str, t.m_str);
}

// 以i为起点提取长度为len的子串
String String::sub(int i, int len) const
{
    String ret;
    if ((i >= 0) && (i < m_length))
    {
        if(len < 0)
            len = 0;
        if((len+ i)> m_length)
            len = m_length - i;

        char *str = reinterpret_cast<char *>(malloc(sizeof(len + 1)));
        strncpy(str, m_str+i, len);
        str[len] = '\0';
        ret = str;
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
    }

    return ret;
}

// 操作符重载
bool String::operator==(const String &s) const
{
    return (strcmp(m_str, s.m_str) == 0);
}
bool String::operator==(const char *s) const // 针对char*
{
    return (strcmp(m_str, s ? s : "") == 0);
}

bool String::operator!=(const String &s) const
{
    return !(*this == s);
}
bool String::operator!=(const char *s) const // 针对char*
{
    return !(*this == s);
}

bool String::operator>(const String &s) const
{
    return (strcmp(m_str, s.m_str) > 0);
}
bool String::operator>(const char *s) const // 针对char*
{
    return (strcmp(m_str, s ? s : "") > 0);
}

bool String::operator<(const String &s) const
{
    return (strcmp(m_str, s.m_str) < 0);
}
bool String::operator<(const char *s) const // 针对char*
{
    return (strcmp(m_str, s ? s : "") < 0);
}

bool String::operator>=(const String &s) const
{
    return (strcmp(m_str, s.m_str) >= 0);
}
bool String::operator>=(const char *s) const // 针对char*
{
    return (strcmp(m_str, s ? s : "") >= 0);
}

bool String::operator<=(const String &s) const
{
    return (strcmp(m_str, s.m_str) <= 0);
}
bool String::operator<=(const char *s) const // 针对char*
{
    return (strcmp(m_str, s ? s : "") <= 0);
}

// 加法
String String::operator+(const String &s)
{
    return (*this + s.m_str);
}

String String::operator+(const char *s)
{
    String ret;
    int len = m_length + strlen(s ? s : "");

    char *str = reinterpret_cast<char *>(malloc(len + 1));
    if (str)
    {
        // 调用字符串相关函数
        strcpy(str, m_str);
        strcat(str, s ? s : "");
        // str保存拼接后的结果
        free(ret.m_str);
        ret.m_str = str;
        ret.m_length = len;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to add String values...");
    }

    return ret;
}

String String::operator+=(const String &s)
{
    return (*this = *this + s.m_str);
}

String String::operator+=(const char *s)
{
    return (*this = *this + s);
}

// 减法
String String::operator-(const String &s)
{
    // 调用构造函数产生临时对象，再调用remove函数，对临时对象进行操作，而不会影响原来的字符串
    // 将临时对象的操作结果返回
    return String(*this).remove(s);
}
String String::operator-(const char *s)
{
    return String(*this).remove(s);
}

String String::operator-=(const String &s)
{
    // 字符串自身被改变
    return remove(s);
}
String String::operator-=(const char *s)
{
    return remove(s);
}

// 重载赋值操作符
String String::operator=(const String &s)
{
    return (*this = s.m_str);
}

String String::operator=(const char *s)
{
    if (m_str != s)
    {
        char *str = strdup(s ? s : "");
        if (str)
        {
            free(m_str);
            m_str = str;
            m_length = strlen(str);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to assign new String value...");
        }
    }
    return *this;
}

String String::operator=(char c)
{
    char s[] = {c, '\0'};
    return (*this = s);
}

// 数组操作符重载
char &String::operator[](int i)
{
    // 参数判断
    if ((i >= 0) && (i < m_length))
    {
        // 返回相应位置处的字符
        // 给非const对象用，引用意味着可以被赋值
        return m_str[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
    }
}
char String::operator[](int i) const
{
    return (const_cast<String &>(*this)[i]); // 清除const属性， 使用非const的[]
}

String::~String()
{
    free(m_str);
}

} // namespace DTLib
