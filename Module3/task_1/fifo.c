#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>
#include <errno.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <string.h>

int fd_fifo;

void sig_handle(int sig) {
    char buffer[] = "Hello SIGABRT!\n";

    if (write(fd_fifo, buffer, strlen(buffer)) == -1) {
        perror("Failed to write to FIFO");
    }
    printf("SIGABRT\n");
    exit(0); 
}

int main() {

    unlink("/tmp/fifo1");

    if (mkfifo("/tmp/fifo1", 0666) == -1) {
        perror("Failed to create FIFO");
    }

    if ((fd_fifo = open("/tmp/fifo1", O_RDWR)) == -1) {
        perror("Failed to open FIFO");
    }

    struct sigaction sa;
    sa.sa_handler = sig_handle;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGABRT, &sa, NULL);

    printf("My pid is: %d\n", getpid());
    printf("Waiting...\n");

    while (1) pause();

    close(fd_fifo);
    unlink("/tmp/fifo1");

    return 0;
}
