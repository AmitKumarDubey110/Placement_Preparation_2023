#include<stdio.h>
int main()
{
    int n,t,i,j,a[300001],b[300001],c[1000002];//change
    long long d;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(i=0;i<=1000000;i++)
    {
        c[i]=0;
    }
    t=0;
    d=0;
    b[0]=a[0];
    c[a[0]]=1;
    for(i=1;i<n;i++)
    {
        if(a[i]>b[t])
        {
            while(a[i]>b[t]&&t>=0)
            {
                c[b[t]]=0;
                t--;
            }
            t++;
            b[t]=a[i];
            c[a[i]]++;
        }
        else
        {
            t++;
            b[t]=a[i];
            c[a[i]]++;
        }
        if(c[a[i]]!=0)
        {
            d+=c[a[i]]-1;
        }
    }
    printf("%lld",2*d);
    return 0;
}
