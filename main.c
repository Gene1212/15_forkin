#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    printf("Parent pre-forking\n");
    int p, status;
    p = fork();
    if (p > 0)
        p = fork();
    if (p == 0)
    {
        printf("Child PID: %d\n", getpid());
        srand(getpid());
        int x = rand() % 9 + 2;
        sleep(x);
        printf("Slept for %d seconds, child process is finished\n", x);
        return x;
    }
    int pid = waitpid(-1, &status, 0);
    if (WIFEXITED(status))
        printf("PID of completed child is %d and it slept for %d seconds\n", p, WEXITSTATUS(status));
    printf("Parent is done, program ending\n");
    return 0;
}