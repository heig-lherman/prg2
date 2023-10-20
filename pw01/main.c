/*
  ---------------------------------------------------------------------------
  Fichier     : main.c
  Nom du labo : Labo1
  Auteur(s)   : [redacted]
  Date        : 04.03.2022
  But         : Programme simulant une planche de Galton.
                Le programme demande le nombre de billes et de rangées de la planche et affiche le nombre de passages
                à chaque endroit, ainsi qu'un histogramme du résultat de la simulation (Dernière ligne).
                La saisie utilisateur est contrôlée et le programme s'arrête après exécution.
  Remarque(s) :
  Compilateur : MinGW-w64
  ---------------------------------------------------------------------------
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SOMME_N_NOMBRE(a) (a) * ((a) -1) / 2// Somme des nombres allant de 1 à a-1

const unsigned NOMBRE_BILLE_MIN = 1000u;
const unsigned NOMBRE_BILLE_MAX = 30000u;
const unsigned NOMBRE_LIGNE_MIN = 10u;
const unsigned NOMBRE_LIGNE_MAX = 20u;
const unsigned TAILLE_HISTOGRAMME_MAX = 15u;
const char SYMBOLE_HISTOGRAMME = '*';

/**
 * Fonction qui affiche l'histogramme
 * @param histogramme
 * @param taille
 * @param symbole
 * @param espacement
 */
void affichageHistogramme(const unsigned *histogramme, unsigned taille, char symbole, unsigned espacement);

/**
 * Fonction qui affiche les valeurs de la planche de Galton
 * @param tab
 * @param nombreLignes
 * @param espacement
 */
void affichagePlanche(unsigned *tab, unsigned nombreLignes, unsigned espacement);

/**
 * Fonction qui calcul les valeurs de l'histogramme en fonction des valeurs du tableau tab
 * @param tab
 * @param taille
 * @param tabRelatif
 */
void calculValeurRelatives(const unsigned *tab, unsigned taille, unsigned *tabRelatif);

/**
 * Fonction qui s'occupe de la saisie utilisateur
 * @param texte
 * @param min
 * @param max
 * @return
 */
unsigned entreeUtilisateur(const char *texte, unsigned min, unsigned max);

/**
 * Fonction qui retourne l'emplacement de la bille dans la planche
 * @param tab
 * @param positionActuelle
 * @param ligneActuelle
 * @return
 */
unsigned faitUnSaut(unsigned *tab, unsigned positionActuelle, unsigned ligneActuelle);
/**
 * Fonction qui simule la planche de Galton
 * @param tab
 * @param nombreBilles
 * @param nombreLignes
 */
void repartitionBilles(unsigned *tab, unsigned nombreBilles, unsigned nombreLignes);
/**
 * Fonction qui retourne la valeur maximale d'un tableau
 * @param tab
 * @param taille
 * @return
 */
unsigned valeurMax(const unsigned *tab, unsigned taille);

/**
 * Fonction qui vide le tampon de la saisie utilisateur
 */
void viderTampon();

int main() {
   unsigned nombreBilles = entreeUtilisateur("Entrez le nombre de billes", NOMBRE_BILLE_MIN, NOMBRE_BILLE_MAX);
   unsigned nombreLignes = entreeUtilisateur("Entrez le nombre de rangees de compteurs", NOMBRE_LIGNE_MIN,
                                             NOMBRE_LIGNE_MAX);

   unsigned *tab = calloc(SOMME_N_NOMBRE(nombreLignes + 1), sizeof(unsigned));
   unsigned *histogramme = calloc(nombreLignes, sizeof(unsigned));

   if (histogramme == NULL || tab == NULL) {
      printf("Erreur d'allocation de memoire\n");
      exit(EXIT_FAILURE);
   }

   // Nombre de digits utilisés pour l'affichage des billes + 1 pour l'espace entre deux nombres
   unsigned espacement = floor(log10(nombreBilles)) + 2;

   printf("\n");

   repartitionBilles(tab, nombreBilles, nombreLignes);
   affichagePlanche(tab, nombreLignes, espacement);

   printf("\n");

   calculValeurRelatives(tab + SOMME_N_NOMBRE(nombreLignes), nombreLignes, histogramme);
   affichageHistogramme(histogramme, nombreLignes, SYMBOLE_HISTOGRAMME, espacement);

   return 0;
}

void affichageHistogramme(const unsigned *histogramme, unsigned taille, const char symbole, unsigned espacement) {
   for (unsigned i = TAILLE_HISTOGRAMME_MAX; i > 0; --i) {
      for (size_t j = 0; j < taille; ++j) {
         printf("%*c", espacement, histogramme[j] >= i ? symbole : ' ');
      }
      printf("\n");
   }
}

void affichagePlanche(unsigned *tab, unsigned nombreLignes, unsigned espacement) {
   unsigned ligne = 0;
   for (int i = 0; i < nombreLignes; ++i) {
      printf("%*s", espacement * (nombreLignes - 1 - i) / 2, "");

      for (size_t j = 0; j < ligne + 1; ++j) {
         printf("%*d", espacement, tab[SOMME_N_NOMBRE(ligne + 1) + j]);
      }
      ++ligne;
      printf("\n");
   }
}

void calculValeurRelatives(const unsigned *tab, const unsigned taille, unsigned *tabRelatif) {
   unsigned max = valeurMax(tab, taille);
   for (size_t i = 0; i < taille; ++i) {
      *(tabRelatif + i) = round((*(tab + i) * (double) TAILLE_HISTOGRAMME_MAX / max));
   }
}

unsigned entreeUtilisateur(const char *texte, const unsigned min, const unsigned max) {
   unsigned entreeCorrecte = 0;
   unsigned nombre;

   do {
      printf("%s [%d - %d] :", texte, min, max);
      entreeCorrecte = scanf("%d", &nombre);
      if (!entreeCorrecte || nombre < min || nombre > max) {
         viderTampon();
         printf("%s\n", "Saisie incorrecte. Veuillez SVP recommencer.");
         entreeCorrecte = 0;
      }
   } while (!entreeCorrecte);
   viderTampon();
   return nombre;
}

unsigned faitUnSaut(unsigned *tab, unsigned positionActuelle, unsigned ligneActuelle) {
   int random = rand() & 1;
   unsigned nouvellePosition = positionActuelle + ligneActuelle + 1 + random;
   tab[nouvellePosition] += 1;
   return nouvellePosition;
}

void repartitionBilles(unsigned *tab, unsigned nombreBilles, unsigned nombreLignes) {
   srand(time(0));
   tab[0] = nombreBilles;
   for (size_t i = 0; i < nombreBilles; ++i) {
      unsigned positionActuelle = 0;
      for (size_t j = 0; j < nombreLignes; ++j) {
         positionActuelle = faitUnSaut(tab, positionActuelle, j);
      }
   }
}

unsigned valeurMax(const unsigned *tab, const unsigned taille) {
   unsigned max = 0;
   for (size_t i = 0; i < taille; ++i) {
      if (*(tab + i) > max) {
         max = *(tab + i);
      }
   }
   return max;
}

void viderTampon() {
   int c;
   do {
      c = getchar();
   } while (c != '\n' && c != EOF);
}
