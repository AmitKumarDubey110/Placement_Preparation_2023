#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
//int16_t arr[30010][15010];
int16_t **arr;
int n;
int8_t tmp[30010];
int16_t cnt[30010];
int16_t inp[30010][2];
int d, min, max;
void scan(int k)
{
    int i;
    for (i = 1; i <= arr[k][0]; i++) {
        if (tmp[arr[k][i]] == 0) {
            tmp[arr[k][i]] = 1;
            d++;
            scan(arr[k][i]);
        }
    }
}

int main() {
    int i, j, a, b;
    scanf("%d", &n);
    
    
    
    arr = (int16_t **) calloc(1, (2 * n + 1) * sizeof(int16_t *));
    if (arr == NULL)
        return -1;
    for(i = 0; i < n; i++) {
        scanf("%d%d", &inp[i][0], &inp[i][1]);
        cnt[inp[i][0]]++;
        cnt[inp[i][1]]++;
    }
    
    for(i = 1; i <= 2*n; i++) {
        arr[i] = (int16_t *) calloc(1, (cnt[i]+1)*sizeof(int16_t));
        if (arr[i] == NULL)
            return -1;
    }
    
    /*
    for(i = 1; i <= 2*n; i++) {
        for(j = 0; j <= n; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    */
  //  return 0;
    for(i = 0; i < n; i++) {
        //scanf("%d%d", &a, &b);
        a=inp[i][0];
        b=inp[i][1];
        if (arr[a] == NULL) {
            arr[a] = (int16_t *) calloc(1, (n+1)*sizeof(int16_t));
            if (arr[a] == NULL)
                return -1;
        }
        if (arr[b] == NULL) {
            arr[b] = (int16_t *) calloc(1, (n+1)*sizeof(int16_t));
            if (arr[b] == NULL)
                return -1;
        }       
        arr[a][0]++;
        arr[a][arr[a][0]] = b;
        arr[b][0]++;
        arr[b][arr[b][0]] = a;
    }
    //return 0;
    /*
    for(i = 1; i <= 2*n; i++) {
        for(j = 0; j <= n; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    return 0;
    */
    /*
    for(i = 1; i <= n; i++) {
        if (arr[i] == NULL)
            continue;
        printf("%d -> ", i);
        for (j = 1; j <= arr[i][0]; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    */
    min = 2000000000;
    max = -1;
    for(i = 1; i <= n; i++) {
        d = 0;
        if (tmp[i] == 0) {
         //   printf("%d -> ", i);
            if (arr[i])
                scan(i);
         //   printf("%d\n", d);
        }
        if (d < min && d != 0)
            min = d;
        if (d > max)
            max = d;
    }
    printf("%d %d\n", min, max);
 
    return 0;
}
