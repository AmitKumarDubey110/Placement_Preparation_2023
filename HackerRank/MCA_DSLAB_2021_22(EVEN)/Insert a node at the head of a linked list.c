// Complete the insertNodeAtHead function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* insertNodeAtHead(SinglyLinkedListNode* llist, int data) {
 
    SinglyLinkedListNode* new = malloc(sizeof(SinglyLinkedListNode));
    new->data = data;
    
    if(llist == NULL){
        llist = new;
        new->next = NULL;
        return llist; 
    }
    
    new-> next = llist;
    llist = new;
    return llist;

}
