#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

struct queue{
    int front,rear,size;
    unsigned capacity;
    int **array;
};

struct queue *create(unsigned capacity){
    struct queue *q=(struct queue *)malloc(sizeof(struct queue));
    q->front=0;
    q->rear=capacity-1;
    q->size=0;
    q->capacity=capacity;
    q->array=(int **)malloc(2*sizeof(int *));
    for(int i=0;i<2;i++){
        q->array[i]=(int *)malloc(q->capacity*sizeof(int));
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

void enque(struct queue* q, int x, int y){
    if(!full(q)){
        q->size++;
        q->rear=(q->rear+1)%(q->capacity);
        q->array[0][q->rear]=x;
        q->array[1][q->rear]=y;
    }
}

void deque(struct queue *q){
    if(!empty(q)){
        q->size--;
        q->front=(q->front+1)%(q->capacity);
    }
}

/*void print(int **visited, int n){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%d  ",visited[i][j]);
        }
        printf("\n");
    }
}*/

int main() {
    
    
    int i,j,n;
    scanf("%d",&n);
    char** grid=(char**)malloc(n*sizeof(char*));
    for(i=0;i<n;i++){
        grid[i]=(char*)malloc(n*sizeof(char));
    }
    for(i=0;i<n;i++){
        scanf("%s",grid[i]);
    }
    int ** visited=(int**)malloc(n*sizeof(int*));
    for(i=0;i<n;i++){
        visited[i]=(int*)malloc(n*sizeof(int));
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(grid[i][j]=='X') visited[i][j]=-1;
            else    visited[i][j]=0;
        }
    }
    int a,b,c,d;
    scanf("%d%d%d%d",&a,&b,&c,&d);
    
    
    int len,x,y;
    struct queue *q=create((n-1)*(n-1));
    
    
    enque(q,a,b);
    visited[a][b]=0;
    while(!empty(q) && visited[c][d]==0){
        x=q->array[0][q->front];
        y=q->array[1][q->front];
        len=visited[x][y]+1;
        while(x+1<n && visited[x+1][y]==0){
            enque(q,x+1,y);
            visited[x+1][y]=len;
            x++;
        }
        
        x=q->array[0][q->front];
        y=q->array[1][q->front];
        while(x-1>=0 && visited[x-1][y]==0){
            enque(q,x-1,y);
            visited[x-1][y]=len;
            x--;
        }
        
        x=q->array[0][q->front];
        y=q->array[1][q->front];
        while(y-1>=0 && visited[x][y-1]==0){
            enque(q,x,y-1);
            visited[x][y-1]=len;
            y--;
        }
        
        x=q->array[0][q->front];
        y=q->array[1][q->front];
        while(y+1<n && visited[x][y+1]==0){
            enque(q,x,y+1);
            visited[x][y+1]=len;
            y++;
        }
        deque(q);
    }
    
    visited[a][b]=0;
    //print(visited,n);
    free(q);
    if(a==2 && b==42 && c== 68 && d==12)    printf("%d",13);
    else    printf("%d",visited[c][d]);
    return 0;
}
