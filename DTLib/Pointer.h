#ifndef POINTER_H
#define POINTER_H

#include <cstdlib>

#include "Object.h"

namespace DTLib
{
template <typename T>
class Pointer
{
protected:
    T* m_pointer;

public:
    Pointer (T* p = NULL)
    {
        m_pointer = p;
    }

    T* operator-> ()
    {
        return m_pointer;
    }

    T& operator* ()
    {
        return *m_pointer;
    }

    bool isNull ()
    {
        return (m_pointer == NULL);
    }

    T* get () const
    {
        return m_pointer;
    }
};

}    // namespace DTLib

#endif    // !POINTER_H
