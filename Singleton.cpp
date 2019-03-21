#include <bits/stdc++.h>
using namespace std;
//饿汉单例，即在最开始的时候，静态对象就已经创建完成；
//单例的饿汉实现是线程安全的，因为对象在使用前就已经创建出来了。
class Singleton
{
  public:
    static Singleton *getIns();
  private:
    Singleton(){};
    //把复制构造函数和=操作符也设为私有,防止被复制
    Singleton(const Singleton &){};
    Singleton &operator=(const Singleton &){};
    ~Singleton(){};

    static Singleton *instance;
};
Singleton* Singleton::instance = new Singleton;
Singleton * Singleton::getIns(){
    return instance;
}
////所谓懒汉模式，就是尽可能晚的创建这个对象的实例
// class singleton
// {
// private:
// 	singleton()
// 	{
// 		pthread_mutex_init(&mutex);
// 	}
 
// 	static singleton* p;
// 	static pthread_mutex_t mutex;
// public:
// 	static singleton* initance()
// 	{
// 		if (p == NULL)   //p != NULL,说明对象已经创建出来了，直接返回对象的指针，没必要在加锁解锁浪费时间。
// 		{
// 			pthread_mutex_lock(&mutex);
// 			if (p == NULL)
// 			{
// 				p = new singleton();
// 			}
// 			pthread_mutex_unlock(&mutex);
// 		}
// 		return p;
// 	}
// };
 
// pthread_mutex_t singleton::mutex;
// singleton* singleton::p = NULL;
int main()
{
    Singleton *Singleton1 = Singleton::getIns();
    Singleton *Singleton2 = Singleton::getIns();;
    printf("%x\n",Singleton1);
    printf("%x\n",Singleton2);
    printf("%x\n",Singleton1==Singleton2);
}
//也可以用pthread_once