#include "stdio.h"
#include "unistd.h"
#include "sys/wait.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Nothing to execute. Please enter some arguments next time.");
        return 0;
    }

    pid_t pid = fork();
    if (pid == 0) {
        printf("I am a child process: %d\n", getppid());
    } else {
        waitpid(pid, NULL, 0);
        printf("I am a parent process: %d\n", getppid());
    }

    return 0;
}
