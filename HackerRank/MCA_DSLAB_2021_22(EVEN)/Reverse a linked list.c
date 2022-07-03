/*
 * Complete the 'reverse' function below.
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

SinglyLinkedListNode* reverse(SinglyLinkedListNode* llist) {

    struct SinglyLinkedListNode* new_llist = NULL;
    struct SinglyLinkedListNode* temp;
    
    while(llist != NULL){
        temp = llist->next;
        llist->next = new_llist;
        new_llist = llist;
        llist = temp;
    }
    
    return new_llist;
}
