/**
 * @file   src/colimacon/colimacon.h
 * @author Jérôme SKODA <contact@jeromeskoda.fr>
 * @date   Tue 17 Oct 2017 01:46:29 PM CEST
 * @brief  Colimaçon header
 */

/**
 * @brief Allocation d'un tableau et remplissage en colimacon
 * @param[in] line nombre de ligne
 * @param[in] col nombre de colonne
 * @return retourne un pointer vers le tableau
 */
int ** colimacon(int line, int col);

/**
 *  @brief Affiche un tableau en colimaçon
 *  @param[in] table table à imprimmer
 *  @param[in] line nombre de ligne de la table
 *  @param[in] col nombre de colonnes de la table
 */
void print_colimacon(int** table, int line, int col);

/**
 *  @brief Supression d'un tableau
 *  @param[in] table table à supprimer
 *  @param[in] line nombre de ligne de la table
 *  @param[in] col nombre de colonnes de la table
 */
void delete_colimacon(int** table, int line, int col);
