#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

struct queue{
    int front,rear,size;
    unsigned capacity;
    long *array;
    int *index;
};

struct queue *create(unsigned capacity){
    struct queue *q=(struct queue *)malloc(sizeof(struct queue));
    q->front=0;
    q->rear=capacity-1;
    q->size=0;
    q->capacity=capacity;
    q->array=(long *)malloc(q->capacity*sizeof(long));
    q->index=(int *)malloc(q->capacity*sizeof(int));
    for(int i=0;i<q->capacity;i++){
        q->array[i]=0;
        q->index[i]=0;
    }
    return q;
}

int full(struct queue* q){
    if(q->size==q->capacity)    return 1;
    else    return 0;
}

int empty(struct queue* q){
    if(q->size==0)  return 1;
    else    return 0;
}

void enque(struct queue* q, long x, int i){
    if(!full(q)){
        q->size++;
        q->rear=(q->rear+1)%(q->capacity);
        q->array[q->rear]=x;
        q->index[q->rear]=i;
    }
}

void deque(struct queue *q){
    if(!empty(q)){
        q->size--;
        q->front=(q->front+1)%(q->capacity);
    }
}

long top_array(struct queue *q){
    if(!empty(q))   return q->array[q->front];
    return INT_MAX;
}

int top_index(struct queue *q){
    if(!empty(q))   return q->index[q->front];
    return INT_MAX;
}

void deque_back(struct queue *q){
    if(!empty(q)){
        q->size--;
        q->rear=(q->rear-1);
        if(q->rear<0)   q->rear=q->capacity+q->rear;
    }
}

long bottom_array(struct queue *q){
    if(!empty(q))   return q->array[q->rear];
    return INT_MAX;
}

int main(){
    
    int n,Q,i,j,k;
    scanf("%d%d",&n,&Q);
    long *a=(long *)malloc(n*sizeof(long));
    for(i=0;i<n;i++){
        scanf("%li",&a[i]);
    }
    int d;
    
    
    
    for(i=0;i<Q;i++){
        long max,min=INT_MAX;
        scanf("%d",&d);
        struct queue *q=create(n);
        j=0;
        //printf("%d %d ",q->rear,q->size);
        while(j<d){
            if(empty(q))    enque(q,a[j],j); 
            else{
                while(a[j]>=bottom_array(q)){   deque_back(q);  }
                enque(q,a[j],j);
            }
            //for(k=0;k<n;k++){ printf("%li ",q->array[k]);  }
            //printf("%d ",bottom_array(q));
            j++;
        }
        min=top_array(q);
        
        
        
        while(j<n){
            while(j-top_index(q)<d && j<n){
                if(top_array(q)<min)    min=top_array(q);
                while(a[j]>=bottom_array(q)){
                    deque_back(q);
                }
                enque(q,a[j],j);
                j++;
            }
            if(j-top_index(q)==d && j<n){
                if(top_array(q)<min)    min=top_array(q);
                deque(q);
                while(a[j]>=bottom_array(q)){
                    deque_back(q);    
                }
                enque(q,a[j],j);
                j++;
            }
        }
        
        
        
        
        if(top_array(q)<min)    min=top_array(q);
        printf("%li\n",min);
        free(q);
    }
    
    
    
    
    
    return 0;
}
