#include <stdio.h>
#include <stdlib.h>
typedef struct _node{
int x;
struct _node *next;
} lnode;
void init( int n ,int *tree);
void range_increment( int i, int j,
 int val ,int *tree);
int query( int i ,int *tree);
void insert_edge(int x,int y);
void dfs0(int u);
void preprocess();
int lca(int a,int b);
int dist(int u,int v);
void dfs1(int u,int p);
int dfs2(int u,int p);
void decompose(int root,int p);
int a[250000],cut[250000]={0},parent[250000],
DP[18][250000],mid[750000],left[750000],
right[750000],level[250000],
sub[250000],N,NN,nn;
long long count[250000]={0},
sum[250000]={0},con[250000]={0};
lnode *table[250000]={0};

int main(){
int x,y,z,leftd,rightd,i;
long long ans,aa=0;
scanf("%d",&NN);
for(i=0;i<NN;i++)
scanf("%d",a+i);
init(NN,mid);
init(NN,left);
init(NN,right);
for(i=0;i<NN;i++){
leftd=x=query(a[i]-1,left);
if(!x)
leftd=1;
rightd=y=query(a[i]-1,right);
if(!y)
rightd=NN;
z=query(a[i]-1,mid);
if(z)
insert_edge(z-1,a[i]-1);
range_increment(leftd-1,rightd-1,a[i]-z,mid);
range_increment(a[i]-1,rightd-1,a[i]-x,left);
range_increment(leftd-1,a[i]-1,a[i]-y,right);
}
preprocess();
decompose(a[NN/2]-1,-1);
for(i=0;i<NN;i++){
for(ans=sum[a[i]-1],x=a[i]-1;1;x=parent[x]){
if(parent[x]==-1)
break;
ans+=sum[parent[x]]-con[x]+dist(a[i]-1,
parent[x])*(count[parent[x]]-count[x]);
}
for(x=a[i]-1;x!=-1;x=parent[x]){
sum[x]+=dist(a[i]-1,x);
count[x]++;
if(parent[x]!=-1)
con[x]+=dist(a[i]-1,parent[x]);
}
printf("%lld\n",aa+=ans);
}
return 0;
}
void init( int n ,int *tree){
N = 1;
while( N < n ) N *= 2;
int i;
for( i = 1; i < N + n; i++ ) tree[i] = 0;
}
void range_increment( int i, int j, 
int val ,int *tree){
for( i += N, j += N; i <= j; 
i = ( i + 1 ) / 2, j = ( j - 1 ) / 2 )
{
if( i % 2 == 1 ) tree[i] += val;
if( j % 2 == 0 ) tree[j] += val;
}
}
int query( int i ,int *tree){
int ans = 0,j;
for( j = i + N; j; j /= 2 ) ans += tree[j];
return ans;
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
void dfs0(int u){
lnode *x;
for(x=table[u];x;x=x->next)
if(x->x!=DP[0][u]){
DP[0][x->x]=u;
level[x->x]=level[u]+1;
dfs0(x->x);
}
return;
}
void preprocess(){
int i,j;
level[a[0]-1]=0;
DP[0][a[0]-1]=a[0]-1;
dfs0(a[0]-1);
for(i=1;i<18;i++)
for(j=0;j<NN;j++)
DP[i][j] = DP[i-1][DP[i-1][j]];
return;
}
int lca(int a,int b){
int i;
if(level[a]>level[b]){
i=a;
a=b;
b=i;
}
int d = level[b]-level[a];
for(i=0;i<18;i++)
if(d&(1<<i))
b=DP[i][b];
if(a==b)return a;
for(i=17;i>=0;i--)
if(DP[i][a]!=DP[i][b])
a=DP[i][a],b=DP[i][b];
return DP[0][a];
}
int dist(int u,int v){
return level[u] + level[v] - 2*level[lca(u,v)];
}
void dfs1(int u,int p){
sub[u]=1;
nn++;
lnode *x;
for(x=table[u];x;x=x->next)
if(x->x!=p && !cut[x->x]){
dfs1(x->x,u);
sub[u]+=sub[x->x];
}
return;
}
int dfs2(int u,int p){
lnode *x;
for(x=table[u];x;x=x->next)
if(x->x!=p && sub[x->x]>nn/2 && !cut[x->x])
return dfs2(x->x,u);
return u;
}
void decompose(int root,int p){
nn=0;
dfs1(root,root);
int centroid = dfs2(root,root);
parent[centroid]=p;
cut[centroid]=1;
lnode *x;
for(x=table[centroid];x;x=x->next)
if(!cut[x->x])
decompose(x->x,centroid);
return;
}
  
