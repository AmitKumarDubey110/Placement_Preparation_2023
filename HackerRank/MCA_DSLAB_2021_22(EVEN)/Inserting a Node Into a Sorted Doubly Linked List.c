/*
 * Complete the 'sortedInsert' function below.
 *
 * The function is expected to return an INTEGER_DOUBLY_LINKED_LIST.
 * The function accepts following parameters:
 *  1. INTEGER_DOUBLY_LINKED_LIST llist
 *  2. INTEGER data
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

DoublyLinkedListNode* sortedInsert(DoublyLinkedListNode* llist, int data) {

     DoublyLinkedListNode *New = create_doubly_linked_list_node(data);
    if (!llist)
    {
        llist = New;
        return llist;
    }
    else if (data < (llist->data))
    {
        New->next = llist; 
        llist->prev = New;
        New->prev = NULL;
        llist = New;
        return llist; 
    }
    else 
    {
        DoublyLinkedListNode *temp = llist;
        while ( ((temp->next) != NULL) && ((temp->next->data) <= data))
            temp = temp->next;
        
        if (temp->next != NULL)
        {
            DoublyLinkedListNode *next = temp->next;
            next->prev = New;
            New->next = next;
        }
        else 
            New->next = NULL;
            
        temp->next = New;
        New->prev = temp;
    }
    return llist; 
}
