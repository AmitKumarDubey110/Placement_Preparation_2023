#include <stdio.h>

long long arr[10000005];
long long diff[10000005];
    
int main(void)
{
    int a,b,k,n,m,i;
    long long max,val;
    
    scanf("%d%d",&n,&m);
    
    
    while(m--)
    {
        scanf("%d%d%d",&a,&b,&k);
        
        if(a==1)
        {
         arr[1] += k; 
        
          if(b<n)
          diff[b] -= k;
        }
        else if(b<n)
        {
         diff[a-1] += k;
         diff[b] -= k;
        }
        else if(b==n)
         diff[a-1] += k;
    }
    
    max = arr[1];
    val = arr[1];
    
    for(i=1;i<n;i++)
    {
      val += diff[i];
      if(val > max)
       max = val;
    } 
    
    printf("%lld\n",max);
    
    return 0;
}
