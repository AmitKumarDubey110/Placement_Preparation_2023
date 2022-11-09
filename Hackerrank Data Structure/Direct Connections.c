#include <stdio.h>
#include <stdlib.h>
#define MOD 1000000007
long long read(int idx,long long*tree);
void update(int idx ,int val,long long*tree,int MaxVal);
void sort_a(int*a,int*b,int*c,int size);
void merge(int*a,int*left_a,int*right_a,int*b,int*left_b,int*right_b,int*c,int*left_c,int*right_c,int left_size, int right_size);
void sort_a2(int*a,int*b,int size);
void merge2(int*a,int*left_a,int*right_a,int*b,int*left_b,int*right_b,int left_size, int right_size);

int main()
{
  int i,j,T,N;
  int *x,*p,*x_sort,*p_sort,*index;
  long long ans,temp,*n_tree,*d_tree;
  x=(int*)malloc(200000*sizeof(int));
  p=(int*)malloc(200000*sizeof(int));
  x_sort=(int*)malloc(200000*sizeof(int));
  p_sort=(int*)malloc(200000*sizeof(int));
  index=(int*)malloc(200000*sizeof(int));
  n_tree=(long long*)malloc(200001*sizeof(long long));
  d_tree=(long long*)malloc(200001*sizeof(long long));
  scanf("%d",&T);
  for(i=0;i<T;i++){
    ans=0;
    scanf("%d",&N);
    for(j=0;j<=N;j++)
      n_tree[j]=d_tree[j]=0;
    for(j=0;j<N;j++)
      scanf("%d",x+j);
    for(j=0;j<N;j++){
      scanf("%d",p+j);
      update(j+1,1,n_tree,N);
    }
    sort_a2(x,p,N);
    for(j=0;j<N;j++){
      x_sort[j]=x[j];
      p_sort[j]=p[j];
      index[j]=j;
      update(j+1,x[j],d_tree,N);
    }
    sort_a(p_sort,x_sort,index,N);
    for(j=N-1;j!=0;j--){
      temp=x_sort[j]*read(index[j],n_tree)-read(index[j],d_tree);
      while(temp<0)
    temp+=MOD;
      temp%=MOD;
      ans+=p_sort[j]*temp;
      ans%=MOD;
      temp=(read(N,d_tree)-read(index[j]+1,d_tree))-x_sort[j]*(read(N,n_tree)-read(index[j]+1,n_tree));
      while(temp<0)
    temp+=MOD;
      temp%=MOD;
      ans+=p_sort[j]*temp;
      ans%=MOD;
      update(index[j]+1,-1,n_tree,N);
      update(index[j]+1,-(x_sort[j]),d_tree,N);
    }
    printf("%lld\n",ans);
  }
  return 0;
}
long long read(int idx,long long*tree){
  long long sum = 0;
  while (idx > 0){
    sum += tree[idx];
    sum%=MOD;
    idx -= (idx & -idx);
  }
  return sum;
}
void update(int idx ,int val,long long*tree,int MaxVal){
  while (idx <= MaxVal){
    tree[idx] += val;
    tree[idx]%=MOD;
    idx += (idx & -idx);
  }
}
void sort_a(int*a,int*b,int*c,int size)
{
  if (size < 2)
    return;
  int m = (size+1)/2,i;
  int*left_a,*left_b,*left_c,*right_a,*right_b,*right_c;
  left_a=(int*)malloc(m*sizeof(int));
  right_a=(int*)malloc((size-m)*sizeof(int));
  left_b=(int*)malloc(m*sizeof(int));
  right_b=(int*)malloc((size-m)*sizeof(int));
  left_c=(int*)malloc(m*sizeof(int));
  right_c=(int*)malloc((size-m)*sizeof(int));
  for(i=0;i<m;i++){
    left_a[i]=a[i];
    left_b[i]=b[i];
    left_c[i]=c[i];
  }
  for(i=0;i<size-m;i++){
    right_a[i]=a[i+m];
    right_b[i]=b[i+m];
    right_c[i]=c[i+m];
  }
  sort_a(left_a,left_b,left_c,m);
  sort_a(right_a,right_b,right_c,size-m);
  merge(a,left_a,right_a,b,left_b,right_b,c,left_c,right_c,m,size-m);
  free(left_a);
  free(right_a);
  free(left_b);
  free(right_b);
  free(left_c);
  free(right_c);
  return;
}
void merge(int*a,int*left_a,int*right_a,int*b,int*left_b,int*right_b,int*c,int*left_c,int*right_c,int left_size, int right_size)
{
  int i = 0, j = 0;
  while (i < left_size|| j < right_size) {
    if (i == left_size) {
      a[i+j] = right_a[j];
      b[i+j] = right_b[j];
      c[i+j] = right_c[j];
      j++;
    } else if (j == right_size) {
      a[i+j] = left_a[i];
      b[i+j] = left_b[i];
      c[i+j] = left_c[i];
      i++;
    } else if (left_a[i] <= right_a[j]) {
      a[i+j] = left_a[i];
      b[i+j] = left_b[i];
      c[i+j] = left_c[i];
      i++;
    } else {
      a[i+j] = right_a[j];
      b[i+j] = right_b[j];
      c[i+j] = right_c[j];
      j++;
    }
  }
  return;
}
void sort_a2(int*a,int*b,int size)
{
  if (size < 2)
    return;
  int m = (size+1)/2,i;
  int*left_a,*left_b,*right_a,*right_b;
  left_a=(int*)malloc(m*sizeof(int));
  right_a=(int*)malloc((size-m)*sizeof(int));
  left_b=(int*)malloc(m*sizeof(int));
  right_b=(int*)malloc((size-m)*sizeof(int));
  for(i=0;i<m;i++){
    left_a[i]=a[i];
    left_b[i]=b[i];
  }
  for(i=0;i<size-m;i++){
    right_a[i]=a[i+m];
    right_b[i]=b[i+m];
  }
  sort_a2(left_a,left_b,m);
  sort_a2(right_a,right_b,size-m);
  merge2(a,left_a,right_a,b,left_b,right_b,m,size-m);
  free(left_a);
  free(right_a);
  free(left_b);
  free(right_b);
  return;
}
void merge2(int*a,int*left_a,int*right_a,int*b,int*left_b,int*right_b,int left_size, int right_size)
{
  int i = 0, j = 0;
  while (i < left_size|| j < right_size) {
    if (i == left_size) {
      a[i+j] = right_a[j];
      b[i+j] = right_b[j];
      j++;
    } else if (j == right_size) {
      a[i+j] = left_a[i];
      b[i+j] = left_b[i];
      i++;
    } else if (left_a[i] <= right_a[j]) {
      a[i+j] = left_a[i];
      b[i+j] = left_b[i];
      i++;
    } else {
      a[i+j] = right_a[j];
      b[i+j] = right_b[j];
      j++;
    }
  }
  return;
}
