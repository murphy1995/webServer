#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

void prepare() {
	printf("pid = %d prepare\n", static_cast<int> (getpid()));
}

void parent() {
	printf("pid = %d parent\n", static_cast<int> (getpid()));
}

void child() {
	printf("pid = %d child\n", static_cast<int> (getpid()));
}

int main(int argc, char const *argv[])
{
	printf("pid = %d Entering main thread\n", static_cast<int> (getpid()));

	pthread_atfork(prepare, parent, child);

	fork();

	printf("pid = %d Exiting main thread\n", static_cast<int> (getpid()));

	return 0;
}