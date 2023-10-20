/*
 ------------------------------------------------------------------------------
 Nom du fichier : taxation.h
 Auteur(s)      : [redacted]
 Date creation  : 24.05.2022
 Description    : Ce module permet de calculer les taxes pour chaque type
                  de véhicule présent dans un parking, en fonction de plusieurs
                  paramètres donnés statiquement.
 Remarque(s)    : Les constantes déclarée statique permettent l'adaptation de
                  l'affichage par l'utilisateur
 Compilateur    : gcc version 12.1.1 (Solus)
 ------------------------------------------------------------------------------
*/

#ifndef PRG2_L2_PARKING_TAXATION_H
#define PRG2_L2_PARKING_TAXATION_H

#include <inttypes.h>
#include <stdlib.h>

#include "vehicule.h"

static const uint16_t LIMITES_CYLINDREE = 1400; // En [cm^3]
static const uint16_t LIMITES_CO2 = 130; // En [g/km]
static const uint16_t LIMITE_PUISSANCE = 250; // En [CV]

// Taxe camionnette
static const double TAXE_POIDS = 10.; // En [CHF]

// Taxe voiture standard
static const double TAXE_COEF_GROSSE_CYLINDREE = 0.05; // En [CHF]
static const double TAXE_CO2_GRANDE = 50.; // En [CHF]
static const double TAXE_CO2_PETITE = 0.; // En [CHF]

// Taxe voiture luxe
static const double TAXE_PUISSANCE_PETITE = 200.; // En [CHF]
static const double TAXE_PUISSANCE_GRANDE = 300.; // En [CHF]
static const double TAXE_COEF_PUISSANCE_GRANDE = 20.; // En [CHF]

// Taxe relative aux types de véhicule/étiquette
// Structure permettant l'évolutivité des taxes
static const double TAXE_DE_BASE[] = {400., 400., 700.}; // en [CHF]

// Types de récapitulatifs. Les valeurs de recapitulatifTaxesAnnuelles(..)
// ci-dessous seront données dans cet ordre.
enum RECAPITULATIF_TAXES {
   SOMME,
   MOYENNE,
   MEDIANE,
   ECART_TYPE,
   NB_RECAPITULATIF_TAXES // Doit rester la dernière valeur
};

// Définit la taxe de base d'un véhicule
double taxeBase(const Vehicule* v);

// Définition des taxes spécifiques au type de véhicules
double taxeVoitureStandard(const Vehicule* v);
double taxeVoitureHautDeGamme(const Vehicule* v);
double taxeCamionnette(const Vehicule* v);

// Regroupement des calculs des taxes dans un tableau de double
typedef const double (* ResultatRecapitulatifTaxes)[NB_RECAPITULATIF_TAXES];
ResultatRecapitulatifTaxes recapitulatifTaxesAnnuelles(
      Parking park,
      size_t taille
);

// Tableau de pointeurs de fonctions calculant la taxe annuelle d'un type
// de véhicule. Permet le principe de d'extension facile du type de véhicule.
static double (* const METHODES_CALCUL_TAXES[])(const Vehicule*) = {
      taxeVoitureStandard,
      taxeVoitureHautDeGamme,
      taxeCamionnette
};

#endif //PRG2_L2_PARKING_TAXATION_H
