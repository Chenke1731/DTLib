#ifndef STRING_H
#define STRING_H

#include "Object.h"

namespace DTLib
{

class String : public Object
{
protected:
  char *m_str; // 指向字符串，字符串的具体表现形式就是字符数组
  int m_length;

  void init(const char *s); // 初始化函数

  bool equal(const char *l, const char *r, int len) const;

  static int *make_pmt(const char *p);
  static int kmp(const char *s, const char *p);

public:
  String();
  String(char c);
  String(const char *s);
  String(const String &s);
  int length() const;
  const char *str() const;

  // 判断是否以指定字符串开始或结束
  bool startWith(const char *s) const;
  bool startWith(const String &s) const;
  bool endOf(const char *s) const;
  bool endOf(const String &s) const;

  String &insert(int i, const char *s);
  String &insert(int i, const String &s);

  String &trim();

  // KMP算法应用
  int indexOf(const char *s) const;
  int indexOf(const String &s) const;

  String &remove(int i, int len); // 删除指定下标处，指定长度的子串

  String &remove(const char *s);
  String &remove(const String &s);

  String &replace(const char *s, const char *t);
  String &replace(const String &s, const char *t);
  String &replace(const char *s, const String &t);
  String &replace(const String &s, const String &t);

  String sub(int i, int len) const;

  // 比较操作符重载函数
  bool operator==(const String &s) const;
  bool operator==(const char *s) const; // 针对char*

  bool operator!=(const String &s) const;
  bool operator!=(const char *s) const; // 针对char*

  bool operator>(const String &s) const;
  bool operator>(const char *s) const; // 针对char*

  bool operator<(const String &s) const;
  bool operator<(const char *s) const; // 针对char*

  bool operator>=(const String &s) const;
  bool operator>=(const char *s) const; // 针对char*

  bool operator<=(const String &s) const;
  bool operator<=(const char *s) const; // 针对char*

  // 加法操作符重载函数
  String operator+(const String &s);
  String operator+(const char *s);
  String operator+=(const String &s);
  String operator+=(const char *s);

  // 减法操作符重载函数
  String operator-(const String &s);
  String operator-(const char *s);
  String operator-=(const String &s);
  String operator-=(const char *s);

  // 赋值操作符重载函数 3种
  String operator=(const String &s);
  String operator=(const char *s);
  String operator=(char c);

  // 数组操作符重载
  char &operator[](int i);      // 非const版本，给非const对象使用
  char operator[](int i) const; // const修饰的常对象使用

  ~String();
};

} // namespace DTLib

#endif // !STRING_H
