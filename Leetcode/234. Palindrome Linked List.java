/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
public class Solution {
    private ListNode left = null;
    public boolean isPalindrome(ListNode head) {
        if (head == null || head.next == null) {
            return true;
        }
        left = head;
        return isP(head);
    }
    private boolean isP(ListNode right) {
        if (right == null) {
            return true;
        }
        if (!isP(right.next)) {
            return false;
        }
        boolean result = left.val == right.val;
        left = left.next;
        return result;
    }
}
