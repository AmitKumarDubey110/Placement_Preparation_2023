/*
 * Complete the 'removeDuplicates' function below.
 *
 * The function is expected to return an INTEGER_SINGLY_LINKED_LIST.
 * The function accepts INTEGER_SINGLY_LINKED_LIST llist as parameter.
 */

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */

SinglyLinkedListNode* removeDuplicates(SinglyLinkedListNode* llist) {

     struct SinglyLinkedListNode*temp1=llist;
    struct SinglyLinkedListNode*temp=llist->next;
    while(temp!=NULL)
    {
        if(llist->data==temp->data)
        {
            temp=temp->next;
            llist->next=temp;
        }
        else
        {
         llist=temp;
         temp=temp->next;
        }
    }
 return temp1;
}
