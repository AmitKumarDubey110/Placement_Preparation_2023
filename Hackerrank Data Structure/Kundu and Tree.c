#include<stdio.h>
#include<stdlib.h>
#define mod 1000000007
#define ll long long
ll nodes[100005],hash[100005],sz[100005];

ll root(ll i)
{
    while(i!=nodes[i])i=nodes[i];
    return i;
}
void unon_ins(ll p,ll q)
{
    ll i,j;
    i=root(p);
    j=root(q);
    if(sz[i]<sz[j]){nodes[i]=j;sz[i]+=sz[j];}
    else{nodes[j]=i;sz[j]+=sz[i];}
}


int main()
    {

    long long res,prod1,prod2,sum=0;
    ll n,i,j,k,n_b=0;
    char ch;
    for(i=0;i<100005;i++)
        nodes[i]=i;
    scanf("%lld",&n);
    for(i=1;i<n;i++)
        {
        ll x,y;
        scanf("%lld %lld %c",&x,&y,&ch);
        //printf("%d %d %c\n",x,y,ch);
        if(ch=='b')
            {
            unon_ins(x,y);
            n_b++;
            }
        }
    if(((n-1)-n_b)>=2){    
    
    for(i=1;i<=n;i++)
            hash[root(nodes[i])]++;

        res=((n*(n-1)/2)*(n-2))/3;
        for(i=1;i<=n;i++)
        {
            long long t=hash[i];
            prod1=prod2=0;
            prod1=((t*(t-1))/2)*(3*n-2*t-2)/3;
            sum=(sum+prod1);
        }
        res=(res-sum);
        
        printf("%lld\n",res%mod);}
    else
        printf("0\n");
    return 0;
}
