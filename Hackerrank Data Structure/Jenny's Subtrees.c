#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASH_SIZE 123455
typedef struct _node{
  int *a;
  int size;
  int label;
  struct _node *next;
} node;
typedef struct _lnode{
  int x;
  struct _lnode *next;
} lnode;
void dfs1(int x,int pa,int h);
void dfs2(int u,int p,int f);
void dfs3(int x,int pa);
void insert_edge(int x,int y);
int insert();
void sort_a(int*a,int size);
void merge(int*a,int*left,int*right,int left_size, int right_size);
int label,size,c1,c2,a[3000],dp[3000],dp2[5000000],cut[3000],sub[3000];
node *hash[HASH_SIZE];
lnode *table[3000];

int main(){
  int n,r,x,y,ans,i;
  scanf("%d%d",&n,&r);
  for(i=0;i<n-1;i++){
    scanf("%d%d",&x,&y);
    insert_edge(x-1,y-1);
  }
  for(i=ans=0;i<n;i++){
    size=x=0;
    dfs1(i,-1,r);
    c2=-1;
    dfs2(i,-1,0);
    dfs3(c1,-1);
    ans++;
    if(dp2[dp[c1]])
      ans--;
    else{
      x=dp[c1];
      if(c2!=-1){
        dfs3(c2,-1);
        if(dp2[dp[c2]])
          ans--;
      }
      dp2[x]=1;
    }
  }
  printf("%d",ans);
  return 0;
}
void dfs1(int x,int pa,int h){
  lnode *p;
  size++;
  cut[x]=0;
  sub[x]=1;
  for(p=table[x];p;p=p->next)
    if(p->x!=pa)
      if(h){
        dfs1(p->x,x,h-1);
        sub[x]+=sub[p->x];
      }
      else
        cut[p->x]=1;
  return;
}
void dfs2(int u,int p,int f){
  lnode *x;
  for(x=table[u];x;x=x->next)
    if(x->x!=p && sub[x->x]>size/2 && !cut[x->x])
      return dfs2(x->x,u,f);
    else if(!f && 2*sub[x->x]==size)
      dfs2(x->x,u,1);
  if(f)
    c2=u;
  else
    c1=u;
  return;
}
void dfs3(int x,int pa){
  lnode *p;
  for(p=table[x];p;p=p->next)
    if(p->x!=pa && !cut[p->x])
      dfs3(p->x,x);
  for(p=table[x],size=0;p;p=p->next)
    if(p->x!=pa && !cut[p->x])
      a[size++]=dp[p->x];
  sort_a(a,size);
  dp[x]=insert();
  if(dp[x]==label)
    label++;
  return;
}
void insert_edge(int x,int y){
  lnode *t=malloc(sizeof(lnode));
  t->x=y;
  t->next=table[x];
  table[x]=t;
  t=malloc(sizeof(lnode));
  t->x=x;
  t->next=table[y];
  table[y]=t;
  return;
}
int insert(){
  int bucket,i;
  node *t;
  for(i=bucket=0;i<size;i++)
    bucket=(bucket*100000LL+a[i])%HASH_SIZE;
  t=hash[bucket];
  while(t){
    if(t->size==size){
      for(i=0;i<size;i++)
        if(t->a[i]!=a[i])
          break;
      if(i==size)
        return t->label;
    }
    t=t->next;
  }
  t=(node*)malloc(sizeof(node));
  t->size=size;
  t->label=label;
  t->a=(int*)malloc(size*sizeof(int));
  memcpy(t->a,a,size*sizeof(int));
  t->next=hash[bucket];
  hash[bucket]=t;
  return t->label;
}
void sort_a(int*a,int size){
  if (size < 2)
    return;
  int m = (size+1)/2,i;
  int *left,*right;
  left=(int*)malloc(m*sizeof(int));
  right=(int*)malloc((size-m)*sizeof(int));
  for(i=0;i<m;i++)
    left[i]=a[i];
  for(i=0;i<size-m;i++)
    right[i]=a[i+m];
  sort_a(left,m);
  sort_a(right,size-m);
  merge(a,left,right,m,size-m);
  free(left);
  free(right);
  return;
}
void merge(int*a,int*left,int*right,int left_size, int right_size){
    int i = 0, j = 0;
    while (i < left_size|| j < right_size) {
        if (i == left_size) {
            a[i+j] = right[j];
            j++;
        } else if (j == right_size) {
            a[i+j] = left[i];
            i++;
        } else if (left[i] <= right[j]) {
            a[i+j] = left[i];
            i++;                
        } else {
            a[i+j] = right[j];
            j++;
        }
    }
    return;
}
