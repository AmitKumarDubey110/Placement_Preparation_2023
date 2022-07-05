class Solution {
    public List<Integer> inorderTraversal(TreeNode root) {
        List<Integer> rst = new ArrayList<>();
        Stack<TreeNode> stack = new Stack<>();
        TreeNode node = root;
        addLeftPath(stack, node); // Dive deep to left path till leaf
        
        while (!stack.isEmpty()) {
            node = stack.pop(); // Add to rst
            rst.add(node.val);
            // Add node.right and all its left children
            if (node.right != null) {
                node = node.right;
                addLeftPath(stack, node);
            }
        }
        return rst;
    }
    
    private void addLeftPath(Stack<TreeNode> stack, TreeNode node) {
        while (node != null) {
            stack.push(node);
            node = node.left;
        }
    }
}
