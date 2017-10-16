#include "../colimacon/colimacon.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Programme de démonstration sans print
 *        Utilisation: colimacon [ligne] [col]  
 */
int main(int argc, char** argv)
{
  if(argc < 3)
  {
    printf("Utilisation: colimacon [ligne] [col]\n");
    return -1;
  }
  int line= atoi(argv[1]);
  int col= atoi(argv[2]);

  if(line < 0 || col < 0)
  {
    printf("Erreur: col ouline doivent être positif");
    return -1;
  }

  int** table= colimacon(line, col);

  delete_colimacon(table, line, col);

  return 0;
}
