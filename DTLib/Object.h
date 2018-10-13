#ifndef OBJECT_H
#define OBJECT_H
#include <cstdlib>


namespace DTLib
{


class Object
{

public:
    void *operator new(size_t size) throw();
    void operator delete(void *p);
    void *operator new[](size_t size) throw();
    void operator delete[](void *p);

    // 重载==操作符，使编译通过，具体使用时在具体的类中重载操作符
    bool operator==(const Object &obj);
    bool operator!=(const Object &obj);

    virtual ~Object() = 0;
};


}



#endif // !OBJECT_H


