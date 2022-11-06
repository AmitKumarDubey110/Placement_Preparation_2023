#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *dc = calloc(n, sizeof(int));
    int count = 0;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        if (x < n) {
            int start = (i+1)%n;
            int end = (start-x+n)%n;
            dc[start]++;
            dc[end]--;
            if (end <= start) count++;
        }
    }
    int id = 0;
    int val = 0;
    for (int i = 0; i < n; i++) {
        count += dc[i];
        if (count > val) {
            val = count;
            id = i;
        }
    }
    printf("%d", id+1);
    free(dc);
    return 0;
}
