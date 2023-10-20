/*
 ------------------------------------------------------------------------------
 Nom du fichier : statistique.c
 Auteur(s)      : [redacted]
 Date creation  : 24.05.2022
 Description    : Implementation des fonctions de relatives
                  au calcul statistique.
 Compilateur    : gcc version 12.1.1 (Solus)
 ------------------------------------------------------------------------------
*/

#include <math.h>

#include "statistique.h"

#define CARRE(x) ((x) * (x))

double somme(const double* valeurs, size_t taille) {
   double somme = 0.00;
   if (!taille) {
      return somme;
   }

   for (size_t i = 0; i < taille; ++i) {
      somme += *(valeurs + i);
   }

   return somme;
}

double moyenne(const double* valeurs, size_t taille) {
   if (!taille) {
      return 0.00;
   }

   return somme(valeurs, taille) / (double) taille;
}

double mediane(const double* valeurs, size_t taille) {
   if (!taille) {
      return 0.00;
   }

   if (taille % 2) {
      return valeurs[taille / 2];
   }

   return (valeurs[(size_t) ceil((double) taille / 2)] +
           valeurs[(size_t) ceil((double) taille / 2) - 1]) / 2;
}

double ecartType(const double* valeurs, size_t taille) {
   if (!taille) {
      return 0.00;
   }

   double ecartType = 0;
   for (size_t i = 0; i < taille; ++i) {
      ecartType += CARRE(moyenne(valeurs, taille) - valeurs[i]);
   }

   return sqrt(ecartType / (double) taille);
}
