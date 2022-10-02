int height(node * root)
{
  if (root)
    return root->ht;
  else
    return -1;
}

void rotateRight(node * & root)
{
    node* temp = root->left;
    root->left = root->left->right;
    temp->right = root;
    root->ht = 1 + ((height(root->right) > height(root->left)) ? height(root->right) : height(root->left));
    temp->ht = 1 + ((height(temp->right) > height(temp->left)) ? height(temp->right) : height(temp->left));
    root = temp;
}

void rotateLeft(node * & root)
{
    node* temp = root->right;
    root->right = root->right->left;
    temp->left = root;
    root->ht = 1 + ((height(root->right) > height(root->left)) ? height(root->right) : height(root->left));
    temp->ht = 1 + ((height(temp->right) > height(temp->left)) ? height(temp->right) : height(temp->left));
    root = temp;
}

void rotateLeftRight(node * & root)
{
    rotateLeft(root->left);
    rotateRight(root);
}

void rotateRightLeft(node * & root)
{
    rotateRight(root->right);
    rotateLeft(root);
}
void insert1(node * & root, int val)
{
    if(root == NULL)
   {
       root = new node();
       root->val = val;
       root->left = NULL;
       root->right = NULL;
       root->ht = 0;
   }
   else if(root->val > val)
   {
       insert1(root->left, val);
       int balance = height(root->right) - height(root->left);
       int leftbalance = height(root->left->right) - height(root->left->left);
       if(balance == -2)
       {
           if(leftbalance == -1)
           {
               rotateRight(root);
           }
           if(leftbalance == +1)
           {
               rotateLeftRight(root);
           }
       }
   }

   else if(root->val < val)
   {
       insert1(root->right, val);
       int balance = height(root->right) - height(root->left);
       int rightbalance = height(root->right->right) - height(root->right->left);
       if(balance == 2)
       {
           if(rightbalance == 1)
           {
               rotateLeft(root);
           }
           if(rightbalance == -1)
           {
               rotateRightLeft(root);
           }
       }
   }
    root->ht = 1 + ((height(root->right) > height(root->left)) ? height(root->right) : height(root->left));
}

node * insert(node * root,int val)
{
   insert1(root, val);
   return root;
}
