#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Nothing to execute. Please enter some arguments next time.");
        return 0;
    }

    int status;
    pid_t pid = fork();
    if (pid == 0) {
        char *program = argv[1];
        char *arguments[argc];
        for (int i = 1; i <= argc; i++) {
            arguments[i - 1] = argv[i];
        }
        arguments[argc] = NULL;

        int exec_exit = execvp(program, arguments);
        if (exec_exit == -1) {
            exit(1);
        }
    } else {
        waitpid(pid, &status, 0);
        if (status == 0) {
            printf("Success.\n");
        } else {
            printf("Failed, exit code = %d\n", status);
        }
    }

    return 0;
}
