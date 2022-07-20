/* you only have to complete the function given below.  
node is defined as  

struct node {
    
    int data;
    struct node *left;
    struct node *right;
  
};

*/
void levelOrder( struct node *root) {

struct node *queue[500];
    int queue_head, queue_end;
    struct node *head;
      
    if (!root)
        return;
    
    queue[0] = root;
    queue_head = 0;
    queue_end = 1;
    
    while (queue_head < queue_end)
    {
        head = queue[queue_head++];
        fprintf(stdout, "%d ", head->data);
        if (head->left)
            queue[queue_end++] = head->left;
        if (head->right)
            queue[queue_end++] = head->right;
    }
}
