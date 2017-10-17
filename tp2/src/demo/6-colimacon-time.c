/**
 * @file   src/demo/6-colimacon-time.c
 * @author Jérôme SKODA <contact@jeromeskoda.fr>
 * @date   Tue 17 Oct 2017 01:46:29 PM CEST
 * @brief  Demo 6
 */

#include "../colimacon/colimacon.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Programme de démonstration affichant le temps de génération
 *        Utilisation: colimacon [ligne] [col]
 */
int main(int argc, char** argv)
{
  clock_t start_t, end_t;
  float total_t;

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


  start_t = clock();

  int** table= colimacon(line, col);

  end_t = clock();

  delete_colimacon(table, line, col);

  total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
  printf("Temps: %f\n", total_t  );

  return 0;
}
