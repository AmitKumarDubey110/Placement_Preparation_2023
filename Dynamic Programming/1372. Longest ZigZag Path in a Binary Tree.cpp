/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int ans = 0;
    unordered_map<TreeNode*,pair<int,int>> dp;
    int helper(TreeNode* root,int dir)
    {
        if(dp.count(root)>0 and dp[root].first==dir)
            return dp[root].second;
        
        if(root==NULL)
            return 0;
        if(dir==-1)
        {
            int temp = 1+helper(root->right,1);
            dp[root].first = 1;
            dp[root].second = temp;
            return temp;
        }
        else
        {
            int temp = 1+helper(root->left,-1);
            dp[root].first = -1;
            dp[root].second = temp;
            return temp;
        }
    
        return 0;
    }
    void caller(TreeNode* root,int dir)
    {
        if(root==NULL)
            return;
        
        if(dp.count(root->right)==0 and dp[root].first!=dir)
            ans = max(ans,helper(root->right,1));
        
        caller(root->right,1);
        
        if(dp.count(root->left)==0 and dp[root].first!=dir)
            ans = max(ans,helper(root->left,-1));
        
        caller(root->left,-1);
    }
    int longestZigZag(TreeNode* root) 
    {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        
        caller(root,1);
        return ans;
    }
};
