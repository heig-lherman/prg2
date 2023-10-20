/*
 ------------------------------------------------------------------------------
 Nom du fichier : statistique.h
 Auteur(s)      : [redacted]
 Date creation  : 24.05.2022
 Description    : Module donnant accès à certaines fonctions de calcul
                  statistique.
 Remarques      : libm est nécessaire pour utiliser ce module (activé avec le
                  flag -lm dans les options du compilateur).
 Compilateur    : gcc version 12.1.1 (Solus)
 ------------------------------------------------------------------------------
*/

#ifndef PRG2_L2_PARKING_STATISTIQUE_H
#define PRG2_L2_PARKING_STATISTIQUE_H

#include <stddef.h>

double somme(const double* valeurs, size_t taille);
double moyenne(const double* valeurs, size_t taille);
double mediane(const double* valeurs, size_t taille);
double ecartType(const double* valeurs, size_t taille);

#endif //PRG2_L2_PARKING_STATISTIQUE_H
