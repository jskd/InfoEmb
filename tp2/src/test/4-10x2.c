/**
 * @file   src/test/4-10x2.c
 * @author Jérôme SKODA <contact@jeromeskoda.fr>
 * @date   Tue 17 Oct 2017 01:46:29 PM CEST
 * @brief  Test 4
 */
#include "../colimacon/colimacon.h"
#include <stdio.h>
#include <stdlib.h>

static const int _line= 10;
static const int _col= 2;
/**
 * @brief Programme de test
 *        Taille 10x2
 */
int main(int argc, char** argv)
{

  int** table= colimacon(_line, _col);

  print_colimacon(table, _line, _col);

  delete_colimacon(table, _line, _col);

  return 0;
}
