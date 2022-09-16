#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct node {
    
    int data;
    struct node *left;
    struct node *right;
  
};

struct node* insert( struct node* root, int data ) {
		
	if(root == NULL) {
	
        struct node* node = (struct node*)malloc(sizeof(struct node));

        node->data = data;

        node->left = NULL;
        node->right = NULL;
        return node;
	  
	} else {
      
		struct node* cur;
		
		if(data <= root->data) {
            cur = insert(root->left, data);
            root->left = cur;
		} else {
            cur = insert(root->right, data);
            root->right = cur;
		}
	
		return root;
	}
}

/*
struct node
{
    int data;
    node* left;
    node* right;
};

*/

struct node2
{
    struct node2* next;
    struct node2* prev;
    struct node* data;
    int idx;
};

typedef struct{
    int size;
    struct node2* front;
    struct node2* rear;
}queue;

struct node2* CreateNode(struct node * data, int idx)
{
    struct node2* n;
    // n = (struct node2*)malloc(sizeof(struct node2));
    // n->data = (struct node*)malloc(sizeof(struct node));
    // n->next = NULL;
    // n->prev = NULL;
    // n->idx = idx;
    struct node2* node2 = (struct node2*)malloc(sizeof(struct node2));

        node2->idx = idx;

        node2->prev = NULL;
        node2->next = NULL;
    node2->data = data;
    return node2;
}


queue CreateQueue()
{
    queue q;
    q.size = 0;
    q.front = NULL;
    q.rear = NULL;
    return q;
}

void
Enqueue(queue *q, struct node * data, int idx)
{
    struct node2* n = CreateNode(data, idx);
    if(q->front == NULL)
        q->front = q->rear = n;
    else
    {
        q->rear->next = n;
        q->rear = n;
    }
    q->size++;
}

struct node2*
Dequeue(queue *q)
{
    if(q->size <= 0)
        return NULL; 
    struct node2* del = q->front;
    q->front = q->front->next;
    q->size--;
    return del;
}

int
IsQueueEmpty(queue *q)
{
    return q == NULL || q->size == 0;
}

void topView(struct node * root) {
    int *a, i, arr_size, idx;
    arr_size = 1001;
    idx = 500;
    struct node2 *curr;
    a = (int*)calloc(arr_size, sizeof(int));
    for (i = 0; i < arr_size; i ++) {
        a[i] = -1;
    }
    queue que = CreateQueue();
    Enqueue(&que, root, idx);
    while (!IsQueueEmpty(&que)) {
        curr = Dequeue(&que);

        if (a[curr->idx] == -1) {
            a[curr->idx] = (int)curr->data->data;
        }
        if (curr->data->left != NULL) {
            Enqueue(&que, curr->data->left, curr->idx -1);
        }
        if (curr->data->right != NULL) {
            Enqueue(&que, curr->data->right, curr->idx +1);
        }
    }

    for (i = 0; i < 1001; i++) {
        if (a[i] != -1){
            printf("%d ", a[i]);
        }
    }
    // if (root == NULL) {
    //     return;
    // }
    // if (a[idx] == -1) {
    //     a[idx] = root->data;
    // }
    // traverse(root->left; a; idx - 1);
    // traverse(root->right; a; idx + 1);
    
  
}

int main() {
  
    struct node* root = NULL;
    
    int t;
    int data;

    scanf("%d", &t);

    while(t-- > 0) {
        scanf("%d", &data);
        root = insert(root, data);
    }
  
	topView(root);
    return 0;
}
