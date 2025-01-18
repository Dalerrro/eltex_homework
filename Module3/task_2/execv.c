#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    printf("PID: %d\n", getpid());

    if (argc > 1) {
        printf("Message: %s\n", argv[1]);
        return 0;
    }

    sleep(1);

    char *message = "hello world!"; 
    char *new_argv[] = {argv[0], message, NULL};

    execv(argv[0], new_argv);

    return 0; 
}
