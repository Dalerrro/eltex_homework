#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>


void handle_sigint(int signum) {
    printf(" -thread 2 get SIGINT\n");
}

void* thread1(void* arg) {
    sigset_t mask;
    sigfillset(&mask);
    pthread_sigmask(SIG_BLOCK, &mask, NULL);

    pthread_t thread_id = pthread_self();
    printf("Thread 1 started! %ld  ( block ) \n", (long)thread_id);

    while (1) {
        sleep(1); 
    }
    return NULL;
}


void* thread2(void* arg) {
    signal(SIGINT, handle_sigint);

    pthread_t thread_id = pthread_self(); 
    printf("Thread 2 started! %ld  (wait SIGINT) \n", (long)thread_id);
    
    while (1) {
        sleep(1); 
    }
    return NULL;
}


void* thread3(void* arg) {
    sigset_t mask;
    int sig;

    sigemptyset(&mask);
    sigaddset(&mask, SIGQUIT); 
    pthread_sigmask(SIG_BLOCK, &mask, NULL);

    pthread_t thread_id = pthread_self(); 
    printf("Thread 3 started! %ld (wait SIGQUIT) \n", (long)thread_id);

    while (1) {
        sigwait(&mask, &sig); 
        if (sig == SIGQUIT) {
            printf(" -thread 3 get SIGQUIT\n");
            break; 
        }
    }
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGQUIT);
    pthread_sigmask(SIG_BLOCK, &mask, NULL);

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_create(&t3, NULL, thread3, NULL);

    pthread_join(t3, NULL);

    printf("end\n");
    pthread_cancel(t1); 
    pthread_cancel(t2); 

    return 0;
}