#ifndef CONVERTIMGMAT_H
#define CONVERTIMGMAT_H

#include "type.h"
#include <string>

/*!
 * \brief convertMat : Elle permet de transformer une image au format .ppm P3 en une grille de jeu pour pacman
 * \details la fonction essai d'ouvrir l'image :<br>
 *      <ul><li>Si elle arrive à l'ouvrir, elle parcours le fichier en recuperant le code RGB
 *      de chaque pixel et en fonction de leur valeur rempli la grille avec les entiers naturels qui correspondent
 *      par exemple aux murs, au pacman, etc.</li>
 *      <li>Si elle n'arrive pas à l'ouvrir alors c'est que le fichier n'existe pas, on renvoie alors une matrice vide
 *      pour dire qu'il n'y a plus de fichier</li></ul>
 * \param[in] nomImg : nom de l'image à convertir en carte
 * \return la grille sous forme de vecteur de vecteur d'entier
 * @fn UIntMat convertMat (const std::string & nomImg);
 */
UIntMat convertMat (const std::string & nomImg);

/*!
 * \brief importAllPlot : Elle permet de recuperer toutes les cartes dans le fichier carte
 * \param[in_out] allPlot : c'est la map qui permet de stocker toutes les grilles
 * \param[in] baseName : c'est le nom réccurent de nos fichier
 * @fn void importAllPlot (plotHolder & allPlot, const string & baseName);
 */
void importAllPlot (plotHolder & allPlot, const string & baseName);

#endif // CONVERTIMGMAT_H
