#include "../colimacon/colimacon.h"
#include <stdio.h>
#include <stdlib.h>

static const int _line= 2;
static const int _col= 10;

/**
 * @brief Programme de démonstration
 *        Taille 2x10     
 */
int main(int argc, char** argv)
{

  int** table= colimacon(_line, _col);

  print_colimacon(table, _line, _col);

  delete_colimacon(table, _line, _col);

  return 0;
}
