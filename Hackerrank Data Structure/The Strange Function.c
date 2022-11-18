#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define INF 200000
typedef struct _node{
  int gcd;
  int max;
  long long sum;
} node;
typedef struct _tree_node{
  enum {red,black} colour;
  int data;
  int real;
  struct _tree_node *left,*right,*parent;
}tree_node;
void solve(int start,int bs,int ns);
void copy_tree(tree_node **d,tree_node *r);
void build(int v,int tl,int tr);
long long query(int v,int tl,int tr,int l,int r,int *gcd,int *ma,long long *sum);
void getp(long long N,long long*prim);
long long CC(long long n, long long d);
int max(int x,int y);
int min(int x,int y);
int abss(int x);
int search(tree_node *root,int data);
void left_rotate(tree_node **root,tree_node *x);
void right_rotate(tree_node **root,tree_node *y);
void reconstruct(tree_node **root,tree_node *x);
int normal_insert(tree_node **root,tree_node *x);
void insert(tree_node **root,tree_node *x);
void sort_a(int*a,int size,int*new_size);
void merge(int*a,int*left,int*right,int left_size, int right_size,int*new_size);
void init( int n );
int range_sum( int i, int j );
void update( int i, long long val );
int a[50000],b[50000],nonzero[50000],rp[30],rc[30],treei[200000],rs,s,N;
long long ans,p[1000],tree[200000];
node t[200000];
tree_node *map[50000];

