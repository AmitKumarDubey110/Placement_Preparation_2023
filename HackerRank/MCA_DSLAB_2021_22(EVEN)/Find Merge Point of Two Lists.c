// Complete the findMergeNode function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
int findMergeNode(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {

   int countA = 0;
    int countB = 0;
    struct SinglyLinkedListNode *tempHeadA, *tempHeadB;
    tempHeadA = head1;
    tempHeadB = head2;
    
    while(tempHeadA != NULL){
        countA++;
        tempHeadA = tempHeadA->next;
    }
    while(tempHeadB != NULL){
        countB++;
        tempHeadB = tempHeadB->next;
    }
    
    // printf("%d %d", countA,countB);
    int biggerNodeExtraNodes = abs(countA - countB);
    // printf("%d", biggerNodeExtraNodes);
    while(biggerNodeExtraNodes--){
         printf("33333333333");
        if(countA > countB){
            head1 = head1->next;
        }
        else{
             head2 = head2->next;
        }
    }
    while(head1 != NULL){
        printf("asdfghjklpoiuytredxdcfgh");
        if(head1 == head2){
            return head1->data;
        }
        else{
             head1 = head1->next;
             head2 = head2->next;
        }
    }
    return 1; 

}
