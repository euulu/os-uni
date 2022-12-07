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
        char *program = argv[1];
        char *arguments[argc];
        for (int i = 1; i <= argc; i++) {
            arguments[i-1] = argv[i];
        }
        arguments[argc] = NULL;

        execvp(program, arguments);
    } else {
        waitpid(pid, NULL, 0);
    }

    return 0;
}
