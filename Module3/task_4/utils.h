#ifndef UTILS_H
#define UTILS_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SERVER_KEY_PATHNAME "chess_queue_key"
#define PROJECT_ID 'C'
#define QUEUE_PERMISSIONS 0660

struct move {
    char from[3];
    char to[3];
};

struct message {
    long message_type;
    struct move move;
};  

key_t get_queue_key() {
    key_t key = ftok(SERVER_KEY_PATHNAME, PROJECT_ID);
    if (key == -1) {
        perror("ftok");
        exit(1);
    }
    return key;
}

int create_semaphore() {
    key_t key = ftok(SERVER_KEY_PATHNAME, PROJECT_ID + 1);
    int semid = semget(key, 2, IPC_CREAT | QUEUE_PERMISSIONS);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }
    return semid;
}

#endif
