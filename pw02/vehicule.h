/*
 ------------------------------------------------------------------------------
 Nom du fichier : vehicule.h
 Auteur(s)      : [redacted]
 Date creation  : 24.05.2022
 Description    : Module gérant la structure de donnée pour véhicules.
                  Les prototypes des fonctions relatives au traitement
                  des véhicules sont définis ici.
 Remarque(s)    : Les constantes déclarée statique ainsi que l'enum à
                  disposition permettent l'ajout de nouveaux types de véhicules.
 Compilateur    : gcc version 12.1.1 (Solus)
 ------------------------------------------------------------------------------
*/

#ifndef PRG2_L2_PARKING_VEHICULE_H
#define PRG2_L2_PARKING_VEHICULE_H

#include <inttypes.h>
#include <stddef.h>

// Définition des étiquettes des véhicules
typedef enum {
   VOITURE_STANDARD,
   VOITURE_HAUT_DE_GAMME,
   CAMIONNETTE,
   NB_TYPE_VEHICULE // Doit rester la dernière valeur
} VEHICULE_TYPE_ETIQUETTE;

// Permet de traiter les noms des types de véhicules
// Défini selon l'ordre donné dans l'étiquette ci-dessus.
static const char* const VEHICULE_TYPE_NOM[] = {
      "Voiture standard",
      "Voiture haut de gamme",
      "Camionnette"
};

typedef struct {
   double volume; // en [m^3]
} Camionnette;

typedef struct {
   uint16_t cylindree; // en [cm^3]
   uint16_t co2;       // en [g/km]
} VoitureStandard;

typedef struct {
   uint16_t puissance; // en [cv]
} VoitureLuxe;

typedef union {
   VoitureStandard standard;
   VoitureLuxe luxe;
} TypeVoiture;

typedef struct {
   uint16_t poids; // en [kg]
   TypeVoiture type;
} Voiture;

typedef union {
   Camionnette camionnette;
   Voiture voiture;
} TypeVehicule;

typedef struct {
   TypeVehicule type;
   VEHICULE_TYPE_ETIQUETTE etiquette;
   const char* marque;
   const char* plaque;
} Vehicule;

typedef const Vehicule* Parking;

// Permet de trier les véhicules d'un parking par le montant
// de la taxe annuelle dans l'ordre décroissant
void triParking(Parking parking, size_t tailleParking);

// Permet de comparer deux véhicules en fonction de leurs taxes respectives
// Les pointeurs donnés doivent pointer sur un pointeur sur Vehicule
// La comparaison est faite pour un ordre décroissant
int comparaisonTaxe(const void* a, const void* b);

// Constructeurs de véhicules
Vehicule construireVoitureStandard(
      const char* marque,
      const char* plaque,
      uint16_t poids,
      uint16_t cylindree,
      uint16_t co2
);

Vehicule construireVoitureLuxe(
      const char* marque,
      const char* plaque,
      uint16_t poids,
      uint16_t puissance
);

Vehicule construireCamionnette(
      const char* marque,
      const char* plaque,
      double volume
);

#endif //PRG2_L2_PARKING_VEHICULE_H
