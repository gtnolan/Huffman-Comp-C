#ifndef ENCODE
#define ENCODE
#include <stdbool.h>
#include "buildtree.h"

typedef struct codeNode
{
  int *path;
  char key;
  int depth;
} mapItem;

void insertItem(char key, int *path, mapItem **table, int depth);
bool encodeFile(char *fileIn, char *fileOut, mapItem **table);
void destroyMap(mapItem **map);
void getCodes(tree *root, int *path, int depth, mapItem **table);

#endif
