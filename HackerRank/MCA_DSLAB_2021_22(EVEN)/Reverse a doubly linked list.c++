/*
 * Complete the 'reverse' function below.
 *
 * The function is expected to return an INTEGER_DOUBLY_LINKED_LIST.
 * The function accepts INTEGER_DOUBLY_LINKED_LIST llist as parameter.
 */

/*
 * For your reference:
 *
 * DoublyLinkedListNode {
 *     int data;
 *     DoublyLinkedListNode* next;
 *     DoublyLinkedListNode* prev;
 * };
 *
 */

DoublyLinkedListNode* reverse(DoublyLinkedListNode* llist) {

   struct DoublyLinkedListNode *prev,*curr,*next;
    curr=llist;
    prev=NULL;
    while(curr)
    {
        next=curr->next;
        curr->next=prev;
        curr->prev=next;
        if(next==NULL)break;
        prev=curr;curr=next;
    }
    curr->prev=NULL;return curr;


}
