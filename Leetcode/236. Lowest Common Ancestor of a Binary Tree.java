/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
class Solution {
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        if(root == null) return null;
        if(root == q || root == p) return root;
        boolean inLeft = contains(root.left, p);
        boolean inRight = contains(root.right, q);
        if((inLeft && inRight) || (!inLeft && !inRight)) return root;
        else if(inLeft && !inRight) return lowestCommonAncestor(root.left, p, q);
        else if(inRight && !inLeft) return lowestCommonAncestor(root.right, p, q);
        return null;
    }
    private boolean contains(TreeNode root, TreeNode node){
        if(root == null) return false;
        if(root == node) return true;
        return contains(root.left, node) || contains(root.right, node);
    }
}
