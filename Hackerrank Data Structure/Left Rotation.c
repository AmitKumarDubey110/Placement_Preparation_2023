#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int n; 
    scanf("%d",&n);
    int d;
    scanf("%d",&d);
    int *arr = malloc(sizeof(int) * n);
    
    for(int arr_i = 0; arr_i < n; arr_i++){
       scanf("%d",&arr[arr_i]);
    }
    
    int *arr2 = malloc(sizeof(int) * n);
    int curr=0;
    for(int i=d; i<n; i++) {
        arr2[curr] = arr[i];
        curr++;
    }
    for(int i=0; i<d; i++) {
        arr2[curr] = arr[i];
        curr++;
    }
    
    for(int i=0; i<n; i++) {
        printf("%d ",arr2[i]);
    }
    
    return 0;
}
