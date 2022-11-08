#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define _DEBUG_     0
typedef struct sRange {
    int s;
    int e;
} Range;

int cmpfunc(const void *a, const void *b) {
    Range *this = (Range *)a;
    Range *that = (Range *)b;
    if (this->s > that->s) return 1;
    if (this->s < that->s) return -1;
    return this->e - that->e;
}

__inline__ int overLaps(Range *a, Range *b) {
    if ((a->s <= b->e) && (a->e >= b->s)) return 1;
    return 0;
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N = 0, M = 0, A = 0, B = 0, C = 0, D = 0, i = 0, j = 0;
    int S = 0;
    scanf("%d %d", &N, &M);
    Range *shots = (Range *)malloc(N * sizeof(Range));
    Range *field = (Range *)malloc(M * sizeof(Range));
    for (i = 0; i < N; i++) {
        scanf("%d %d", &A, &B);
        shots[i].s = A;
        shots[i].e = B;
    }
    qsort(shots, N, sizeof(Range), cmpfunc);
    #if 0 //_DEBUG_
    for (i = 0; i < N; i++) {
        printf("%d %d\n", shots[i].s, shots[i].e);
    }
    #endif
    // get fielders
    for (i = 0; i < M; i++) {
        scanf("%d %d", &C, &D);
        field[i].s = C;
        field[i].e = D;
    }
    qsort(field, M, sizeof(Range), cmpfunc);
    // Keep moving fielder and shot together
    i = 0;
    j = 0;
    while (i < M && j < N) {
        if (field[i].e < shots[j].s) i++; // increment fielder
        else if (field[i].s > shots[j].e) j++; //increment shot
        else {
            // they are overlapping, check all the shots
            int tempJ = j;
            while (tempJ < N && shots[tempJ].s <= field[i].e) {
                if (overLaps(&shots[tempJ], &field[i])) {
                    S++;
                }
                tempJ++;
            }
            i++;
        }
        #if _DEBUG_
        printf("s %d, f %d, S %d\n", j, i, S);
        #endif
    }
    printf("%d\n", S);
    return 0;
}
