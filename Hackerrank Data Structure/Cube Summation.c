#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define max 3001
#define max1 101
int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t,n,m,x1,x2,y1,y2,z1,z2;
    int i,j,k,x[max],y[max],z[max];
    long W[max];
    char str[7];
    scanf("%d",&t);
    j=0;
    while(t--)
    {
        long mat[max1][max1][max1]={0};
        scanf("%d%d",&n,&m);
        for(i=0;i<m;i++)
        {
            scanf("%s",str);
            if(str[0]=='U')
            {
                scanf("%d%d%d%ld",&x[j],&y[j],&z[j],&W[j]);
                mat[x[j]][y[j]][z[j]]=W[j];
                j++;
            }
            else
            {
                scanf("%d%d%d%d%d%d",&x1,&y1,&z1,&x2,&y2,&z2);
                long sum=0;
                for(k=0;k<j;k++)
                {
                    if(x[k]>=x1 && x[k]<=x2)
                    {
                        if(y[k]>=y1 && y[k]<=y2)
                        {
                            if(z[k]>=z1 && z[k]<=z2)
                            {
                                if(W[k]==mat[x[k]][y[k]][z[k]])
                                    sum+=W[k];
                            }
                        }
                    }
                }
                printf("%ld\n",sum);
            }
        }
    }
    return 0;
}
