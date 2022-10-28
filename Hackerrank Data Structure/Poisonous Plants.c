#include<stdio.h>
int main(){
    long int n,i,j,min=0,locmin;
    scanf("%ld",&n);
    long long int *p=(long long int *)malloc(sizeof(long long int)*n);
    for(i=0;i<n;i++)
    scanf("%lld",&p[i]);
    
    i=n-2;
    j=n-1;
    
    while(i>=0){
               if(j<n && p[j]>p[i]){
                      locmin=0;
                              while(j<n && (p[j]>p[i] || p[j]<0)){
  
                              if(p[j]>0)
                              p[j]=locmin-1;
                              
                              if(locmin>p[j])
                              locmin = p[j];
                              //else
                              //p[j] = -1;
                              j++;               
                              }  
               }
               j=i;
               i--;
    }
    for(i=0;i<n;i++){
                     if(p[i]<min)
                     min=p[i];
    }
    printf("%ld ",-min);
    free(p);
    return 0;
}
