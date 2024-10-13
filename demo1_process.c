#include <stdio.h>
#include <unistd.h>
#define NUMBER_OF_PROCESSES 5

int main() {
	pid_t pid[NUMBER_OF_PROCESSES];
	pid_t pid1= fork();
	if (pid1 == 0){
		execl("/bin/ps", "ps", "l", (char *)NULL);
    		perror("Failed to exec ps");
	}
	for (int i = 0; i < NUMBER_OF_PROCESSES; i++)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{	sleep(1);
			printf("hello from the child %d with pid %d\n", i,getpid());
			return 0;
		}
	}
	return 0;
}
