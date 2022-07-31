#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct _node node;
struct _node{
    long long int data;
    node *next;
};
node* getnode(long long int data){
    node *newnode=(node*)malloc(sizeof(node));
    newnode->data=data;
    newnode->next=NULL;
    return newnode;
}
node * push(node *top,int long long  data){
    node *newnode=getnode(data);
    if(top == NULL)
        return newnode;
    newnode->next=top;
    return newnode;        
}

node * delete(node *top){
    node  *temp=top;
    top=top->next;
    free(temp);
    return top;
}
void move(node *fromTop,node *toTop) {
    int data=fromTop->data;
    delete(fromTop);
    push(toTop,data);
        
}

void printMax(node *maxtop){
    printf("%lld\n",maxtop->data);
}
int main() {
   
    int choice;
    long long int N;
    long long int data;
    node *top=NULL,*maxtop=NULL;
    scanf("%lld",&N);
    while(N) {
        scanf("%d",&choice);
        if(choice == 1) {
            scanf("%lld",&data);
            if(top == NULL)
                maxtop=push(top,data);
            else if(data >= maxtop->data)
                maxtop=push(maxtop,data);
            top=push(top,data);
            
        }
        else if(choice == 2) {
            if(top->data == maxtop->data)
                maxtop=delete(maxtop);
            top=delete(top);
        }
        else if(choice == 3) {
            printMax(maxtop);
        }
        N--;
    }
    return 0;
}
