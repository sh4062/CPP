#include <bits/stdc++.h>
using namespace std;
class A{
public:
    void setA(int);
private:
    int a;
};
class B{
public:
    void setB(int);
private:
    int b;
};
class C:public A, private B{
public:
    void setC(int, int, int);
private:
    int c;
};
void A::setA(int x){
    a = x;
}
void B::setB(int x){
    b = x;
}
void C::setC(int x, int y, int z){
    setA(x);
    setB(y);
    c = z;
}
// int main(int argc, const char * argv[]) {
//     C obj;
//     obj.setA(5); // A
//     obj.setB(6); // B
//     obj.setC(6, 7, 9); // C
//     return 0;
// }
// int main(){
//     istringstream istr("5 1.2");

// int a;

// float b;

// istr >> a >> b;
// cout<<a<<b;
// }
  
// int main()
// {
//    int a[10] = {1,2,3,4,5,6,7,8,9,0}, *pa = a;
//    cout<<a[1]<<pa[1];

// }

#include <iostream>
using namespace std;

class Base0 {   
public:
    Base0(int var) : var0(var) { }
    int var0;
    void fun0() { cout << "Member of Base0" << endl; }
};
class Base1: virtual public Base0 {
public: 
    Base1(int var) : Base0(var) { }
    int var1;
};
class Base2: virtual public Base0 { 
public:
    Base2(int var) : Base0(var) { }
    int var2;
};

class Derived: public Base1, public Base2 {
public:
    Derived(int var):Base0(var-1),Base1(var),Base2(var+1) 
   { }
    int var;
    void fun() 
   { cout << "Member of Derived" << endl; }
};

int main() {    //程序主函数
    Derived d(1);
    cout<<d.var0; //直接访问虚基类的数据成员
    d.fun0();   //直接访问虚基类的函数成员
    return 0;
}