// Complete the mergeLists function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* mergeLists(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {

 SinglyLinkedList *newHead = malloc(sizeof(SinglyLinkedList));
    newHead->head = NULL;
    newHead->tail = NULL;
    
    while(head1 != NULL && head2 != NULL){
        if(head1->data > head2->data){
            insert_node_into_singly_linked_list(&newHead, head2->data);
            head2 = head2->next;
        }
        else if(head1->data < head2->data){
            insert_node_into_singly_linked_list(&newHead, head1->data);
            head1 = head1->next;
        }
        else{
            insert_node_into_singly_linked_list(&newHead, head1->data);
            insert_node_into_singly_linked_list(&newHead, head2->data);
            head1 = head1->next;
            head2 = head2->next;
        }
    }
    
    while(head1 != NULL){
        insert_node_into_singly_linked_list(&newHead, head1->data);
        head1 = head1->next;
    }
    while(head2 != NULL){
        insert_node_into_singly_linked_list(&newHead, head2->data);
        head2 = head2->next;
    }
    
    return newHead->head;
}
