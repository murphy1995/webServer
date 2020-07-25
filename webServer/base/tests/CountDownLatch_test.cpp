#include <stdio.h>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include "webServer/base/Thread.h"
#include "webServer/base/CountDownLatch.h"

using namespace webServer;
using namespace std;

class CountDownLatch_test
{
public:
	CountDownLatch_test(int numthread) : latch(1){
		for(int i = 0; i < numthread; i++) {
			string threadName = "thread" + to_string(i);
			threads.push_back(new Thread(bind(&CountDownLatch_test::threadFunc, this), threadName));
		}
		for_each(threads.begin(), threads.end(), bind(&Thread::start, std::placeholders::_1));
	}
	
	void run() {
		latch.countDown();
	}

	void joinAll() {
		for_each(threads.begin(), threads.end(), bind(&Thread::join, std::placeholders::_1));
	}

private:
	void threadFunc() {
		latch.wait();

		printf("current thread id = %d, name : %s; begin to work...\n", CurrentThread::tid(), CurrentThread::name());
		sleep(2);
		printf("current thread id = %d, name : %s; end work\n", CurrentThread::tid(), CurrentThread::name());
	}

	CountDownLatch latch;
	std::vector<webServer::Thread*> threads;	
};

int main(int argc, char const *argv[])
{
	printf("current thread id = %d, pid : %d\n", CurrentThread::tid(), ::getpid());

	CountDownLatch_test test(3);

	sleep(3);

	printf("current thread id = %d, pid : %d, testing begin\n", CurrentThread::tid(), ::getpid());	

	test.run();
	test.joinAll();

	printf("thread created %d\n", Thread::numCreated());	

	return 0;
}