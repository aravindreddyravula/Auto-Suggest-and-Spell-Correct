#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED

#define ALPHABET_SIZE 26
#include <stdbool.h>

typedef struct trien{
    bool isEOW;
    struct trien *next[ALPHABET_SIZE];
}TNode;

TNode *createTrieNode();
bool insertWordTrie(TNode *root, char word[]);
void printTrie(TNode *root, char word[], int last);
bool rinsertWordTrie(TNode *root, char word[]);
bool deleteWordFromTrie(TNode *root, char word[]);
bool hasWord(TNode *root, char word[]);
void printWordsWithPrefix(TNode *root, char prefix[]);
bool isLeaf(TNode *root);

#endif // TRIE_H_INCLUDED
