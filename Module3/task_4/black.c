#include "utils.h"

int main() {
    key_t key = get_queue_key();
    int msgid = msgget(key, IPC_CREAT | QUEUE_PERMISSIONS);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    int semid = create_semaphore();

    struct move black_moves[] = {
        {"e7", "e5"}, {"b8", "c6"}, {"f8", "c5"}, {"d7", "d6"}
    };
    int num_moves = sizeof(black_moves) / sizeof(black_moves[0]);

    for (int i = 0; i < num_moves; i++) {
        
        struct sembuf wait_black = {1, -1, 0};
        semop(semid, &wait_black, 1);

       
        struct message msg;
        if (msgrcv(msgid, &msg, sizeof(struct move), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        printf("Черные: получили ход %s -> %s\n", msg.move.from, msg.move.to);

        
        msg.message_type = 1;
        msg.move = black_moves[i];
        if (msgsnd(msgid, &msg, sizeof(struct move), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
        printf("Черные: %s -> %s\n", msg.move.from, msg.move.to);

        sleep(2);

        struct sembuf signal_white = {0, 1, 0};
        semop(semid, &signal_white, 1);
    }

    printf("Черные: ходов больше нет. Игра окончена.\n");
    return 0;
}
