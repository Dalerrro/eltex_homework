#include <stdio.h>

#define NUM 2;

int main () {
    int N;
    int result = 1;

    printf("Enter N: ");
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        result *= NUM;
    }

    printf("Result = %d\n", result);

    return 0;
}