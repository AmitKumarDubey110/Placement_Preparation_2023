#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int n, a[100000][2], i, j, k;
    long int tot;
    scanf("%d", &n);
    for(i=0; i < n; i++)
        scanf("%d%d", &a[i][0], &a[i][1]);
    for(i = 0; i < n; i++) {
        j = i;
        k = n;
        tot = 0;
        while (k--) {
            tot += a[j][0];
          //  printf("## %d %d\n", tot, a[j][1]);
            if (tot < a[j][1])
                break;
            tot -= a[j][1];
            j ++;
            if (j == n)
                j = 0;
        }
        //printf("%d\n", k);
        if (k == -1) {
            printf("%d", j);
            break;
        }
        
    }
        
    
    return 0;
}
