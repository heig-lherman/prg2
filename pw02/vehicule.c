/*
 ------------------------------------------------------------------------------
 Nom du fichier : vehicule.c
 Auteur(s)      : [redacted]
 Date creation  : 24.05.2022
 Description    : Implementation des fonctions de relatives
                  au traitement des véhicules.
 Compilateur    : gcc version 12.1.1 (Solus)
 ------------------------------------------------------------------------------
*/

#include <inttypes.h>
#include <stdlib.h>

#include "taxation.h"
#include "vehicule.h"

void triParking(Parking parking, size_t tailleParking) {
   qsort(parking, tailleParking, sizeof(Vehicule*), comparaisonTaxe);
}

int comparaisonTaxe(const void* a, const void* b) {
   Vehicule vehiculeA = *(Vehicule*) a;
   Vehicule vehiculeB = *(Vehicule*) b;

   double resultat = METHODES_CALCUL_TAXES[vehiculeA->etiquette](vehiculeA) -
                     METHODES_CALCUL_TAXES[vehiculeB->etiquette](vehiculeB);

   // Comparaison par ordre décroissant
   return resultat > 0 ? -1 : resultat < 0 ? 1 : 0;
}


Vehicule construireVoitureStandard(
      const char* marque,
      const char* plaque,
      uint16_t poids,
      uint16_t cylindree,
      uint16_t co2
) {
   return (Vehicule) {
         .plaque = plaque,
         .marque = marque,
         .etiquette = VOITURE_STANDARD,
         .type = {.voiture = {
               .poids = poids,
               .type = {.standard = {
                     .cylindree = cylindree,
                     .co2 = co2,
               }}
         }}
   };
}

Vehicule construireVoitureLuxe(
      const char* marque,
      const char* plaque,
      uint16_t poids,
      uint16_t puissance
) {
   return (Vehicule) {
         .plaque = plaque,
         .marque = marque,
         .etiquette = VOITURE_HAUT_DE_GAMME,
         .type = {.voiture = {
               .poids = poids,
               .type = {.luxe = {
                     .puissance = puissance,
               }}
         }}
   };
}

Vehicule construireCamionnette(
      const char* marque,
      const char* plaque,
      double volume
) {
   return (Vehicule) {
         .plaque = plaque,
         .marque = marque,
         .etiquette = CAMIONNETTE,
         .type = {.camionnette = {
               .volume = volume,
         }}
   };
}
