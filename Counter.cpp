#include <boost/core/noncopyable.hpp>
#include <iostream>
#include "MutexLock.h"
using namespace std;
//线程安全：不要在构造时候泄漏this指针
namespace mx{
class Counter : boost::noncopyable
{
    //
  public:
    Counter() : value_(0){};
    int64_t value() const;
    int64_t getAndIncrease();

  private:
    int64_t value_;
    //    计数器被mutable修饰，那么它就可以突破const的限制，在被const修饰的函数里面也能被修改。

    mutable mx::MutexLock mutex_;
};
}

int64_t mx::Counter::value()const{
  return value_;
}
int64_t mx::Counter::getAndIncrease(){
  mx::MutexLockGuard lock(mutex_);
  int64_t ret = value_++;
  return ret;
}
int main()
{
    mx::Counter a;
    a.getAndIncrease();
    a.getAndIncrease();
    a.getAndIncrease();
    cout<<a.value();
    
}
