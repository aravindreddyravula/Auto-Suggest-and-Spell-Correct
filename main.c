#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define ALPHABET_SIZE 26
typedef struct n
{
    bool isEndOfWord;
    struct n *next[ALPHABET_SIZE];
}node;
node* createNode()
{
    int i;
    node *newNode;
    newNode = (node*)malloc(sizeof(node));
    newNode->isEndOfWord = false;
    for(i=0;i<ALPHABET_SIZE;i++)
        newNode->next[i] = NULL;
    return newNode;
}
node *root;

void insertWord(char word[])
{
    node *temp = root;
    int i;
    for(i=0; word[i]!='\0';i++)
    {
        int idx = word[i]-'a';
        if(temp->next[idx] == NULL)
        {
            temp->next[idx] = createNode();
        }
        temp = temp->next[idx];
    }
    temp->isEndOfWord = true;
   // printf("\nInserted %s",word);
}
bool hasWord(char word[])
{
    int idx,i;
    node *temp = root;
    for(i=0;word[i]!='\0';i++)
    {
        int idx = word[i]-'a';
        if(temp->next[idx]==NULL)
            return false;
        temp = temp->next[idx];
    }
    return temp->isEndOfWord;

}
void replace(char mw[])
{
    int i;
    char j,c;
    for(i=0;mw[i]!=NULL;i++)
    {
        c=mw[i];
        for(j='a';j<='z';j++)
        {
            mw[i]=j;
            if(hasWord(mw) == true)
                printf("Replace :%s\n",mw);
        }
        mw[i]=c;
    }
}
void insert(char mw[])
{
    int i;
    int j;
    char mw2[200];
    for(i=0;i<=strlen(mw);i++)
    {
            strcpy(mw2,mw);
            for(j=strlen(mw)-1;j>=i;j--)
                mw2[j+1]=mw2[j];
            for(j='a';j<='z';j++)
            {
                mw2[i]=j;
                if(hasWord(mw2))
                    printf("\n%s",mw2);
            }
    }

}
void insertion(char mw[])
{
    int len= strlen(mw);
    int i;
    char *nw = malloc(len+2);
    sprintf(nw,"%c%s",'~',mw);
    for(i=0; i<=len; i++)
    {
        char ch;
        for(ch='a'; ch<='z'; ch++)
        {
            nw[i] = ch;
            if(hasWord(nw)==true)
                printf("\nInsertion : %s",nw);
        }
        nw[i] = nw[i+1];
    }
    free(nw);
}
int main()
{
    char mw[200];

    root=createNode();
  //  insertion(mw);
  FILE *fp = fopen("dict.txt","r");
  if(fp==NULL)
        printf("File not found");
  while(!feof(fp))
  {
      fscanf(fp,"%s",mw);
      insertWord(mw);
  }
  printf("\nEnter the missplet word :");
    scanf("%s",mw);
    replace(mw);
    insert(mw);
    return 0;
}
