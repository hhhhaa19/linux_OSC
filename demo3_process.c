#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#define NUMBER_OF_PROCESSES 4
#define MAX_EXPERIMENT_DURATION 1000 // in milliseconds

long getDifferenceInMicroSeconds(struct timeval start, struct timeval end) {
    long seconds = end.tv_sec - start.tv_sec;
    long useconds = end.tv_usec - start.tv_usec;
    return (seconds * 1000000 + useconds);
}

void runChildProcess(int index, struct timeval baseTime) {
    while(1) {
        struct timeval currentTime;
        gettimeofday(&currentTime, NULL);
        long elapsedMicroseconds = getDifferenceInMicroSeconds(baseTime, currentTime);

        if (elapsedMicroseconds / 1000 > MAX_EXPERIMENT_DURATION) {
            break;
        }

        printf("%ld, %d\n", elapsedMicroseconds, index);
    }
}

int main() {
    struct timeval startTime;
    gettimeofday(&startTime, NULL);
    int i, status;
    pid_t pid[NUMBER_OF_PROCESSES];

    for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
        pid[i] = fork();

        if (pid[i] < 0) {
            printf("Fork error\n");
        } else if (pid[i] == 0) {
            runChildProcess(i, startTime);
            return 0; // Child exits after running
        }
    }

    // Wait for all children to finish
    for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
        waitpid(pid[i], &status, 0);
    }

    printf("All child processes have finished\n");
    return 0;
}

