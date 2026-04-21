/******************************************************************************************************************
 * NOM DU FICHIER  : sd_G7_gestion_etudiants_C
 
 DESCRIPTION    :   Ce programme permet de gérer les notes d'une promotion d'étudiants.
                    Il calcule la moyenne brute (DST 45% / Examen 55%) puis applique 
                    une bonification pour obtenir la moyenne définitive.
                    Le programme utilise une structure pour les identifiants et 
                    l'arithmétique de pointeurs pour le parcours des données.

OBJECTIF        :   Mettre en pratique les STRUCTURES complexes, l'allocation dynamique
                    de tableaux de structures et la manipulation par pointeurs.

ENTREES         :   - Nombre d'étudiants (taille du tableau)
                    - Informations (Numéro, Nom, Notes DST et Examen)

SORTIES         :   - Affichage des noms et des moyennes définitives après bonus.

 MEMBRES DE GROUPE7 : MENSAH Maurice (Chef)         - GM
                      PITCHE S. Phanuel Jonas K.    - GM
                      TCHOGLI Ayefouni Magloire     - GM
                      PADANAM Essobiou Raoul        - GM
                      DOSSOU Kodjovi Kevin          - GC
                      PALA Kivema Christophe        - GC
                      GAO Abdou Sabour Rodolphe     - GM
                      NONDO Rewou Tracy             - GC
                      BLAODEKISSI Essossolam        - GC

 DATE           : 21/04/2026
 VERSION        : Final - Gestion Étudiants
********************************************************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ─────────────────────────────────────────────
 * DÉFINITION DE LA STRUCTURE
 * ───────────────────────────────────────────── */
struct Identifiant_etudiant {
    long numCarte;
    char nom[50];
    float noteDST;
    float noteExamen;
    float moyenneBrute;
    float moyenneDefinitive;
};
typedef struct Identifiant_etudiant Identifiant_etudiant;

/* ─────────────────────────────────────────────
 * PROTOTYPES
 * ───────────────────────────────────────────── */
static int      lire_taille_promotion(void);
static void     saisir_information(Identifiant_etudiant *e);
static void     calculer_moyennes(Identifiant_etudiant *tab, int n);
static void     afficher_resultats(const Identifiant_etudiant *tab, int n);
static void     vider_buffer(void);

/* ─────────────────────────────────────────────
 * POINT D'ENTRÉE
 * ───────────────────────────────────────────── */
int main(void)
{
    puts("\n╔══════════════════════════════════════════════╗");
    puts(  "║      GESTION DES NOTES - PROMOTION G7        ║");
    puts(  "╚══════════════════════════════════════════════╝\n");

    /* 1. Lecture du nombre d'étudiants (taille du tableau) */
    int n = lire_taille_promotion();

    /* 2. Allocation dynamique du tableau d'étudiants */
    Identifiant_etudiant *promotion = malloc((size_t)n * sizeof(Identifiant_etudiant));
    if (promotion == NULL) {
        fprintf(stderr, "[ERREUR FATALE] Échec de l'allocation mémoire.\n");
        return EXIT_FAILURE;
    }

    /* 3. Saisie des informations via pointeurs */
    Identifiant_etudiant *courant = promotion;
    Identifiant_etudiant *fin = promotion + n;
    int compteur = 1;

    while (courant < fin) {
        printf("\n--- Saisie Étudiant %d ---\n", compteur);
        saisir_information(courant);
        courant++;
        compteur++;
    }

    /* 4. Calculs des moyennes (Brute et Définitive) */
    calculer_moyennes(promotion, n);

    /* 5. Affichage des résultats */
    afficher_resultats(promotion, n);

    /* 6. Libération de la mémoire */
    free(promotion);
    promotion = NULL;

    puts("\n** Fin du programme - Groupe 7 **\n");
    return EXIT_SUCCESS;
}

/* ─────────────────────────────────────────────
 * IMPLÉMENTATIONS
 * ───────────────────────────────────────────── */

static void vider_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static int lire_taille_promotion(void) {
    int n;
    printf("Nombre d'etudiants dans le tableau : ");
    while (scanf("%d", &n) != 1 || n <= 0) {
        vider_buffer();
        printf("[!] Valeur invalide. Entrez un nombre > 0 : ");
    }
    vider_buffer();
    return n;
}

static void saisir_information(Identifiant_etudiant *e) {
    printf("  Numero de carte : ");
    scanf("%ld", &e->numCarte);
    vider_buffer();

    printf("  Nom complet     : ");
    fgets(e->nom, 50, stdin);
    e->nom[strcspn(e->nom, "\n")] = '\0';

    printf("  Note DST        : ");
    while (scanf("%f", &e->noteDST) != 1) {
        vider_buffer();
        printf("  [!] Note invalide. Entrez un reel : ");
    }

    printf("  Note Examen     : ");
    while (scanf("%f", &e->noteExamen) != 1) {
        vider_buffer();
        printf("  [!] Note invalide. Entrez un reel : ");
    }
    vider_buffer();
}

static void calculer_moyennes(Identifiant_etudiant *tab, int n) {
    Identifiant_etudiant *courant = tab;
    Identifiant_etudiant *fin = tab + n;

    while (courant < fin) {
        /* Calcul Moyenne Brute (45% DST + 55% EXAM) */
        courant->moyenneBrute = (0.45f * courant->noteDST) + (0.55f * courant->noteExamen);

        /* Application du bonus selon les conditions */
        if (courant->moyenneBrute < 10.0f)
            courant->moyenneDefinitive = courant->moyenneBrute + 1.0f;
        else if (courant->moyenneBrute <= 15.0f)
            courant->moyenneDefinitive = courant->moyenneBrute + 0.5f;
        else
            courant->moyenneDefinitive = courant->moyenneBrute;

        courant++;
    }
}

static void afficher_resultats(const Identifiant_etudiant *tab, int n) {
    const Identifiant_etudiant *courant = tab;
    const Identifiant_etudiant *fin = tab + n;

    puts("\n╔══════════════════════════════════════════════╗");
    puts(  "║             RESULTATS FINAUX                 ║");
    puts(  "╚══════════════════════════════════════════════╝");

    while (courant < fin) {
        printf("\nEtudiant : %-20s | Moyenne : %.2f", courant->nom, courant->moyenneDefinitive);
        courant++;
    }
    puts("\n------------------------------------------------");
}
