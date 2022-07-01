/*
 * Complete the 'insertNodeAtPosition' function below.
 *
 * The function is expected to return an INTEGER_SINGLY_LINKED_LIST.
 * The function accepts following parameters:
 *  1. INTEGER_SINGLY_LINKED_LIST llist
 *  2. INTEGER data
 *  3. INTEGER position
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

SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* llist, int data, int position) {

    if((position-1)>0){
        insertNodeAtPosition(llist->next, data, position-1);
    }
    else{
        SinglyLinkedListNode* newnode = create_singly_linked_list_node(data);
        newnode->next = llist->next;
        llist->next = newnode;
    }
    return llist;
}
