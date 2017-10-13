#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct cursor {
  int x;
  int y;
};


/**
 *  Print tableÒ
 */
void print_table(int** table, int cols, int rows)
{
  for(int y=0; y<rows; y++) {
      for(int x=0; x<cols; x++) {
        printf(" %03d ", table[x][y]);
      }
      printf("\n");
  }
}

/**
 * Generate table
 * La flemme de factoriser (write right, down, left, top)
 */
void generate_table(int** table, int cols, int rows)
{
  struct cursor pos= {0,0};

  int x=-1;
  int y=-1;
  int count=1;
  char write;

    while(1) {

    // write right
      write=0;

    x++; // go to first case
    y++; // cancel increment of previous move

    while(table[x][y] == 0 && x < cols && y < rows) {
      table[x][y]= count; // on ecrit si la case est vide
      count++;
      x++; // passage a la case suivante
      write= 1;
    }

    if(!write)
      return; // rien ecrit c'est terminé

      // write down
      x--;// cancel increment of previous move
      y++;// go to first case
      write=0;

    while(table[x][y] == 0 && x < cols && y < rows) {
      table[x][y]= count;
      count++;
      y++;
      write= 1;
    }

    if(!write)
      return;

      // write left
      x--; // go to first case
      y--; // cancel increment of previous move
      write=0;

    while(table[x][y] == 0 && x < cols && y < rows) {
      table[x][y]= count;
      count++;
      x--;
      write= 1;
    }

    if(!write)
      return;

      // write left

      x++; // cancel increment of previous move
      y--; // go to first case

      write=0;

    while(table[x][y] == 0 && x < cols && y < rows) {
      table[x][y]= count;
      count++;
      y--;
      write= 1;
    }

    if(!write)
      return;
    }

}

// main
int main(int argc, char** argv)
{
  if(argc < 3)
  {
    printf("Utilisation: colimacon [colonnes] [lignes]\n");
    return -1;
  }

  int cols= atoi(argv[1]);
  int rows= atoi(argv[2]);
  cols++;
  rows++;

  if(cols < 0 || rows < 0)
  {
    printf("Erreur les colonnes et les lignes doivent être positif.\n");
    return -1;
  }

  int** table= (int**) malloc(cols*sizeof(int *));

  for(int i=0; i<cols; i++) {
    table[i]= (int*) malloc(rows*sizeof(int));
    memset(table[i], 0, sizeof(rows*sizeof(int)));
  }



  generate_table( table, rows, cols);
  print_table( table, rows, cols);

  for(int i=0; i<cols; i++)
    free(table[i]);
  free(table);
}
