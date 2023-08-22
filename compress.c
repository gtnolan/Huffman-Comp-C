#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "buildtree.h"
#include "encode.h"

int main(int argc, char **argv)
{
  if (argc != 4)
    return EXIT_FAILURE;

  int charFreq[256] = {0};
  unsigned char chars[256];

  if (readData(argv[1], charFreq, chars) == false)
  {
    return EXIT_FAILURE;
  }
  quickSort(charFreq, chars, 0, 255);
  node *head = buildList(chars, charFreq);
  int size = 1;
  tree *huffman = compressList(head, &size);

  mapItem **table = malloc(sizeof(mapItem *) * 256);
  for (int x = 0; x < 256; x++)
  {
    table[x] = NULL;
  }

  int *path = malloc(sizeof(int) * (size * 2));
  getCodes(huffman, path, 0, table);

  if (printPost(huffman, argv[3]) == false)
  {
    return EXIT_FAILURE;
  }

  deleteTree(huffman);
  free(path);

  if (encodeFile(argv[1], argv[2], table) == false)
  {
    return EXIT_FAILURE;
  }
  

  destroyMap(table);
  return EXIT_SUCCESS;
}
