// Complete the compare_lists function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
bool compare_lists(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {

struct SinglyLinkedListNode *t1;
    struct SinglyLinkedListNode *t2;
    t1=head1;t2 = head2;
    if(t1==NULL && t2==NULL)
        return 1;
    if(t1 != NULL && t2 == NULL)
        return 0;
     if(t1 == NULL && t2 != NULL)
        return 0;
    else
    {
        while(t1->next != NULL && t2->next != NULL)
        {
            if(t1->data == t2->data)
            {
                t1 = t1->next;
                t2 = t2->next;
            }
            else return 0;
        }
        if(t1->next == NULL && t2->next == NULL)
            return 1;
        else return 0;
    }
}
