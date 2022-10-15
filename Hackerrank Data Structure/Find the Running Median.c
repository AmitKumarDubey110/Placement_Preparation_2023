#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
     
    
    int a[100000], n, i, j, t, k, start, end, mid;
    scanf("%d", &n);
    for(i=0; i < n; i++) {
        scanf("%d", &t);
        start = 0;
        end = i;
        mid = (end-start)/2;
        while (start != mid && mid != end) {
            
            if (a[mid] > t)
                end = mid;
            else if (a[mid] <= t)
                start = mid;
            mid = start + (end - start)/2;
                
        }
        
        for(j=mid; j < i; j++) {
            if (a[j] > t) {
                break;
            }
        }
        
                //memcpy(&a[j+1], &a[j], (i-j)*sizeof(int));
        for(k = i; k >= (j+1); k--)
              a[k] = a[k-1];
        a[j] = t;
        //for(j = 0; j <= i; j++)
        //    printf("%d ", a[j]);
       //printf("\n");
        if(i%2 == 0) {
            printf("%.1f\n", (float)a[i/2]);
        } else {
            printf("%.1f\n", (float)(a[i/2] + a[(i+1)/2])/2.0);
        }
    }
    return 0;
}
