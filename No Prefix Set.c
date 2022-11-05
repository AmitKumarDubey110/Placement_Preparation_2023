#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


typedef struct node
{
    int is_word;
    struct node* children[10];
}*NODE;

NODE head=NULL;

NODE GetNewNode()
{
    NODE temp = (NODE)malloc(sizeof(struct node));
    temp->is_word = 0;
    int i;
    for(i=1;i<=5;i++)
        temp->children[i]=NULL;
    return temp;
}

void Insert(char word[])
{
    int digit;
    //printf("%d\n",rev);
    NODE temp;
    if(head==NULL)
    {
        head = GetNewNode();
    }
    temp=head;
    int i=0;
    while(word[i]!='\0')
    {
        digit = word[i];
        digit=digit-97;
        
        if(temp->children[digit]==NULL)
        {
            temp->children[digit]=GetNewNode();
        }
        temp = temp->children[digit];
        i++;
    }
    temp->is_word=1;
}

int Search(char word[])
{
    int digit,found=0;

    NODE temp = head;
    if(temp==NULL)return 0;
    int i=0;
    while(word[i]!='\0')
    {
        digit=word[i];
        digit=digit-97;
        if(temp->children[digit]==NULL)
            return 0;
        temp=temp->children[digit];
        if(temp->is_word==1)return 1;
        i++;
    }
    if(word[i]=='\0')//Check if we have scanned all characters....if we have, then prefix present       
        found=1;
   return found;
}



int main(void)
{
  char words[61];
  int number;
    int bad_set=0;
  scanf("%d",&number);
  while(number--)
  {
      scanf("%s",words);
      if(Search(words)==1)
      {
          printf("BAD SET\n%s",words);
          bad_set=1;
         break;
      }
      else
          Insert(words);
  }
    if(bad_set==0)
        printf("GOOD SET");
}
