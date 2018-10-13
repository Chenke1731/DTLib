#ifndef ARRAY_H
#define ARRAY_H

#include "Object.h"
#include "Exception.h"

namespace DTLib
{


template<typename T>
class Array : public Object
{
protected:
  T *m_array;

public:
  virtual bool set(int i, const T &e)
  {
      bool ret = ((i >= 0) && (i < length()));
      if(ret)
      {
          m_array[i] = e;
      }
      return ret;
  }
  virtual bool get(int i, T &e)
  {
      bool ret = ((i >= 0) && (i < length()));
      if(ret)
      {
          e = m_array[i];
      }
      return ret;
  }
  virtual int length() const = 0;

  // 数组访问操作符重载
  T &operator[](int i)
  {
      if((i >= 0) && (i < length()))
      {
          return m_array[i];
      }
      else
      {
          THROW_EXCEPTION(NoEnoughMemoryException, "Parameter i is invalid...");
      }
  }
  T operator[](int i) const
  {
      // *this的类型？ (*this)[i]是什么鬼
      return (const_cast<Array<T> &>(*this)[i]);
  }
};

}



#endif // !ARRAY_H
