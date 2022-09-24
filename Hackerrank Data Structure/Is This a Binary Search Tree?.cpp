/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node struct is defined as follows:
	struct Node {
		int data;
		Node* left;
		Node* right;
	}
*/
enum comp {LESS, GREATER};
    bool checkBST(Node* root,int minVal, int maxVal ){
        if(root==0)
            return true;
        int nVal=root->data;
        if(nVal<=minVal || nVal>=maxVal)
            return false;
        return checkBST(root->left,minVal,nVal) && checkBST(root->right,nVal, maxVal);
    }
    bool checkBST(Node* root) {
        if(root==0)
            return true;
        return checkBST(root->left, -1, root->data) && checkBST(root->right,root->data, 10001);
    }
