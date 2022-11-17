#include <stdio.h>
#include <stdlib.h>
#define INF 200000
int get(int l,int r);
int max(int x,int y);
int min(int x,int y);
void init( int n );
void range_increment( int i, int j, int val );
int query( int i );
void sort_a(int*a,int size,int*new_size);
void merge(int*a,int*left,int*right,int left_size, int right_size,int*new_size);
int N,a[100000],b[100000],map[100001],dp[4][100000][18],dp1[30][100000],dp2[30][100000],tree[400000];

int main(){
  int n,k,s,ns,h,l,m,i,j;
  scanf("%d%d",&n,&k);
  for(i=j=1,map[0]=0;i<=100000;i++)
    if(j*2<=i){
      j*=2;
      map[i]=map[i-1]+1;
    }
    else
      map[i]=map[i-1];
  for(i=0;i<n;i++)
    scanf("%d",a+i);
  for(i=0;i<n;i++)
    dp[0][i][0]=dp[1][i][0]=dp[2][i][0]=dp[3][i][0]=a[i];
  for(j=1;1<<j<=n;j++)
    for(i=0;i+(1<<j)-1<n;i++){
      dp[0][i][j]=max(dp[0][i][j-1],dp[0][i+(1<<(j-1))][j-1]);
      dp[1][i][j]=min(dp[1][i][j-1],dp[1][i+(1<<(j-1))][j-1]);
      dp[2][i][j]=dp[2][i][j-1]|dp[2][i+(1<<(j-1))][j-1];
      dp[3][i][j]=dp[3][i][j-1]&dp[3][i+(1<<(j-1))][j-1];
    }
  for(i=0;i<n;i++)
    for(j=0;j<30;j++)
      if(a[i]&(1<<j)){
        dp1[j][i]=i;
        dp2[j][i]=INF;
      }
      else{
        dp1[j][i]=INF;
        dp2[j][i]=i;
      }
  for(i=n-2;i>=0;i--)
    for(j=0;j<30;j++){
      dp1[j][i]=min(dp1[j][i],dp1[j][i+1]);
      dp2[j][i]=min(dp2[j][i],dp2[j][i+1]);
    }
  init(n);
  for(i=0;i<n;i++){
    for(j=s=0;j<30;j++){
      if(dp1[j][i]!=INF)
        b[s++]=dp1[j][i];
      if(dp2[j][i]!=INF)
        b[s++]=dp2[j][i];
    }
    sort_a(b,s,&ns);
    for(j=ns-1;j>=0;j--)
      if(get(i,b[j])>=k){
        if(j==ns-1)
          h=n-1;
        else
          h=b[j+1]-1;
        l=s=b[j];
        while(l<=h){
          m=(h+l)/2;
          if(get(i,m)>=k){
            s=m;
            l=m+1;
          }
          else
            h=m-1;
        }
        range_increment(i,s,s-i+1);
        break;
      }
  }
  for(i=0;i<n;i++)
    printf("%d\n",query(i));
  return 0;
}
int get(int l,int r){
  int a,b,c,d,len;
  len=map[r-l+1];
  a=max(dp[0][l][len],dp[0][r-(1<<len)+1][len]);
  b=min(dp[1][l][len],dp[1][r-(1<<len)+1][len]);
  c=dp[2][l][len]|dp[2][r-(1<<len)+1][len];
  d=dp[3][l][len]&dp[3][r-(1<<len)+1][len];
  return c-d-a+b;
}
int max(int x,int y){
  return (x>y)?x:y;
}
int min(int x,int y){
  return (x<y)?x:y;
}
void init( int n )
{
  N = 1;
  while( N < n ) N *= 2;
  int i;
  for( i = 1; i < N + n; i++ ) tree[i] = -1;
}
void range_increment( int i, int j, int val )
{
  for( i += N, j += N; i <= j; i = ( i + 1 ) / 2, j = ( j - 1 ) / 2 )
  {
    if( i % 2 == 1 ) tree[i] = max(val,tree[i]);
    if( j % 2 == 0 ) tree[j] = max(val,tree[j]);
  }
}
int query( int i )
{
  int ans = -1,j;
  for( j = i + N; j; j /= 2 ) ans = max(tree[j],ans);
  return ans;
}
void sort_a(int*a,int size,int*new_size){
  if (size < 2){
    (*new_size)=size;
    return;
  }
  int m = (size+1)/2,i;
  int *left,*right;
  left=(int*)malloc(m*sizeof(int));
  right=(int*)malloc((size-m)*sizeof(int));
  for(i=0;i<m;i++)
    left[i]=a[i];
  for(i=0;i<size-m;i++)
    right[i]=a[i+m];
  int new_l_size=0,new_r_size=0;
  sort_a(left,m,&new_l_size);
  sort_a(right,size-m,&new_r_size);
  merge(a,left,right,new_l_size,new_r_size,new_size);
  free(left);
  free(right);
  return;
}
void merge(int*a,int*left,int*right,int left_size, int right_size,int*new_size){
  int i = 0, j = 0,index=0;
  while (i < left_size|| j < right_size) {
    if (i == left_size) {
      a[index++] = right[j];
      j++;
    } else if (j == right_size) {
      a[index++] = left[i];
      i++;
    } else if (left[i] <= right[j]) {
      a[index++] = left[i];
      i++;
    } else {
      a[index++] = right[j];
      j++;
    }
    if(index>1&&a[index-2]==a[index-1])
      index--;
  }
  (*new_size)=index;
  return;
}
