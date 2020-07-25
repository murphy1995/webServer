#include <stdio.h>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <unistd.h>
#include <sys/types.h>
#include "webServer/base/Thread.h"
#include "webServer/base/CountDownLatch.h"
#include "webServer/base/BlockingQueue.h"
#include "webServer/base/Timestamp.h"

using namespace webServer;
using namespace std;

class BlockingQueue_test
{
public:
	BlockingQueue_test(int numthread) : latch(numthread), numThread(numthread){
		for(int i = 0; i < numthread; i++) {
			string threadName = "thread" + to_string(i);
			threads.push_back(new Thread(bind(&BlockingQueue_test::threadFunc, this), threadName));
		}
		for_each(threads.begin(), threads.end(), bind(&Thread::start, std::placeholders::_1));
	}
	
	void run() {
		printf("CurrentThread is : %d , wait threads ready\n", CurrentThread::tid());
		latch.wait();
		printf("CurrentThread is : %d , main thread begin...\n", CurrentThread::tid());
		for (int i = 0; i < 10000; ++i)
		{
			queue_.put(Timestamp::now());
			usleep(1000);
			//printf("CurrentThread is : %d , put value is : %d; size is : %zu\n",
			// ::getpid(), i, queue_.size());
		}
	}

	void joinAll() {
		for (int i = 0; i < numThread; ++i)
		{
			queue_.put(Timestamp::invalid());
		}
		for_each(threads.begin(), threads.end(), bind(&Thread::join, std::placeholders::_1));
	}

private:
	void threadFunc() {
		printf("CurrentThread is : %d , thread begin...\n", CurrentThread::tid());
		latch.countDown();
		bool running = true;
		std::map<int, int> timeDiffCount;
		while(running) {
			Timestamp currentTime = Timestamp::now();
			Timestamp t = queue_.take();

			if(t.valid()) {
				int timediff = static_cast<int>(timeDifference(currentTime, t));
				//printf("CurrentThread is : %d , take time is : %s; time difference is : %d\n", 
				//CurrentThread::tid(), t.toString().c_str(), timediff);
				timeDiffCount[timediff]++;
			}
			
			running = t.valid();
		}
		printf("CurrentThread is : %d , quit task\n", CurrentThread::tid());
		for(auto it = timeDiffCount.begin(); it != timeDiffCount.end(); it++) {
			printf("CurrentThread is : %d, timeDiff is : %d; count is : % d\n", 
				CurrentThread::tid(), it->first, it->second);
		}
	}

	CountDownLatch latch;
	std::vector<webServer::Thread*> threads;
	BlockingQueue<Timestamp> queue_;
	int numThread;
};

int main(int argc, char const *argv[])
{
	printf("current thread id = %d, pid : %d, testing begin\n", CurrentThread::tid(), ::getpid());	

	const int THREAD_NUM = 5;
	BlockingQueue_test test(THREAD_NUM);

	//sleep(3);
	test.run();
	test.joinAll();

	printf("thread created %d\n", Thread::numCreated());	

	return 0;
}