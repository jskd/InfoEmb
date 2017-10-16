#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "colimacon.h"

/**
 * @brief Borne de remplissage
 */
struct borne {
  /// Borne haute
  int haute;
  /// Borne droite
  int droite;
  /// Borne basse
  int basse;
  /// Borne gauche
  int gauche;
};

/**
 * @brief Cursuer de postion de remplissage
 */
struct curseur {
  /// Position dans les collones
  int col;
  /// Position dans les lignes
  int ligne;
};

/**
 * @brief Les differentes direction de remplissage
 */
typedef enum {
  /// De bas vers le haut
  HAUT,
  /// De droite vers la gauche
  GAUCHE,
  /// De haut vers le bas
  BAS,
  /// De gauche vers la droite
  DROITE
} direction_t ;

/**
 *  @brief Affiche un tableau en colimaçon
 *  @param[in] table table à imprimmer
 *  @param[in] line nombre de ligne de la table
 *  @param[in] col nombre de colonnes de la table
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

/**
 *  @brief Supression d'un tableau
 *  @param[in] table table à supprimer
 *  @param[in] line nombre de ligne de la table
 *  @param[in] col nombre de colonnes de la table
 */
void delete_colimacon(int** table, int line, int col)
{
  for(int i_line; i_line<line; i_line++)
    free(table[i_line]);
  free(table);
}

/**
 *  @brief Allocation d'un tableau
 *  @param[in] line nombre de ligne de la table
 *  @param[in] col nombre de colonnes de la table
 *  @return pointeur vers le tableau
 */
static int** _malloc_colimacon(int line, int col) {

  int** table= malloc( line * sizeof(int *) );
  for(int i_line=0; i_line < line; i_line++)
    table[i_line] = malloc( col * sizeof(int));

  return table;
}

/**
 *  @brief Fonction d'iteration du curseur de remplissage en fonction
 *         de la direction
 *  @param[out] c curseur à déplacer
 *  @param[in] d direction
 */
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

/**
 *  @brief Fonction d'iteration de borne de remplissage en fonction
 *         de la direction
 *  @param[out] b borne
 *  @param[in] d direction
 */
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

/**
 * @brief Fonction de calcule de la positon initial pour remplir dans une direction
 * @param[in] borne 
 * @param[in] direction
 * @return curseur
 */
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

/**
 * @brief Calcule si l'ecriture est possible en fonction des bornes
 * @param[in] cur 
 * @param[in] bor
 * @return si true alors ecriture possible
 */
static char _canWrite(struct curseur* cur, struct borne* bor) {
  return cur->col > bor->gauche && cur->col < bor->droite
    && cur->ligne > bor->haute && cur->ligne < bor->basse;
}

/**
 * @brief Ecriture complete vers une direction
 * @param[in] tab tableau à remplir
 * @param[in] bor borne du tableau 
 * @param[in] val valeur à entrer
 / @return si -1 aucune écriture sinon 0
 */
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

/**
 * @brief Allocation d'un tableau et remplissage en colimacon
 * @param[in] line nombre de ligne
 * @param[in] col nombre de colonne
 * @return retourne un pointer vers le tableau
 */
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

