class Solution {
    public boolean isValidBST(TreeNode root) {
        if(root == null) return true; 
        Stack<TreeNode> stack = new Stack<>();
        TreeNode pre = null;
        while (root != null || !stack.isEmpty()){
            // left 
            while(root != null){
                stack.push(root);
                root = root.left;
            }
            root = stack.pop();
            // do
            if (pre!= null && pre.val >= root.val) return false;
            // record predecessor
            pre = root;
            // right
            root = root.right;
        }

        return true;
    }
}
