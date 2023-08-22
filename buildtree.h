#ifndef BUILD
#define BUILD
#include <stdbool.h>

typedef struct treeNode
{
  unsigned char letter;
  int freq;
  struct treeNode *left;
  struct treeNode *right;
} tree;

typedef struct linkNode
{
  tree *val;
  struct linkNode *next;
} node;

node *addNode(unsigned char letter, int freq, tree *left, tree *right, node *head);
bool readData(char *filename, int *charFreq, unsigned char *chars);
void swap(int *x, int *y);
void swapChar(unsigned char *x, unsigned char *y);
void quickSort(int *arr, unsigned char *chars, int min, int max);
node *buildList(unsigned char *chars, int *charFreq);
node *popHead(node *head);
void sortList(node *head);
tree *compressList(node *head, int *size);
void deleteTree(tree *tree);
bool printPost(tree * huffman, char * codeFile);

#endif
