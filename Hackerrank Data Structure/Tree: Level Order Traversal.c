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

/* you only have to complete the function given below.  
node is defined as  

struct node {
    
    int data;
    struct node *left;
    struct node *right;
  
};

*/int height(struct node* root)
{
    if(!root)
        return 0;
    else
    {
        int rl=height(root->left);
        int rr=height(root->right);
        if(rl>rr)
            return rl+1;
        else
            return rr+1;
    }
}void printlevelorder(struct node* root,int level)
{
    if(!root)
        return;
    else if(level==1)
        printf("%d ",root->data);
    else if(level>1)
    {
        printlevelorder(root->left,level-1);
        printlevelorder(root->right,level-1);
}
}
void levelOrder( struct node *root) {
    int h=height(root);
    int i;
    for(i=0;i<=h;i++)
    {
    printlevelorder(root,i);
    }

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
  
	levelOrder(root);
    return 0;
}
