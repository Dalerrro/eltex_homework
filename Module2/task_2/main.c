#include <stdio.h>

#define NUM 2;

int main () {
    int N;
    int result = 1;
    int *p = &result;

    printf("Enter N: ");
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        *p *= NUM;
    }

    printf("Result = %d\n", result);

    return 0;
}