#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    int num, rot,p,i;
    scanf("%d %d", &num, &rot);  
    int arr[num];
    
    for ( i = 0; i <num; i++)
    {
        
    scanf("%d",&arr[i]);    
    }
    for(i = 0; i <num; i++)
    {
        p=arr[(i+rot) % num];
        printf("%d ", p);    
    }
   
    
    return 0;
}