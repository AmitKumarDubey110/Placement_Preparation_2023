int getHeight(struct node* root)
{

int counter_right = 0;
int counter_left = 0;   
    
    if (root == NULL)
    {
        return -1;
    }
    
         counter_left = getHeight(root->left);
        counter_left++;
         
         counter_right = getHeight(root->right);
         counter_right++; 
         
        if (counter_left > counter_right)
        {
            return counter_left;
        }
              
         return counter_right;     
}
