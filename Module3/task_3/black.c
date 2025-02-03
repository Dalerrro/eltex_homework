#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

typedef struct {
    double time_w; // #1
    double time_b; // #2
    time_t period;   
    int temp; // -1 = start, 1, 2      
} Chess;

int main() {
    Chess *game;
    int shmid;
    char pathname[] = "white.c";
    key_t key;

    if ((key = ftok(pathname, 0)) < 0) {
        perror("Не удалось создать ключ");
        exit(1);
    }

    if ((shmid = shmget(key, sizeof(Chess), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
        if (errno != EEXIST) {
            perror("ошибка создания shm");
            exit(1);
        }
        if ((shmid = shmget(key, sizeof(Chess), 0666)) < 0) {
            perror("ошибка подключения к shm");
            exit(1);
        }
    }

    if ((game = (Chess *)shmat(shmid, NULL, 0)) == (void *)-1) {
        perror("Ошибка привязки разделяемой памяти");
        exit(1);
    }

    if (game->temp != 1 && game->temp != 2) {
        game->time_w = 0;
        game->time_b = 0;
        game->period = time(NULL);
        game->temp = 2; 
        printf("Игра началась. Ходят чёрные.\n");
    }

    printf("#%d\n", game->temp);

    if (game->temp != 2) {
        printf("Ошибка хода. Сейчас ходят белые.\n");
        shmdt(game);
        exit(1);
    }

    double move_time = difftime(time(NULL), game->period);
    game->time_w += move_time;

    if (game->time_w > 10) {
        printf("!Предел по времени (+ %.2f сек) \n", move_time);
        printf("Время белых: %.2f секунд\n", game->time_w);
        printf("Время чёрных: %.2f секунд\n", game->time_b);
        shmdt(game);
        exit(1);

       if (shmctl(shmid, IPC_RMID, NULL) < 0) {
            perror("Ошибка удаления сегмента памяти");
        }

        shmdt(game);
        exit(1);
    }

    game->period = time(NULL);
    game->temp = 1; 


    printf("Ход чёрных. Прошло %.2f сек.\n", move_time);
    printf("Общее время белых: %.2f сек\n", game->time_w);
    printf("Общее время чёрных: %.2f сек\n", game->time_b);

    if (shmdt(game) < 0) {
        perror("Ошибка отсоединения памяти");
        exit(1);
    }
    return 0;
}