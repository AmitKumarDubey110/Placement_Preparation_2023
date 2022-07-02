/*
 * Complete the 'reversePrint' function below.
 *
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

void reversePrint(SinglyLinkedListNode* llist) {

    SinglyLinkedListNode* current=llist,*next,*prev=NULL;
    while(current!=NULL)
    {   next=current->next;
        current->next=prev;
        prev=current;
        current=next;
     
       
        
    }
    llist=prev;
    SinglyLinkedListNode* temp=llist;
    while(temp!=NULL)
    {
        printf("%d\n",temp->data);
        temp=temp->next;
    }
}
