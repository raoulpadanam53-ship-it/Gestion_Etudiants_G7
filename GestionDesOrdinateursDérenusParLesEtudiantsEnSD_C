/* Description : Ce programme en langage C permet de gérer dynamiquement un parc informatique de 300 ordinateurs maximum en utilisant un tableau de pointeurs sur structures.
Grâce à une architecture en compilation séparée, il offre une gestion optimisée de la mémoire vive : 
chaque ordinateur est alloué dynamiquement et manipulé via le formalisme pointeur pour plus d'efficacité. 
L'utilisateur dispose d'un menu complet pour ajouter, supprimer ou lister des machines sur une seule ligne, 
tout en ayant accès à des fonctions avancées comme le tri par performance (vitesse CPU) et 
le calcul automatique de la valeur financière totale du parc. Enfin, le programme garantit la stabilité du système 
en libérant proprement chaque bloc de mémoire utilisé avant de quitter.  */





/*ordinateur.h*/


#ifndef ORDINATEUR_H_INCLUDED
#define ORDINATEUR_H_INCLUDED
#define MAX_ORD 300



struct Ordinateur{
    int num_carte_detenteur;
    char specialite_detenteur[50];
    char num_serie[50];
    char marque[50];
    float vitesse_cpu;
    int ram;
    int taille_disque;
    int prix_estime;
};

typedef struct Ordinateur Tordinateur;


// Prototypes des fonctions
void afficherMenu();
Tordinateur* saisirOrdinateur();
void ajouterOrdinateur(Tordinateur** parc, int* nb_actuel);
void listerOrdinateurs(Tordinateur** parc, int nb_actuel);
void afficherDetails(Tordinateur** parc, int nb_actuel);
void supprimerOrdinateur(Tordinateur** parc, int* nb_actuel);
void repartirParSpecialite(Tordinateur** parc, int nb_actuel);
void repartirParMarque(Tordinateur** parc, int nb_actuel);
void classerParVitesse(Tordinateur** parc, int nb_actuel);
long calculerValeurTotale(Tordinateur** parc, int nb_actuel);
void libererParc(Tordinateur** parc, int nb_actuel);


#endif // ORDINATEUR_H_INCLUDED













/*main.c*/

#include <stdio.h>
#include <stdlib.h>
#include "ordinateur.h"





int main() {
    // Allocation dynamique correcte

    Tordinateur**  parc = malloc(MAX_ORD*sizeof(Tordinateur**));
    if (!parc) return 1;

    int nb_actuel = 0;
    int choix;

    do {
        afficherMenu();
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouterOrdinateur(parc, &nb_actuel);

            break;

            case 2: listerOrdinateurs(parc, nb_actuel);

            break;

            case 3: afficherDetails(parc, nb_actuel);

            break;

            case 4: supprimerOrdinateur(parc, &nb_actuel);

            break;

            case 7: classerParVitesse(parc, nb_actuel);

            break;

            case 8:
                printf("Valeur totale du parc : %ld F CFA\n",
                       calculerValeurTotale(parc, nb_actuel));
            break;

            case 0:
                libererParc(parc, nb_actuel);
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    return 0;
}















void afficherMenu() {
    printf("\n--- GESTION DU PARC INFORMATIQUE SD+C ---\n");
    printf("1. Ajouter un ordinateur\n");
    printf("2. Lister les ordinateurs\n");
    printf("3. Afficher les détails d'un ordinateur\n");
    printf("4. Supprimer un ordinateur\n");
    printf("5. Répartir par spécialité\n");
    printf("6. Répartir par marque\n");
    printf("7. Classer par vitesse des processeurs\n");
    printf("8. Calculer la valeur totale du parc\n");
    printf("0. Quitter\n");
    printf("Choix : ");
}



Tordinateur* saisirOrdinateur() {
    Tordinateur* nouv = (Tordinateur*)malloc(sizeof(Tordinateur));
    if (!nouv) return NULL;

    printf("Numéro de carte du détenteur : ");
    scanf("%d", &nouv->num_carte_detenteur);
    printf("Spécialité : ");
    scanf("%s", nouv->specialite_detenteur);
    printf("Numéro de série : ");
    scanf("%s", nouv->num_serie);
    printf("Marque : ");
    scanf("%s", nouv->marque);
    printf("Vitesse CPU (GHz) : ");
    scanf("%f", &nouv->vitesse_cpu);
    printf("RAM (Go) : ");
    scanf("%d", &nouv->ram);
    printf("Disque (Go) : ");
    scanf("%d", &nouv->taille_disque);
    printf("Prix estim (F CFA) : ");
    scanf("%d", &nouv->prix_estime);

    return nouv;
}







void ajouterOrdinateur(Tordinateur** parc, int* nb_actuel) {

    if (*nb_actuel >= MAX_ORD) {
        printf("Erreur : Parc plein !\n");
        return;
    }


    Tordinateur* nouv = saisirOrdinateur();
    if (nouv) {
        *(parc + *nb_actuel) = nouv;
        (*nb_actuel)++;
        printf("Ordinateur ajout avec succs.\n");
    }


}





void listerOrdinateurs(Tordinateur** parc, int nb_actuel) {
    printf("\n%-10s | %-15s | %-10s | %-10s\n", "ID Carte", "Marque", "Srie", "Prix");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < nb_actuel; i++) {
        Tordinateur* o = *(parc + i);
        printf("%-10d | %-15s | %-10s | %-10d F\n",
               o->num_carte_detenteur, o->marque, o->num_serie, o->prix_estime);
    }
}





