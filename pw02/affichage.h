/*
 ------------------------------------------------------------------------------
 Nom du fichier : affichage.h
 Auteur(s)      : [redacted]
 Date creation  : 24.05.2022
 Description    : Ce module permet de gérer l'affichage des données des
                  véhicules et statistiques d'un parking.
 Remarque(s)    : Permet uniquement un affichage dans la console
                  Les constantes déclarées statiques permettent l'adaptation de
                  l'affichage par l'utilisateur
 Compilateur    : gcc version 12.1.1 (Solus)
 ------------------------------------------------------------------------------
*/

#ifndef PRG2_L2_PARKING_AFFICHAGE_H
#define PRG2_L2_PARKING_AFFICHAGE_H

#include <inttypes.h>
#include <stdio.h>

#include "taxation.h"
#include "vehicule.h"

// Constantes permettant la manipulation de l'affichage par l'utilisateur
// Une valeur trop élevée aura pour conséquence un affichage insignifiant
static const uint8_t LARGEUR_COLONNE = 22;
static const char SEPARATEUR_COLONNE = '|';
static const char SEPARATEUR_LIGNE = '-';

// Affiche une ligne de séparation qui s'étend sur la largeur totale du tableau
void ligne(void);

// Affiche un véhicule dans la console
void afficherVehicule(const Vehicule* v);

// Affiche les véhicules d'un parking
void afficherVehicules(Parking park, size_t taille);

// Affiche le récapitulatif des taxes annuelles
void afficherTaxes(ResultatRecapitulatifTaxes valeursCalculees);

// Récupère un tableau de caractères contenant
// la description d'un véhicule standard
const char* descriptionVoitureStandard(const Vehicule* vehicule);

// Récupère un tableau de caractères contenant
// la description d'un véhicule haut de gamme
const char* descriptionVoitureHautDeGamme(const Vehicule* vehicule);

// Récupère un tableau de caractères contenant
// la description d'une camionnette
const char* descriptionCamionnette(const Vehicule* vehicule);

// Tableau de pointeurs de fonctions qui retourne la description d'un type
// de véhicule sous la forme d'un tableau de caractères.
// Principe de d'extension simplifié du type de véhicule
static const char* (* const METHODES_DESCRIPTION[])(const Vehicule*) = {
      descriptionVoitureStandard,
      descriptionVoitureHautDeGamme,
      descriptionCamionnette
};

#endif //PRG2_L2_PARKING_AFFICHAGE_H
