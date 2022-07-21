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
class Solution {
    public ListNode reverseBetween(ListNode head, int m, int n) { 
        ListNode preRev = null;
        ListNode curr = head;
        int i = 1;
        while(i<m) { preRev = curr; curr = curr.next; i++; }
        
        ListNode end = curr;     
        ListNode pre = null; 
        while(i<=n) {
         ListNode temp = curr.next;
            curr.next = pre;
            pre = curr;
            curr = temp;
            i++;
        }
        
        end.next = curr;
        if(preRev != null) preRev.next = pre;
        return preRev == null ? pre: head;    
    }
}
