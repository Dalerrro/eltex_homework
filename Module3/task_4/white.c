#include "utils.h"

int main() {
    key_t key = get_queue_key();
    int msgid = msgget(key, IPC_CREAT | QUEUE_PERMISSIONS);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    int semid = create_semaphore();

   
    semctl(semid, 0, SETVAL, 1);  
    semctl(semid, 1, SETVAL, 0);

    struct move white_moves[] = {
        {"e2", "e4"}, {"g1", "f3"}, {"f1", "c4"}, {"d2", "d3"}
    };
    int num_moves = sizeof(white_moves) / sizeof(white_moves[0]);

    for (int i = 0; i < num_moves; i++) {
       
        struct sembuf wait_white = {0, -1, 0};
        semop(semid, &wait_white, 1);

    
        struct message msg;
        msg.message_type = 1;
        msg.move = white_moves[i];
        if (msgsnd(msgid, &msg, sizeof(struct move), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
        printf("Белые: %s -> %s\n", msg.move.from, msg.move.to);

       
        sleep(2);


        struct sembuf signal_black = {1, 1, 0};
        semop(semid, &signal_black, 1);
    }

    printf("Белые: ходов больше нет. Игра окончена.\n");
    return 0;
}
