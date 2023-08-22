#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "buildtree.h"

bool readData(char *filename, int *charFreq, unsigned char *chars)
{
  FILE *fR = fopen(filename, "r");
  if (fR == NULL)
    return false;

  int temp = 0;

  while ((temp = fgetc(fR)) != EOF)
  {
    charFreq[temp]++;
    chars[temp] = temp;
  }

  fclose(fR);
  return true;
}

void swap(int *x, int *y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

void swapChar(unsigned char *x, unsigned char *y)
{
  unsigned char temp = *x;
  *x = *y;
  *y = temp;
}

void quickSort(int *arr, unsigned char *chars, int min, int max)
{
  if (max - min < 1)
    return;
  int pivot = min;
  for (int x = min; x <= max; x++)
  {
    if (arr[x] >= arr[max])
    {
      swap(&arr[x], &arr[pivot]);
      swapChar(&chars[x], &chars[pivot]);
      pivot++;
    }
  }
  quickSort(arr, chars, min, pivot - 2);
  quickSort(arr, chars, pivot, max);
  return;
}

node *addNode(unsigned char letter, int freq, tree *left, tree *right, node *head)
{
  node *new = malloc(sizeof(node));
  tree *newVal = malloc(sizeof(tree));

  if (new == NULL)
  {
    exit(1);
  }

  newVal->right = right;
  newVal->left = left;
  newVal->letter = letter;
  newVal->freq = freq;

  new->next = head;
  new->val = newVal;

  return (new);
}

node *buildList(unsigned char *chars, int *charFreq)
{
  int x = 0;
  node *head = NULL;

  while (charFreq[x] != 0)
  {
    head = addNode(chars[x], charFreq[x], NULL, NULL, head);
    x++;
  }

  return head;
}

node *popHead(node *head)
{
  if (head == NULL || head->next == NULL)
    return NULL;
  node *temp = head->next->next;
  free(head->next);
  free(head);
  return (temp);
}

void sortList(node *head)
{
  node *temp = head->next;
  node *current = head;
  while (temp != NULL && (current->val->freq > temp->val->freq))
  {
    tree *append = current->val;
    current->val = temp->val;
    temp->val = append;
    temp = temp->next;
    current = current->next;
  }
}

tree *compressList(node *head, int *size)
{
  while (head->next != NULL)
  {
    tree *left = head->val;
    tree *right = head->next->val;
    head = popHead(head);
    head = addNode('h', left->freq + right->freq, left, right, head);
    sortList(head);
    *size = *size + 1;
  }
  tree *huffman = head->val;
  free(head);
  return (huffman);
}

void deleteTree(tree *tree)
{
  if (tree == NULL)
    return;
  deleteTree(tree->right);
  deleteTree(tree->left);
  free(tree);
}

static void printPost_helper(tree *huffman, FILE * fW) {
  if (huffman == NULL)
  {
    return;
  }

  printPost_helper(huffman->left, fW);
  printPost_helper(huffman->right, fW);
  if (huffman->left == NULL && huffman->right == NULL) 
  {
    fprintf(fW, "1%c", huffman->letter);
  } 
  else 
  {
    fprintf(fW, "0");
  }
}

bool printPost(tree * huffman, char * codeFile) 
{
  FILE * fW = fopen(codeFile, "wb");
  if (fW == NULL)
  {
    return false;
  }
  printPost_helper(huffman, fW);
  fprintf(fW, "0");
  fclose(fW);
  return true;
}
