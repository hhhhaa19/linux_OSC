#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#define NUMBER_OF_PROCESSES 4
long int getDifferenceInMilliSeconds(struct timeval start, struct
		timeval end) {
	int seconds = end.tv_sec - start.tv_sec;
	int useconds = end.tv_usec - start.tv_usec;
	int mtime = (seconds * 1000 + useconds / 1000.0);
	return mtime;
}
long int getDifferenceInMicroSeconds(struct timeval start, struct
timeval end) {
int seconds = end.tv_sec - start.tv_sec;
int useconds = end.tv_usec - start.tv_usec;
int mtime = (seconds * 1000000 + useconds);
return mtime;
}


int main() {
	struct timeval startTime;
	gettimeofday(&startTime,NULL);
	int i, status;
	pid_t pid[NUMBER_OF_PROCESSES];
	for (int i = 0 ;i< NUMBER_OF_PROCESSES;i++){
		struct timeval currentTime;
		printf("Hello from the parent process with PID %d\n", getpid());
        	pid[i] = fork();
		if(pid[i] < 0) {
               		printf("fork error\n");
        	} else if(pid[i] == 0) {
                	gettimeofday(&currentTime,NULL);
                	printf("Hello from the child process with PID %d at time %ld\n", getpid(),getDifferenceInMicroSeconds(startTime,currentTime));
                	return 0;
        	}
	}
	for (int i = 0;i<NUMBER_OF_PROCESSES;i++){
		waitpid(pid[i], &status, WUNTRACED);
	}
	printf("Child process has finished\n");
	return 0;
}

