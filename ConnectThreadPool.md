## ConnectThreadPool ##

ConnectThreadPool用来创建链接线程池。当NetInterface收到新的链接请求时将新的链接分配到某个ConnectThread中去，这个过程实际上是通过ConnectThreadPool来完成的。ConnectThreadPool通过继承ConnectAccepter类获得分配链接的能力。

```
class ConnectThreadPool:public ThreadPool<SocketHandle>, public ConnectAccepter
{
public:
	//实现ConnectAccepter:接收一个新的连接请求
	bool accept(SocketHandle trans_fd);
public:
	ConnectThreadPool(unsigned int thread_num):ThreadPool<SocketHandle>(thread_num){}
};

inline
bool ConnectThreadPool::accept(SocketHandle trans_fd)
{
	SLOG_DEBUG("connect thread pool accept fd=%d", trans_fd);
	return add_task(trans_fd);
}
```
> 通过实现accept方法，将新的链接添加到线程池中。当线程池收到一个任务（新链接）后，会将该任务分配到某个线程，然后通过notify\_add\_task通知线程添加一个新的任务；线程收到通知后，从等待队列中取出任务进行相应的处理。