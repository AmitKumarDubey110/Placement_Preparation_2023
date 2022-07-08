// Complete the has_cycle function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
bool has_cycle(SinglyLinkedListNode* head) {


    struct SinglyLinkedListNode* slow=head, * fast=head;
    while((slow!=NULL)&&(fast!=NULL)&&(fast->next!=NULL))
    {
        slow=slow->next;
        fast=fast->next->next;
        if(slow==fast)
            return 1;
    }
    return 0;
}
