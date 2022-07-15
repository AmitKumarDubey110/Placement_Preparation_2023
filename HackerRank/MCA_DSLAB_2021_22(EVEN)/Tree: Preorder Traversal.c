/* you only have to complete the function given below.  
node is defined as  

struct node {
    
    int data;
    struct node *left;
    struct node *right;
  
};

*/
void preOrder( struct node *root) {

     if(root == NULL){
        return;
    }
    else{
    printf("%d ",root->data);
    preOrder(root->left);
    preOrder(root->right);
    }
}
