#include <boost/core/noncopyable.hpp>
#include <pthread.h> 

namespace mx{
class MutexLock
: boost::noncopyable
{
public:
	MutexLock()
	{	pthread_mutex_init(&_mutex, NULL);	}

	~MutexLock()
	{	pthread_mutex_destroy(&_mutex);	}

	void lock()
	{	pthread_mutex_lock(&_mutex);}

	void unlock()
	{	pthread_mutex_unlock(&_mutex);}

	pthread_mutex_t * getMutexLockPtr()
	{	return &_mutex;	}

private:
	pthread_mutex_t _mutex;
};
//RAII 资源获取就是初始化 它保证在任何情况下，使用对象时先构造对象，最后析构对象。
class MutexLockGuard
{
public:
	explicit MutexLockGuard(MutexLock & mutex)
	: _mutex(mutex)
	{	_mutex.lock();	}

	~MutexLockGuard()
	{	_mutex.unlock();	}

private:
	MutexLock & _mutex;
};
}