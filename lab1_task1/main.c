#include <unistd.h>
#include "stdio.h"
#include "sys/wait.h"

int main() {
    pid_t pid1, pid2, pid3;

    pid1 = fork();

    if (pid1 == 0) {
        sleep(10);
    } else {
        pid2 = fork();
        if (pid2 == 0) {
            sleep(10);
        } else {
            pid3 = fork();
            if (pid3 == 0) {
                sleep(10);
            } else {
                waitpid(pid1, NULL, 0);
            }
        }
    }

    return 0;
}
