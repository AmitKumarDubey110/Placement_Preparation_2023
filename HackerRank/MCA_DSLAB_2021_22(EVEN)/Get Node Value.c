/*
 * Complete the 'getNode' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_SINGLY_LINKED_LIST llist
 *  2. INTEGER positionFromTail
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

int getNode(SinglyLinkedListNode* llist, int positionFromTail) {

    int count = 0;
    
    SinglyLinkedListNode *ptr = llist;
    
    while(ptr!=NULL)
    {
        ++count;
        ptr=ptr->next;
    }
    
    count = count-positionFromTail;
    
    ptr=llist;
    --count;
    
    while(count!=0)
    {
        --count;
        ptr=ptr->next;
    }
    
    return ptr->data;
}
