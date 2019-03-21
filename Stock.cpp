#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <memory>
#include <string>
#include <iostream>
#include "MutexLock.h"
using namespace std;
using namespace mx;
class Stock
{
  public:
    string key();
};
class StockFactory : enable_shared_from_this<StockFactory>,
                     boost::noncopyable
{
  public:
    shared_ptr<Stock> get(const string &key)
    {
        shared_ptr<Stock> pStock;
        MutexLockGuard lock(mutex_);
        weak_ptr<Stock>& wkstock = stock_[key];
        pStock = wkstock.lock();
        if(!pStock){
            pStock.reset(new Stock(),boost::bind(&StockFactory::weakDeleteCallback, weak_ptr<StockFactory>(shared_from_this()),_1));
        }
        return pStock;
    }

  private:
    void removeStock(Stock *stock)
    {
        if (stock)
        {
            MutexLockGuard lock(mutex_);
            stock_.erase(stock->key());
        }
    }
    //对象与对象之间的成员变量是相互独立的.要想共用数据,则需要使用静态成员或静态方法
    //普通成员函数和静态成员函数的区别是:普通成员函数在参数传递时编译器会隐藏地传递一个this指针.通过this指针来确定调用类产生的哪个对象;
    //但是静态成员函数没有this指针,不知道应该访问哪个对象中的数据,所以在程序中不可以用静态成员函数访问类中的普通变量.
    static void weakDeleteCallback(const weak_ptr<StockFactory> &wkFactory, Stock *stock)
    {
        shared_ptr<StockFactory> fac(wkFactory.lock());
        if (fac)
        {
            fac->removeStock(stock);
        }
        delete stock;
    }

  private:
    mutable MutexLock mutex_;
    std::map<string, weak_ptr<Stock>> stock_;
};