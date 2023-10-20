/*
 ------------------------------------------------------------------------------
 Nom du fichier : main.c
 Auteur(s)      : [redacted]
 Date creation  : 23.05.2022
 Description    : Programme principal qui utilise et affiche les résultats de
                  la librairie de gestion des frais de parking.
 Remarque(s)    : Le programme s'exécute en ligne de commande et se termine
                  à la fin de l'exécution du programme. Il n'y a pas de
                  saisie demandée à l'utilisateur.
 Fonctionnement : L'évolutivité de ce code est simplifiée grâce aux tableaux de
                  pointeurs de fonction permettant de calculer la taxe d'un
                  type de véhicule ainsi que son affichage dans la console, et,
                  à la disponibilité des constantes dans les fichiers .h .
                  L'ensemble des manipulations nécessaires à l'ajout d'un
                  nouveau type de véhicule (par ex : voiture électrique) sont :
                     - Ajout d'une étiquette de type
                       dans vehicule.h -> VEHICULE_TYPE_ETIQUETTE.
                     - Ajout d'une chaine de caractère
                       dans vehicule.h -> VEHICULE_TYPE_NOM.
                     - Ajout d'un struct dans vehicule.h
                     - Ajout d'un constructeur dans vehicule.h
                     - Ajout d'une étiquette dans vehicule.h -> VehiculeType
                     - Ajout d'une fonction
                       dans taxation.h -> double (*taxes[])(const Vehicule *)
                       qui permet le calcul de la taxe du nouveau type
                       de véhicule.
                     - Ajout d'une fonction dans affichage.h
                       -> void (*METHODES_DESCRIPTION[])(const Vehicule *)
                       qui permet l'affichage du nouveau type de véhicule.
 Compilateur    : gcc version 12.1.1 (Solus)
 ------------------------------------------------------------------------------
*/

#include <stdlib.h>

#include "affichage.h"
#include "taxation.h"
#include "vehicule.h"

#define TAILLE_PARKING 10

int main(void) {

   // Définition des véhicules du parking
   const Vehicule park[TAILLE_PARKING] = {
         construireVoitureStandard("Peugeot 306", "VD123456", 1500, 1200, 187),
         construireVoitureLuxe("Mercedes", "ZH123456", 2000, 249),
         construireCamionnette("VW T4", "FR123456", 6),
         construireCamionnette("Volvo Transporter", "FR123456", 5),
         construireVoitureStandard("Opel Corsa", "VD123456", 2000, 1800, 208),
         construireVoitureLuxe("Ferrari Enzo", "ZH123456", 1750, 380),
         construireVoitureLuxe("Mazeratti", "SH123456", 2000, 500),
         construireVoitureStandard("VW Passat", "FR123456", 1000, 1600, 180),
         construireVoitureStandard("Dacia", "BS123456", 1650, 1399, 129),
         construireVoitureStandard("Audi A4", "LU123456", 900, 2000, 400),
   };

   // Mise en ordre par taxe (décroissant)
   triParking(park, TAILLE_PARKING);
   afficherVehicules(park, TAILLE_PARKING);

   ResultatRecapitulatifTaxes valeursCalculees = recapitulatifTaxesAnnuelles(
         park,
         TAILLE_PARKING
   );
   if (valeursCalculees) {
      afficherTaxes(valeursCalculees);
   }

   free((void*) valeursCalculees);
   valeursCalculees = NULL;

   return EXIT_SUCCESS;
}
