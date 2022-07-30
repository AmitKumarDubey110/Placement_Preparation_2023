#include <stdio.h>
#include <stdlib.h>
typedef struct _ct_node{
  int size;
  int priority;
  int value;
  struct _ct_node *left,*right;
} ct_node;
void tar(ct_node *root);
int get_size(ct_node *root);
ct_node* merge(ct_node *L,ct_node *R);
int sizeOf(ct_node *root);
void recalc(ct_node *root);
void split(int x,ct_node **L,ct_node **R,ct_node *root);
void computeTree();
int P[100000],T[100000],st[100000],N;
ct_node pool[100000];

int main(){
  int M,x,y,z,i;
  ct_node *root,*l,*m,*r,*t;
  scanf("%d%d",&N,&M);
  for(i=0;i<N;i++){
    scanf("%d",&pool[i].value);
    P[i]=pool[i].priority=rand();
    pool[i].left=pool[i].right=NULL;
  }
  computeTree();
  for(i=0;i<N;i++)
    if(T[i]==-1)
      root=&pool[i];
    else
      if(i<T[i])
        pool[T[i]].left=&pool[i];
      else
        pool[T[i]].right=&pool[i];
  get_size(root);
  for(i=0;i<M;i++){
    scanf("%d%d%d",&x,&y,&z);
    switch(x){
      case 1:
        split(y-2,&l,&t,root);
        split(z-y,&m,&r,t);
        root=merge(merge(m,l),r);
        break;
      default:
        split(y-2,&l,&t,root);
        split(z-y,&m,&r,t);
        root=merge(merge(l,r),m);
    }
  }
  N=0;
  tar(root);
  printf("%d\n",(T[0]>T[N-1])?T[0]-T[N-1]:T[N-1]-T[0]);
  for(i=0;i<N;i++)
    printf("%d ",T[i]);
  return 0;
}
void tar(ct_node *root){
  if(!root)
    return;
  tar(root->left);
  T[N++]=root->value;
  tar(root->right);
  return;
}
int get_size(ct_node *root){
  if(!root)
    return 0;
  root->size=get_size(root->left)+get_size(root->right)+1;
  return root->size;
}
ct_node* merge(ct_node *L,ct_node *R){
  if(!L)
    return R;
  if(!R)
    return L;
  if(L->priority>R->priority){
    L->right=merge(L->right,R);
    recalc(L);
    return L;
  }
  R->left=merge(L,R->left);
  recalc(R);
  return R;
}
int sizeOf(ct_node *root){
  return (root)?root->size:0;
}
void recalc(ct_node *root){
  root->size=sizeOf(root->left)+sizeOf(root->right)+1;
  return;
}
void split(int x,ct_node **L,ct_node **R,ct_node *root){
  if(!root){
    *L=*R=NULL;
    return;
  }
  int curIndex=sizeOf(root->left);
  ct_node *t;
  if(curIndex<=x){
    split(x-curIndex-1,&t,R,root->right);
    root->right=t;
    recalc(root);
    *L=root;
  }
  else{
    split(x,L,&t,root->left);
    root->left=t;
    recalc(root);
    *R=root;
  }
  return;
}
void computeTree(){
  int i,k,top=-1;
  for(i=0;i<N;i++){
    k=top;
    while(k>=0 && P[st[k]]<P[i])
      k--;
    if(k!=-1)
      T[i]=st[k];
    if(k<top)
      T[st[k+1]]=i;
    st[++k]=i;
    top=k;
  }
  T[st[0]]=-1;
  return;
}
