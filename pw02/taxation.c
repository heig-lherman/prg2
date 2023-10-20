/*
 ------------------------------------------------------------------------------
 Nom du fichier : taxation.c
 Auteur(s)      : [redacted]
 Date creation  : 24.05.2022
 Description    : Implémentation des fonctions de calculation des divers taxes.
 Compilateur    : gcc version 12.1.1 (Solus)
 ------------------------------------------------------------------------------
*/

#include "statistique.h"
#include "taxation.h"
#include "vehicule.h"

// diviseur pour la transformation d'unité de kg vers tonne
const uint16_t KG_VERS_TONNE = 1000;

double taxeBase(const Vehicule* v) {
   return TAXE_DE_BASE[v->etiquette];
}

double taxeVoitureStandard(const Vehicule* v) {
   if (v->type.voiture.type.standard.cylindree >= LIMITES_CYLINDREE) {
      return taxeBase(v) +
             v->type.voiture.type.standard.cylindree *
             TAXE_COEF_GROSSE_CYLINDREE;
   }

   if (v->type.voiture.type.standard.co2 < LIMITES_CO2) {
      return taxeBase(v) + TAXE_CO2_PETITE;
   }

   return taxeBase(v) + TAXE_CO2_GRANDE;
}

double taxeVoitureHautDeGamme(const Vehicule* v) {
   if (v->type.voiture.type.luxe.puissance <= LIMITE_PUISSANCE) {
      return taxeBase(v) + TAXE_PUISSANCE_PETITE;
   }

   return taxeBase(v) +
          TAXE_PUISSANCE_GRANDE +
          TAXE_COEF_PUISSANCE_GRANDE *
          (double) v->type.voiture.poids /
          KG_VERS_TONNE;
}

double taxeCamionnette(const Vehicule* v) {
   return taxeBase(v) + TAXE_POIDS * v->type.camionnette.volume;
}

ResultatRecapitulatifTaxes recapitulatifTaxesAnnuelles(
      Parking park,
      size_t taille
) {
   // Tableau de NB_TYPE_VEHICULE dimension permettant de
   // stocker temporairement les taxes annuelles des véhicules
   double* taxesOrdonnees = (double*) calloc(
         taille * NB_TYPE_VEHICULE,
         sizeof(double)
   );
   if (!taxesOrdonnees) {
      return NULL;
   }

   // Tableau permettant de stocker le nombre de véhicules par types
   size_t nombreVehiculeParType[NB_TYPE_VEHICULE] = {0};

   // Récupération des taxes annuelles des véhicules
   for (size_t i = 0; i < taille; ++i) {
      size_t position = taille * park[i]->etiquette +
                        nombreVehiculeParType[park[i]->etiquette];

      taxesOrdonnees[position] = METHODES_CALCUL_TAXES[park[i]->etiquette](
            park[i]
      );

      ++nombreVehiculeParType[park[i]->etiquette];
   }

   // Tableau de NB_TYPE_VEHICULE dimension permettant de stocker
   // dynamiquement les récap. des taxes annuelles des véhicules
   double (* valeursCalculees)[NB_RECAPITULATIF_TAXES];
   valeursCalculees = (double (*)[NB_RECAPITULATIF_TAXES]) calloc(
         NB_TYPE_VEHICULE,
         sizeof(*valeursCalculees)
   );
   if (!valeursCalculees) {
      return NULL;
   }

   // Récupération des récap. des taxes annuelles des véhicules
   for (size_t i = 0; i < NB_TYPE_VEHICULE; ++i) {
      size_t positionDebut = i * taille;
      const double* premiereTaxe = &taxesOrdonnees[positionDebut];
      (valeursCalculees[i][SOMME]) = somme(
            premiereTaxe,
            nombreVehiculeParType[i]
      );
      (valeursCalculees[i][MOYENNE]) = moyenne(
            premiereTaxe,
            nombreVehiculeParType[i]
      );
      (valeursCalculees[i][MEDIANE]) = mediane(
            premiereTaxe,
            nombreVehiculeParType[i]
      );
      (valeursCalculees[i][ECART_TYPE]) = ecartType(
            premiereTaxe,
            nombreVehiculeParType[i]
      );
   }

   free(taxesOrdonnees);
   taxesOrdonnees = NULL;

   return (ResultatRecapitulatifTaxes) valeursCalculees;
}

