#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "colimacon.h"

struct borne {
  int haute;
  int droite;
  int basse;
  int gauche;
};

struct curseur {
  int col;
  int ligne;
};

typedef enum {
  HAUT,
  GAUCHE,
  BAS,
  DROITE
} direction_t ;

/**
 *  Print tableÒ
 */
void print_colimacon(int** table, int line, int col)
{
  for(int i_line=0; i_line < line; i_line++) {
      for(int i_col=0; i_col < col; i_col++) {
        printf(" %03d ", table[i_line][i_col] );
      }
      printf("\n");
  }
}

void delete_colimacon(int** table, int line, int col)
{
  for(int i_line; i_line<line; i_line++)
    free(table[i_line]);
  free(table);
}

static int** _malloc_colimacon(int line, int col) {

  int** table= malloc( line * sizeof(int *) );
  for(int i_line=0; i_line < line; i_line++)
    table[i_line] = malloc( col * sizeof(int));

  return table;
}

static void _iter_curseur( struct curseur* c, direction_t d ) {
  switch(d) {
    case HAUT:
      c->ligne--;
      break;
    case BAS:
      c->ligne++;
      break;
    case DROITE:
      c->col++;
      break;
    case GAUCHE:
      c->col--;
      break;
  }
}

static void _iter_borne( struct borne* borne, direction_t d) {
  switch(d) {
    case HAUT:
      borne->gauche++;
      break;
    case BAS:
      borne->droite--;
      break;
    case DROITE:
      borne->haute++;
      break;
    case GAUCHE:
      borne->basse--;
      break;
  }
}

static struct curseur _get_position_initiale(struct borne* borne, direction_t d) {
  struct curseur cur;
  switch(d) {
    case HAUT:
      cur.col = borne->gauche+1;
      cur.ligne = borne->basse-1;
      break;
    case BAS:
      cur.col =  borne->droite-1;
      cur.ligne = borne->haute+1;
      break;
    case GAUCHE:
      cur.col = borne->droite-1;
      cur.ligne = borne->basse-1;
      break;
    case DROITE:
      cur.col = borne->gauche+1;
      cur.ligne = borne->haute+1;
      break;
  }
  return cur;
}

static char _canWrite(struct curseur* cur, struct borne* bor) {
  return cur->col > bor->gauche && cur->col < bor->droite
    && cur->ligne > bor->haute && cur->ligne < bor->basse;
}


static int _ecriture_direction(int** tab, struct borne* bor, int* val,
  direction_t dir)
{
  struct curseur cur= _get_position_initiale(bor, dir);

  if(!_canWrite(&cur, bor)) {
      return -1;
  }

  do {
    tab[cur.ligne][cur.col]= *val;
    (*val)++;
    _iter_curseur(&cur, dir);
  } while(_canWrite(&cur, bor));

  _iter_borne(bor, dir);

  return 0;
}


int** colimacon(int line, int col) {

  struct borne borne;
  borne.gauche= -1;
  borne.haute= -1;
  borne.droite= col;
  borne.basse= line;
  int valeur=1;

  // initlisation du tableau
  int** table= _malloc_colimacon(line, col);

  while(1) {
    if(_ecriture_direction(table, &borne, &valeur, DROITE))
      break;
    if(_ecriture_direction(table, &borne, &valeur, BAS))
      break;
    if(_ecriture_direction(table, &borne, &valeur, GAUCHE))
      break;
    if(_ecriture_direction(table, &borne, &valeur, HAUT))
      break;
  }

  return table;
}

