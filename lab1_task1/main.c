#include <unistd.h>
#include "stdio.h"
#include "sys/wait.h"

int main() {
    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 == 0) {
        pid2 = fork();
        if (pid2 == 0) {
            sleep(20);
        }
        sleep(20);
    } else {
        waitpid(pid1, NULL, 0);
        printf("Done.");
    }

    return 0;
}
