#include "Object.h"
#include <cstdlib>



namespace DTLib
{

    // new的重载实现，针对单个对象
    // throw是异常规格说明，作用：表示当前的这个重载函数是不会抛出任何异常的
    // 申请堆空间失败就返回空指针
    void* Object::operator new(size_t size) throw()
    {
        return malloc(size);
    }
    void  Object::operator delete(void *p)
    {
        free(p);
    }
    void* Object::operator new[](size_t size) throw()
    {
        return malloc(size);
    }
    void  Object::operator delete[](void *p)
    {
        free(p);
    }

     bool Object::operator==(const Object &obj)
     {// 默认的实现方式比较地址就行
         return (this == &obj);
     }
     bool Object::operator!=(const Object &obj)
     {
         return (this != &obj);
     }


    Object::~Object()
    {
        // 析构函数的纯虚版本也需要提供函数体
    }

    
} // DTLib


