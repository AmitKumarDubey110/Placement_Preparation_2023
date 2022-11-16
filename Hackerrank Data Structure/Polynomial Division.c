#include <stdio.h>
#include <stdlib.h>
#define MOD 1000000007
void build(int v,int tl,int tr);
void update(int v,int tl,int tr,int pos,int new_val);
long long sum(int v,int tl,int tr,int l,int r);
long long modInverse(long long a,long long mod);
int min(int x,int y);
int max(int x,int y);
int c[100000];
long long dp[100000],t[400000];

int main(){
  int n,a,b,q,x,y,a_inv,i;
  scanf("%d%d%d%d",&n,&a,&b,&q);
  a_inv=modInverse(a,MOD);
  for(i=dp[0]=1;i<100000;i++)
    dp[i]=(MOD-dp[i-1]*b%MOD*a_inv%MOD)%MOD;
  for(i=0;i<n;i++)
    scanf("%d",c+i);
  build(1,0,n-1);
  while(q--){
    scanf("%d",&x);
    if(x==1){
      scanf("%d%d",&x,&y);
      update(1,0,n-1,x,y);
    }
    else{
      scanf("%d%d",&x,&y);
      if(sum(1,0,n-1,x,y))
        printf("No\n");
      else
        printf("Yes\n");
    }
  }
  return 0;
}
void build(int v,int tl,int tr){
  int tm;
  if(tl==tr)
    t[v]=c[tl];
  else{
    tm=(tl+tr)/2;
    build(v*2,tl,tm);
    build(v*2+1,tm+1,tr);
    t[v]=(t[v*2]+t[v*2+1]*dp[tm-tl+1])%MOD;
  }
  return;
}
void update(int v,int tl,int tr,int pos,int new_val){
  int tm;
  if(tl==tr)
    t[v]=new_val;
  else{
    tm=(tl+tr)/2;
    if(pos<=tm)
      update(v*2,tl,tm,pos,new_val);
    else
      update(v*2+1,tm+1,tr,pos,new_val);
    t[v]=(t[v*2]+t[v*2+1]*dp[tm-tl+1])%MOD;
  }
  return;
}
long long sum(int v,int tl,int tr,int l,int r){
  int tm,temp;
  if(l>r)
    return 0;
  if(l==tl && r==tr)
    return t[v];
  tm=(tl+tr)/2;
  if(min(r,tm)>=l)
    temp=min(r,tm)-l+1;
  else
    temp=0;
  return (sum(v*2,tl,tm,l,min(r,tm))+sum(v*2+1,tm+1,tr,max(l,tm+1),r)*dp[temp])%MOD;
}
long long modInverse(long long a,long long mod){
    long long b0 = mod, t, q;
    long long x0 = 0, x1 = 1;
    while (a > 1) {
        q = a / mod;
        t = mod; mod = a % mod; a = t;
        t = x0; x0 = x1 - q * x0; x1 = t;
    }
    if (x1 < 0) x1 += b0;
    return x1;
}
int min(int x,int y){
  return (x<y)?x:y;
}
int max(int x,int y){
  return (x>y)?x:y;
}
