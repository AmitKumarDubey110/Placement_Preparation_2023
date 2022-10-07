#include <stdio.h>

#define MAX_N 100000

int heap[MAX_N], heap_len;

int Q;
int order, num;

void insert(int number)
{
    int parent, pos;
    int temp;
    heap[heap_len++] = number;
    pos = heap_len - 1;
    parent = pos / 2;
    while(1)
    {
        if(heap[parent] > heap[pos])
        {
            temp = heap[pos];
            heap[pos] = heap[parent];
            heap[parent] = temp;
            pos = parent;
            parent = pos / 2;
        }
        else break;
    }
}

void heap_adjust(int index)
{
    int left, right, min, temp;
    while(1){
        
    left = 2 * index + 1;
    right = 2 * (index + 1);
    min = index;
    if(left < heap_len && heap[index] > heap[left])
        min = left;
    if(right < heap_len && heap[min] > heap[right])
        min = right;
    
    if(min != index)
    {
        temp = heap[min];
        heap[min] = heap[index];
        heap[index] = temp;
        index = min;
    }
    else break;
    
    }
    
}

void delete(int number)
{
    int index;
    int i, temp, pos;
    for(i = 0; i < heap_len; i++)
    {
        if(heap[i] == number)
        {
            index = i;
            pos = heap_len - 1;
            heap_len--;
            if(index < pos)
            {
                heap[index] = heap[pos];
                
                heap_adjust(index);
            }
            
            break;
        }
    }
   
}

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int i;
    scanf("%d", &Q);
    heap_len = 0;
    for(i = 0; i < Q; i++)
    {
        scanf("%d", &order);
        if(order == 1)
        {
            scanf("%d", &num);
            insert(num);
        }
        else if(order == 2)
        {
            scanf("%d", &num);
            delete(num);
        }    
        else if(order == 3)
        {
            printf("%d\n", heap[0]);
        }
    }
    
    
    return 0;
}
