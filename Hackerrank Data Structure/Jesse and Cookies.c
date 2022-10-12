#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

long int n;
long int aa[1000002];
void siftdown(long int *a, long int n, long int start) {
    long int r, lch, swap, t;
    //printf("##%d %d##\n", start, a[start]);
    r = start;
    while (r * 2 <= n) {
        lch = 2 * r;
        swap = r;
        if (a[lch] < a[swap]) {
            swap = lch;
        }
        if (lch+1 <= n && a[lch+1] < a[swap]) {
            swap = lch+1;
        }
        if (swap == r) {
            return;
        } else {
            t = a[swap];
            a[swap] = a[r];
            a[r] = t;
            r = swap;
        }
    }
}

void heapify(long int *a, long int n)
{
    long int start;
    start = n/2;
    while (start >= 1) {
        siftdown(a, n, start);
        start --;
      //  print();
    }    
}
void print(long int *a) {
    long int i;
    for (i = 1; i <= n; i++)
        printf("%ld ", a[i]);
    printf("\n");
}
int main() {
    long int k, i, t, *a, tmp;
    scanf("%ld%ld", &n, &k);
    
    for(i = 1; i <= n; i++)
        scanf("%ld", &aa[i]);
//   print(aa);
    t = 0;
    heapify(aa, n);
//    print(aa);
    a = &aa[0];
    while (1) {
        
   //     print();
        if (a[1] >= k) 
            break;
        if (n == 2) {
            n--;
            if (a[1] < a[2]) {
                a[1] = a[1] + 2 * a[2];
            } else {
                a[1] = a[2] + 2 * a[1];
            }
            t++;
            
        }
        if (n == 1)
            break;
        
        if (a[2] < a[3]) {
            a[2] = a[1] + 2*a[2];
            siftdown(a, n, 2);
        } else {
            a[3] = a[1] + 2*a[3];
            siftdown(a, n, 3);
            
        }
        a[1] = a[n];
        n--;
        siftdown(a, n, 1);
        t++;
      // print(a);
            
    }
    if (a[1] < k)
        printf("-1\n");
    else
    printf("%ld\n", t);
   // print();
 
    return 0;
}
