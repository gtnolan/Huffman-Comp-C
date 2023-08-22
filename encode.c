#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "encode.h"

void insertItem(char key, int *path, mapItem **table, int depth)
{
  int index = key;
  
  table[index] = malloc(sizeof(mapItem));

  table[index]->path = path;
  table[index]->key = key;
  table[index]->depth = depth;

  return;
}

bool encodeFile(char *fileIn, char *fileOut, mapItem **table)
{
  FILE *fR = fopen(fileIn, "r");
  if (fR == NULL)
  {
    return false;
  }
  FILE *fW = fopen(fileOut, "wb");
  if (fW == NULL)
  {
    return false;
  }

  char temp;
  unsigned char buffer = 0x00;
  int bitCt = 0;

  while ((temp = fgetc(fR)) != EOF)
  {
    int index = temp;
    for (int y = 0; y < table[index]->depth; y++)
    {
      if (bitCt == 8)
      {
        fwrite(&buffer, 1, 1, fW);
        bitCt = 0;
        buffer = 0x00;
      }
      buffer <<= 1;
      if (table[index]->path[y] == 1)
      {
        buffer |= 1;
      }
      
      bitCt++;
    }
  }
  if (bitCt != 0)
  {
    buffer <<= (8 - bitCt);
    fwrite(&buffer, 1, 1, fW);
  }

  fclose(fR);
  fclose(fW);
  return true;
}

void destroyMap(mapItem **map)
{
  for (int x = 0; x < 256; x++)
  {
    if (map[x] != NULL)
    {
      free(map[x] -> path);
      free(map[x]);
    }
  }
  free(map);
  return;
}

void getCodes(tree *root, int *path, int depth, mapItem **table)
{
  if (root->right == NULL && root->left == NULL)
  {
    int *val = malloc(sizeof(int) * (depth + 1));
    for (int x = 0; x < depth; x++)
    {
      val[x] = path[x];
    }
    insertItem(root->letter, val, table, depth);

    return;
  }
  path[depth] = 0;
  getCodes(root->left, path, depth + 1, table);
  path[depth] = 1;
  getCodes(root->right, path, depth + 1, table);
}