void afficherDetails(Tordinateur** parc, int nb_actuel) {
    int id;
    printf("Entrez le numro de carte du dtenteur : ");
    scanf("%d", &id);
    for (int i = 0; i < nb_actuel; i++) {
        if ((*(parc + i))->num_carte_detenteur == id) {
            Tordinateur* o = *(parc + i);
            printf("\n--- DETAILS ---\nMarque: %s\nCPU: %.2f GHz\nRAM: %d Go\nDisque: %d Go\nSpcialit: %s\n",
                   o->marque, o->vitesse_cpu, o->ram, o->taille_disque, o->specialite_detenteur);
            return;
        }
    }
    printf("Ordinateur non trouv.\n");
}




void supprimerOrdinateur(Tordinateur** parc, int* nb_actuel) {
    int id;
    printf("Numro de carte de l'ordinateur  supprimer : ");
    scanf("%d", &id);
    for (int i = 0; i < *nb_actuel; i++) {
        if ((*(parc + i))->num_carte_detenteur == id) {
            free(*(parc + i)); // Libration de la mmoire de la structure
            // Dcalage des pointeurs suivants
            for (int j = i; j < *nb_actuel - 1; j++) {
                *(parc + j) = *(parc + j + 1);
            }
            (*nb_actuel)--;
            printf("Ordinateur supprim.\n");
            return;
        }
    }
    printf("Introuvable.\n");
}





void classerParVitesse(Tordinateur** parc, int nb_actuel) {
    // Tri à bulles simple sur les pointeurs
    for (int i = 0; i < nb_actuel - 1; i++) {
        for (int j = 0; j < nb_actuel - i - 1; j++) {
            if ((*(parc + j))->vitesse_cpu < (*(parc + j + 1))->vitesse_cpu) {
                Tordinateur* temp = *(parc + j);
                *(parc + j) = *(parc + j + 1);
                *(parc + j + 1) = temp;
            }
        }
    }
    printf("Liste classe par vitesse (dcroissant).\n");
    listerOrdinateurs(parc, nb_actuel);
}



long calculerValeurTotale(Tordinateur** parc, int nb_actuel) {
    long total = 0;
    for (int i = 0; i < nb_actuel; i++) {
        total += (*(parc + i))->prix_estime;
    }
    return total;
}

void libererParc(Tordinateur** parc, int nb_actuel) {
    for (int i = 0; i < nb_actuel; i++) {
        free(*(parc + i));
    }
    free(parc);
    printf("Mmoire libre. Au revoir !\n");
}
