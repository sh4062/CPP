#include<boost/function.hpp>
#include<boost/bind.hpp>
#include<iostream>
typedef boost::function<void(void)> Func;

int test(int num)
{
   std::cout<<"In test"<<num<<std::endl;    
}

int main()
{
  Func f(boost::bind(test,6));
  f();
}