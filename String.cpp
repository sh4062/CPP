#include <iostream>
#include<string.h>
using namespace std;
class String
{
  public:
    String(const char *str = NULL); //default
    String(const String &str);      //copy
    ~String();                      //

    String operator+(const String &str) const;
    String& operator=(const String &str);
    String& operator+=(const String &str);
    bool operator==(const String &str) const;
    char &operator[](int n) const;

    int size() const;
    const char *c_str() const;

    friend istream &operator>>(istream &is, String &str);
    friend ostream &operator<<(ostream &os, String &str);

  private:
    char *data;
    int length;
};

String::String(const char *str)
{
    if (!str)
    {
        length = 0;
        data = new char[1];
        *data = '\0';
    }
    else
    {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }
}
//拷贝构造函数需要进行深复制。
String::String(const String &str)//拷贝构造函数
{
	length = str.size();
	data = new char[length + 1];
	strcpy(data, str.c_str());
}
//析构函数需要进行内存的释放及长度的归零。

String::~String()//析构函数
{
	delete []data;
	length = 0;
}
//重载字符串连接运算，这个运算会返回一个新的字符串。

String String::operator+(const String &str) const//重载+
{
	String newString;
	newString.length = length + str.size();
	newString.data = new char[newString.length + 1];
	strcpy(newString.data, data);
	strcat(newString.data, str.data);
	return newString;
}
//重载字符串赋值运算，这个运算会改变原有字符串的值，为了避免内存泄露，这里释放了原先申请的内存再重新申请一块适当大小的内存存放新的字符串。

String& String::operator = (const String &str)//重载=
{
	if (this == &str)	return *this;

	delete []data;
	length = str.length;
	data = new char[length + 1];
	strcpy(data, str.c_str());
	return *this;
}
//重载字符串+=操作，总体上是以上两个操作的结合。

String& String::operator+=(const String &str)//重载+=
{
	length += str.length;
	char *newData = new char[length + 1];
	strcpy(newData, data);
	strcat(newData, str.data);
	delete []data;
	data = newData;
	return *this;
}
//重载相等关系运算，这里定义为内联函数加快运行速度。

inline bool String::operator==(const String &str) const//重载==
{
	if (length != str.length)	return false;
	return strcmp(data, str.data) ? false : true;
}
//重载字符串索引运算符，进行了一个简单的错误处理，当长度太大时自动读取最后一个字符。

inline char& String::operator[](int n) const//重载[]
{
	if (n >= length) return data[length-1]; //错误处理
	else return data[n];
}
//重载两个读取私有成员的函数，分别读取长度和C字符串。

inline int String::size() const//获取长度
{
	return length;
}
//重载输入运算符，先申请一块足够大的内存用来存放输入字符串，再进行新字符串的生成。这是一个比较简单朴素的实现，网上很多直接is>>str.data的方法是错误的，因为不能确定str.data的大小和即将输入的字符串的大小关系。

istream& operator>>(istream &is, String &str)//输入
{
	char tem[1000];  //简单的申请一块内存
	is >> tem;
	str.length = strlen(tem);
	str.data = new char[str.length + 1];
	strcpy(str.data, tem);
	return is;
}
//重载输出运算符，只需简单地输出字符串的内容即可。注意为了实现形如cout<<a<<b的连续输出，这里需要返回输出流。上面的输入也是类似。

ostream& operator<<(ostream &os, String &str)//输出
{
	os << str.data;
	return os;
}
inline const char* String::c_str() const//获取C字符串
{
	return data;
}