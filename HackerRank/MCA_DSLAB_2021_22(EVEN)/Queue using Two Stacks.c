#include<stdio.h>
#include<malloc.h>


struct node{
	int data;
	struct node* next;
};


struct queue{
	struct node* head1;
	struct node* head2;
};


struct node* push(struct node* temp,int data){
	struct node* newnode = (struct node*)malloc(sizeof(struct node));
	newnode->data = data;
	newnode->next = temp;
	temp = newnode;
	return temp;
}


void enqueue(struct queue* q,int data){
	q->head1 = push(q->head1,data);
}


int pop(struct node** temp){
	int data = ( *temp )->data;
	(*temp) = (*temp)->next;
	return data;
}


void dequeue(struct queue*q){
	int x;
	if(q->head2 == NULL){
		while(q->head1){
			x = pop( &(q->head1) );
			q->head2 = push(q->head2,x);
		}
		x = pop(&(q->head2));
	}else{
		x = pop(&(q->head2));		
	}	
}


void print(struct queue* q){
	int x;
	if(q->head2){
	}else{
		while(q->head1){
			x = pop((&q->head1));
			q->head2 = push(q->head2,x);
		}
		
	}
	x = q->head2->data;
	printf("%d\n",x);
}


int main(void){
	int data,queries,choice;
	struct queue* q  = (struct queue*)malloc(sizeof(struct queue));
	q->head1 = q->head2 = NULL;
	scanf("%d",&queries);
	for(int i = 0 ;i < queries ;i++){
		scanf("%d",&choice);
		if(choice == 1){
			scanf("%d",&data);
			enqueue(q,data);
		}else if(choice == 2){
			dequeue(q);
		}else if(choice == 3){
			print(q);
		}
	}

}
