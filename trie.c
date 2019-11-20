#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "trie.h"

TNode *createTrieNode(){
    TNode *newNode = malloc(sizeof(TNode));
    newNode->isEOW = false;
    int i;
    for(i = 0;i < ALPHABET_SIZE;i++)
        newNode->next[i] = NULL;
    return newNode;
}
bool insertWordTrie(TNode *root, char word[]){
    int i = 0, index;
    while(word[i] != '\0'){
        index = word[i] - 'a';
        if(root->next[index] == NULL)
            root->next[index] = createTrieNode();
        root = root->next[index];
        i++;
    }
    if(root->isEOW == true)
        return false;
    root->isEOW = true;
    return true;
}
bool rinsertWordTrie(TNode *root, char word[]){
    if(word[0] == '\0'){
        if(root->isEOW == true)
            return false;
        root->isEOW = true;
        return true;
    }
    int index = word[0] - 'a';
    if(root->next[index] == NULL)
        root->next[index] = createTrieNode();
    return rinsertWordTrie(root->next[index],word+1);
}
void printTrie(TNode *root,char word[],int last){
    assert(root != NULL);
    int i = 0;
    if(root->isEOW)
        printf("%s\n",word);
    while(i < ALPHABET_SIZE){
        if(root->next[i] != NULL){
            word[last] = 'a' + i;
            word[last + 1] = '\0';
            printTrie(root->next[i],word,last+1);
        }
        i++;
    }
}
bool isLeaf(TNode *root){
    int i;
    for(i = 0;i < ALPHABET_SIZE; i++)
        if(root->next[i] != NULL)
            return false;
    return true;
}
bool deleteWordFromTrie(TNode *root, char word[])
{
    if(root==NULL)
        return false;

    if(word[0]=='\0')
    {
        if(root->isEOW==false)
            return false;

        if(isLeaf(root))
        {
            free(root);
            return true;
        }
        else
        {
            root->isEOW = false;
            return false;
        }

    }

    int idx = word[0] - 'a';
    if(deleteWordFromTrie(root->next[idx], word+1))
    {
        root->next[idx] = NULL;
        if(isLeaf(root) && root->isEOW==false)
        {
            free(root);
            return true;
        }
    }
    //Dummy return is the following
    return false;
}
bool hasWord(TNode *root, char word[]){
    int i = 0, index;
    while(word[i] != '\0'){
        index = word[i] - 'a';
        if(root->next[index] != NULL)
            root = root->next[index];
        else
            return false;
        i++;
    }
    return root->isEOW;
}
void printWordsWithPrefix(TNode *root, char prefix[]){
    int i = 0, index;
    char *some_array = malloc(1000*sizeof(char));
    while(prefix[i] != '\0'){
        index = prefix[i] - 'a';
        root = root->next[index];
        some_array[i] = prefix[i];
        i++;
    }
    some_array[i] = prefix[i];
    printTrie(root,some_array,i);
}