int main(){
  int n,x,ns,i,j,k,l;
  long long sum;
  tree_node *last_node,*p_node;
  getp(1000,p);
  scanf("%d",&n);
  for(i=0;i<n;i++)
    scanf("%d",a+i);
  build(1,0,n-1);
  init(n);
  for(i=sum=0;i<n;i++){
    sum+=a[i];
    update(i,sum);
  }
  for(i=n-1;i>=0;i--){
    if(i==n-1)
      last_node=NULL;
    else
      last_node=map[i+1];
    if(a[i]){
      nonzero[i]=i;
      for(j=rs=0,x=abss(a[i]);p[j] && p[j]*p[j]<=x;j++)
        if(x%p[j]==0){
          rp[rs]=p[j];
          rc[rs]=0;
          while(x%p[j]==0){
            rc[rs]++;
            x/=p[j];
          }
          rs++;
        }
      if(x!=1){
        rp[rs]=x;
        rc[rs]=1;
        rs++;
      }
      for(j=s=0;j<rs;j++)
        for(k=0,x=rp[j];k<rc[j];k++,x*=rp[j]){
          p_node=(tree_node*)malloc(sizeof(tree_node));
          p_node->data=x;
          p_node->left=p_node->right=p_node->parent=NULL;
          l=search(last_node,x);
          if(l!=INF){
            p_node->real=l;
            b[s++]=l+1;
          }
          else
            p_node->real=i;
          insert(&map[i],p_node);
        }
      b[s++]=i;
      sort_a(b,s,&ns);
      solve(i,ns,n);
    }
    else{
      nonzero[i]=INF;
      s=0;
      copy_tree(&map[i],last_node);
      if(i!=n-1 && nonzero[i+1]!=INF)
        b[s++]=nonzero[i+1];
      sort_a(b,s,&ns);
      solve(i,ns,n);
    }
    if(i!=n-1)
      nonzero[i]=min(nonzero[i],nonzero[i+1]);
  }
  printf("%lld",ans);
  return 0;
}
void solve(int start,int bs,int ns){
  int gcd,ma,i,j;
  long long t,sum;
  for(i=0;i<bs;i++){
    if(b[i]==ns)
      continue;
    if(i==bs-1)
      j=range_sum(b[i],ns-1);
    else
      j=range_sum(b[i],b[i+1]-1);
    t=query(1,0,ns-1,start,j,&gcd,&ma,&sum);
    if(t>ans)
      ans=t;
  }
  return;
}
void copy_tree(tree_node **d,tree_node *r){
  tree_node *p;
  if(!r)
    return;
  copy_tree(d,r->left);
  p=(tree_node*)malloc(sizeof(tree_node));
  p->data=r->data;
  p->real=r->real;
  p->left=p->right=p->parent=NULL;
  insert(d,p);
  b[s++]=r->real+1;
  copy_tree(d,r->right);
  return;
}
void build(int v,int tl,int tr){
  int tm;
  if(tl==tr){
    t[v].gcd=abss(a[tl]);
    t[v].max=t[v].sum=a[tl];
  }
  else{
    tm=(tl+tr)/2;
    build(2*v,tl,tm);
    build(2*v+1,tm+1,tr);
    t[v].gcd=CC(t[2*v].gcd,t[2*v+1].gcd);
    t[v].max=max(t[2*v].max,t[2*v+1].max);
    t[v].sum=t[2*v].sum+t[2*v+1].sum;
  }
  return;
}
long long query(int v,int tl,int tr,int l,int r,int *gcd,int *ma,long long *sum){
  int tm,g1,g2,m1,m2;
  long long s1,s2;
  if(tl>r || tr<l){
    *gcd=0;
    *ma=0;
    *sum=0;
    return 0;
  }
  if(tl>=l && tr<=r){
    *gcd=t[v].gcd;
    *ma=t[v].max;
    *sum=t[v].sum;
    return (*gcd)*((*sum)-(*ma));
  }
  tm=(tl+tr)/2;
  query(2*v,tl,tm,l,r,&g1,&m1,&s1);
  query(2*v+1,tm+1,tr,l,r,&g2,&m2,&s2);
  *gcd=CC(g1,g2);
  *ma=max(m1,m2);
  *sum=s1+s2;
  return (*gcd)*((*sum)-(*ma));
}
void getp(long long N,long long*prim)
{
  long long i,j,index=2,flag;
  if(N<=1){
    prim[0]=0;
    return;}
  if(N==2){
  prim[0]=2;
  prim[1]=0;
  return;}
  prim[0]=2;
  prim[1]=3;
  for(i=5;i<=N;i=i+2)
    {
      for(j=1,flag=1;prim[j]<=sqrt(i);j++)
        {
          if(i%prim[j]==0){
            flag=0;
            break;}
        }
      if(flag==1)
        {prim[index]=i;
          index++;}
    }
  prim[index]=0;
  return;
}
long long CC(long long n, long long d)
{
  if(n==0)
    return d;
  if(d==0)
    return n;
    while( 1 )
    {
        n = n % d;
	if( n == 0 )
		return d;
	d = d % n;
        if( d == 0 )
		return n;
    }
}
int max(int x,int y){
  return (x>y)?x:y;
}
int min(int x,int y){
  return (x<y)?x:y;
}
int abss(int x){
  return (x<0)?-x:x;
}
int search(tree_node *root,int data){
  if(!root)
    return INF;
  if(root->data==data)
    return root->real;
  if(data<root->data)
    return search(root->left,data);
  return search(root->right,data);
}
void left_rotate(tree_node **root,tree_node *x){
  tree_node *y;
  y=x->right;
  if(!y) return;
  x->right=y->left;
  if(y->left)
    y->left->parent=x;
  y->parent=x->parent;
  if(x->parent==NULL) *root=y;
  else
    if(x==x->parent->left)
      x->parent->left=y;
    else
      x->parent->right=y;
  y->left=x;
  x->parent=y;
  return;
}
void right_rotate(tree_node **root,tree_node *y){
  tree_node *x;
  x=y->left;
  if(!x) return;
  y->left=x->right;
  if(x->right)
    x->right->parent=y;
  x->parent=y->parent;
  if(y->parent==NULL) *root=x;
  else
    if(y==y->parent->right)
      y->parent->right=x;
    else
      y->parent->left=x;
  x->right=y;
  y->parent=x;
  return;
}
void reconstruct(tree_node **root,tree_node *x){
  tree_node *y,*z;
  y=x->parent;
  z=x->parent->parent;
  x->colour=black;
  z->colour=red;
  x->parent=z->parent;
  if(z->parent==NULL)
    *root=x;
  else if(z==z->parent->left)
    z->parent->left=x;
  else
    z->parent->right=x;
  if(z->left==y){
    x->left=y;
    x->right=z;
  }
  else{
    x->left=z;
    x->right=y;
  }
  y->parent=z->parent=x;
  y->left=y->right=z->left=z->right=NULL;
  return;
}
int normal_insert(tree_node **root,tree_node *x){
  if(*root==NULL)
    *root=x;
  else if((*root)->data==x->data)
    return 0;
  else{
    x->parent=*root;
    if((*root)->data>x->data)
      return normal_insert(&((*root)->left),x);
    else
      return normal_insert(&((*root)->right),x);
  }
  return 1;
}
void insert(tree_node **root,tree_node *x){
  if(!normal_insert(root,x))
    return;
  tree_node *y;
  x->colour=red;
  while(x!=*root && x->parent->colour==red){
    if(x->parent==x->parent->parent->left){
      y=x->parent->parent->right;
      if(!y)
        if(x==x->parent->left){
          x->parent->colour=black;
          x->parent->parent->colour=red;
          right_rotate(root,x->parent->parent);
        }
        else{
          y=x->parent;
          reconstruct(root,x);
          x=y;
        }
      else if(y->colour==red){
        x->parent->colour=black;
        y->colour=black;
        x->parent->parent->colour=red;
        x=x->parent->parent;
      }
      else{
        if(x==x->parent->right){
          x=x->parent;
          left_rotate(root,x);
        }
        x->parent->colour=black;
        x->parent->parent->colour=red;
        right_rotate(root,x->parent->parent);
      }
    }
    else{
      y=x->parent->parent->left;
      if(!y)
        if(x==x->parent->right){
          x->parent->colour=black;
          x->parent->parent->colour=red;
          left_rotate(root,x->parent->parent);
        }
        else{
          y=x->parent;
          reconstruct(root,x);
          x=y;
        }
      else if(y->colour==red){
        x->parent->colour=black;
        y->colour=black;
        x->parent->parent->colour=red;
        x=x->parent->parent;
      }
      else{
        if(x==x->parent->left){
          x=x->parent;
          right_rotate(root,x);
        }
        x->parent->colour=black;
        x->parent->parent->colour=red;
        left_rotate(root,x->parent->parent);
      }
    }
  }
  (*root)->colour=black;
  return;
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
void init( int n )
{
  N = 1;
  while( N < n ) N *= 2;
  int i;
  for( i = 1; i < N + n; i++ ) tree[i] = -1000000000000000000LL;
}
int range_sum( int i, int j )
{
  int ansi;
  long long ans = -1000000000000000000LL;
  for( i += N, j += N; i <= j; i = ( i + 1 ) / 2, j = ( j - 1 ) / 2 )
  {
    if( i % 2 == 1 )
      if(tree[i]>ans){
        ans=tree[i];
        ansi=treei[i];
      }
    if( j % 2 == 0 )
      if(tree[j]>ans){
        ans=tree[j];
        ansi=treei[j];
      }
  }
  return ansi;
}
void update( int i, long long val )
{
  int j;
  for( j = i + N; j; j /= 2 )
    if(val>tree[j]){
      tree[j]=val;
      treei[j]=i;
    }
}
