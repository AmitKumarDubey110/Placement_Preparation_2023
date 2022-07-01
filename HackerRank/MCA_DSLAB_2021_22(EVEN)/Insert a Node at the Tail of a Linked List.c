// Complete the insertNodeAtTail function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* insertNodeAtTail(SinglyLinkedListNode* head, int data) {
 if (head == NULL) {
        return create_singly_linked_list_node(data);
    }
    
    SinglyLinkedListNode *node = head;
    while (node->next != NULL) {
        node = node->next;
    }
    node->next = create_singly_linked_list_node(data);
    return head;

}
