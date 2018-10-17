#ifndef LIST_H
#define LIST_H

#include "Object.h"

namespace DTLib
{
template <typename T>
class List : public Object
{
    // 对于容器类型的类，可以考虑禁用拷贝构造和赋值操作
protected:
    List (const List&);
    List& operator= (const List&);

public:
    List () {}
    virtual bool insert (const T& e)        = 0;
    virtual bool insert (int i, const T& e) = 0;
    virtual bool remove (int i)             = 0;
    virtual bool set (int i, const T& e)    = 0;
    virtual bool get (int i, T& e) const    = 0;
    virtual int  find (const T& e) const    = 0;
    virtual int  length () const            = 0;
    virtual void clear ()                   = 0;
};

}    // namespace DTLib

#endif    // !LIST_H
