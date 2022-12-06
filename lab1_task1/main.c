#include <unistd.h>
#include "sys/wait.h"

int main() {
    pid_t pid1, pid2, pid3, pid4, pid5;

    pid1 = fork();

    if (pid1 == 0) {
        pid4 = fork();
        sleep(10);
    } else {
        pid2 = fork();
        if (pid2 == 0) {
            pid4 = fork();
            if (pid4 == 0) {
                sleep(10);
            } else {
                pid5 = fork();
                sleep(10);
            }
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
