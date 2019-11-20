#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

TNode *alphabetTrie[ALPHABET_SIZE];

void buildTrie(char ch){
    FILE *fp = fopen("words.txt","r");
    if(fp == NULL){
        printf("Error opening dictionary file");
        fclose(fp);
        return NULL;
    }
    TNode *root = createTrieNode();
    char temp[100];
    while(fscanf(fp,"%s",temp) == 1){
        if(temp[0] == ch){
            insertWordTrie(root,temp);
            break;
        }
    }
    while(fscanf(fp,"%s",temp) == 1){
        if(temp[0] == ch)
            insertWordTrie(root,temp);
        else
            break;
    }
    fclose(fp);
    alphabetTrie[ch - 'a'] = root;
}

void initializeAlphabetTrie(){
    int i;
    for(i = 0;i < ALPHABET_SIZE;i++){
        alphabetTrie[i] = NULL;
    }
}

char* convertToLowerCase(char *str){
    int i = 0;
    while(str[i] != '\0') {
        if(str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 'a' - 'A';
        i++;
    }
    return str;

}

int main()
{
    initializeAlphabetTrie();
    int words = 0;
    printf("How many words do you want to enter : ");
    scanf("%d", &words);
    while(words--){
        printf("\nEnter word : ");
        char *word = malloc(sizeof(char) * 100);
        fflush(stdin);
        scanf("%s",word);
        word = convertToLowerCase(word);
        int index = word[0] - 'a';
        if(alphabetTrie[index] == NULL)
            buildTrie(word[0]);
        printf("Auto Suggest output : \n");
        printWordsWithPrefix(alphabetTrie[index],word);
        free(word);
    }
    return 0;
}
