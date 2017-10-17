/**
 * @file   src/test/7-1000x1000.c
 * @author Jérôme SKODA <contact@jeromeskoda.fr>
 * @date   Tue 17 Oct 2017 01:46:29 PM CEST
 * @brief  Test 1000
 */

#include "../colimacon/colimacon.h"
#include <stdio.h>
#include <stdlib.h>

static const int _line= 1000;
static const int _col= 1000;

/**
 * @brief Programme de test (sans print)
 *        Taille 1000x1000
 */
int main(int argc, char** argv)
{

  int** table= colimacon(_line, _col);

  delete_colimacon(table, _line, _col);

  return 0;
}
