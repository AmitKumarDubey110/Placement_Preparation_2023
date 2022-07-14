/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) {
 *         val = x;
 *         next = null;
 *     }
 * }
 */
public class Solution {
    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        if(headA == null || headB == null) return null;
        ListNode a = headA;
        ListNode b = headB;
        int count = 0;
        while(a != b){
            if(count == 2) break;
            if(a == null) count ++;
            a = a == null ? headB : a.next;
            b = b == null ? headA : b.next;
        }
        if(a != b) return null;
        else
            return a;
    }
}
