#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

/* Head ends here */
void partition(int ar_size, int *  ar) {

int f,temp=ar[0],j=0,k=0,i;
    int ar1[ar_size],ar2[ar_size];
    for(i=0;i<ar_size;i++)
    {
        if(ar[i]<temp)
        {
            ar1[j]=ar[i];
            j++;
        }
        if(ar[i]>temp)
        {
            ar2[k]=ar[i];
            k++;
           //printf("k=%d\n",k);
        }
       
    }
  /*  ar1[j]=temp;
    j++;
        for(i=0;i<k;i++)
        {
         ar1[j]=ar2[i];
            j++;
        }*/
   // printf("j=%d\n",j);
    for(i=0;i<j;i++)
    printf("%d ",ar1[i]);
    printf("%d ",temp);
    for(i=0;i<k;i++)
        printf("%d ",ar2[i]);
    
}

/* Tail starts here */
int main() {
   
   int _ar_size;
scanf("%d", &_ar_size);
int _ar[_ar_size], _ar_i;
for(_ar_i = 0; _ar_i < _ar_size; _ar_i++) { 
   scanf("%d", &_ar[_ar_i]); 
}

partition(_ar_size, _ar);
   
   return 0;
}
