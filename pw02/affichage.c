/*
 ------------------------------------------------------------------------------
 Nom du fichier : affichage.c
 Auteur(s)      : [redacted]
 Date creation  : 24.05.2022
 Description    : Implémentation des fonctions d'affichage.
 Remarque(s)    : Permet uniquement un affichage dans la console.
 Compilateur    : gcc version 12.1.1 (Solus)
 ------------------------------------------------------------------------------
*/

#include <stdlib.h>

#include "affichage.h"
#include "taxation.h"

// Valeurs de mise en forme de l'affichage sous forme de tableau
static const uint8_t NOMBRE_COLONNES = 3;

// Définition de la largeur du tableau affiché dans la console
static const uint8_t LARGEUR_TABLEAU =
      NOMBRE_COLONNES * (LARGEUR_COLONNE + 3) + 1;

// Définition de la largeur de la colonne de description
static const uint8_t LONGUEUR_DESCRIPTION = LARGEUR_TABLEAU - 4;

// Définition des en-têtes du tableau affiché dans la console
static const char* const ENTETE[] = {
      "IMMATRICULATION",
      "MODELE",
      "TAXE ANNUELLE"
};

// Définition des noms relatifs au récapitulatif des taxes annuelles
static const char* const CALCULATION_NOM[] = {
      "Somme [en CHF]",
      "Moyenne [en CHF]",
      "Mediane [en CHF]",
      "Ecart-type [en CHF]"
};

void ligne(void) {
   for (size_t i = 0; i < LARGEUR_TABLEAU; ++i) {
      printf("%c", SEPARATEUR_LIGNE);
   }

   printf("\n");
}

void afficherVehicule(const Vehicule* v) {
   ligne();

   // Propriétés
   printf("%c %-*s ", SEPARATEUR_COLONNE, LARGEUR_COLONNE, v->plaque);
   printf("%c %-*s ", SEPARATEUR_COLONNE, LARGEUR_COLONNE, v->marque);
   printf(
         "%c %*.2lf CHF ",
         SEPARATEUR_COLONNE,
         LARGEUR_COLONNE - 4,
         METHODES_CALCUL_TAXES[v->etiquette](v)
   );
   printf("%c\n", SEPARATEUR_COLONNE);

   // Description
   const char* description = (METHODES_DESCRIPTION[v->etiquette])(v);
   if (description) {
      printf(
            "%c %-*s %c\n",
            SEPARATEUR_COLONNE,
            LONGUEUR_DESCRIPTION,
            description,
            SEPARATEUR_COLONNE
      );
   }
   free((void*) description);
   description = NULL;

   ligne();
}

void afficherVehicules(Parking park, size_t taille) {
   // en-tête
   ligne();
   for (size_t i = 0; i < NOMBRE_COLONNES; ++i) {
      printf("%c %-*s ", SEPARATEUR_COLONNE, LARGEUR_COLONNE, ENTETE[i]);
   }
   printf("%c\n", SEPARATEUR_COLONNE);
   ligne();

   // contenu
   for (size_t i = 0; i < taille; ++i) {
      afficherVehicule(park[i]);
      printf("\n");
   }
}

void afficherTaxes(ResultatRecapitulatifTaxes valeursCalculees) {
   printf("Statistiques des taxes annuelles dues:\n");

   // en-tête
   printf("| %*c |", LARGEUR_COLONNE, ' ');
   for (size_t i = 0; i < NB_TYPE_VEHICULE; ++i) {
      printf(" %*s |", LARGEUR_COLONNE, VEHICULE_TYPE_NOM[i]);
   }
   printf("\n");

   // contenu
   for (size_t i = 0; i < NB_RECAPITULATIF_TAXES; ++i) {
      printf("| %*s |", LARGEUR_COLONNE, CALCULATION_NOM[i]);
      for (size_t j = 0; j < NB_TYPE_VEHICULE; ++j) {
         printf(
               " %*.2lf |",
               LARGEUR_COLONNE,
               valeursCalculees[j][i]
         );
      }
      printf("\n");
   }
}

const char* descriptionVoitureStandard(const Vehicule* vehicule) {
   char* description = (char*) calloc(LONGUEUR_DESCRIPTION + 1, sizeof(char));
   if (!description) {
      return NULL;
   }

   snprintf(
         description, LONGUEUR_DESCRIPTION,
         "%s - %s %" PRIu16 " %s - %s %" PRIu16 " %s - %s %" PRIu16 " %s",
         VEHICULE_TYPE_NOM[vehicule->etiquette],
         "Cylindree:",
         vehicule->type.voiture.type.standard.cylindree,
         "cm3",
         "CO2:",
         vehicule->type.voiture.type.standard.co2,
         "g/km",
         "Poids:",
         vehicule->type.voiture.poids,
         "kg"
   );

   return description;
}

const char* descriptionVoitureHautDeGamme(const Vehicule* vehicule) {
   char* description = (char*) calloc(LONGUEUR_DESCRIPTION + 1, sizeof(char));
   if (!description) {
      return NULL;
   }

   snprintf(
         description, LONGUEUR_DESCRIPTION,
         "%s - %s %" PRIu16 " %s - %s %" PRIu16 " %s",
         VEHICULE_TYPE_NOM[vehicule->etiquette],
         "Puissance:",
         vehicule->type.voiture.type.luxe.puissance,
         "CV",
         "Poids:",
         vehicule->type.voiture.poids,
         "kg"
   );

   return description;
}

const char* descriptionCamionnette(const Vehicule* vehicule) {
   char* description = (char*) calloc(LONGUEUR_DESCRIPTION + 1, sizeof(char));
   if (!description) {
      return NULL;
   }

   snprintf(
         description, LONGUEUR_DESCRIPTION,
         "%s - %s %.2lf %s",
         VEHICULE_TYPE_NOM[vehicule->etiquette],
         "Volume",
         vehicule->type.camionnette.volume,
         "m3"
   );

   return description;
}
