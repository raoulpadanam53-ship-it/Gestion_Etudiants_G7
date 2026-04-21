#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ─────────────────────────────────────────────
 * STRUCTURE DE DONNÉES
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
 * FONCTIONS UTILES (PROTOTYPES)
 * ───────────────────────────────────────────── */
void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Passage par adresse (pointeur) pour éviter la copie inutile de données */
void saisirInformation(Identifiant_etudiant *e) {
    printf("  Numero : ");
    scanf("%ld", &e->numCarte);
    viderBuffer();

    printf("  Nom    : ");
    fgets(e->nom, 50, stdin);
    e->nom[strcspn(e->nom, "\n")] = '\0';

    printf("  Note DST    : ");
    scanf("%f", &e->noteDST);
    printf("  Note Examen : ");
    scanf("%f", &e->noteExamen);
    viderBuffer(); 
}

/* Utilisation pure de l'arithmétique de pointeurs */
void calculerMoyennes(Identifiant_etudiant *tab, int n) {
    Identifiant_etudiant *p = tab;      // On initialise p au début du tableau
    Identifiant_etudiant *fin = tab + n; // On définit l'adresse de fin

    while (p < fin) {
        /* Calcul Moyenne Brute */
        p->moyenneBrute = (0.45f * p->noteDST) + (0.55f * p->noteExamen);

        /* Logique de bonification */
        if (p->moyenneBrute < 10.0f)
            p->moyenneDefinitive = p->moyenneBrute + 1.0f;
        else if (p->moyenneBrute <= 15.0f)
            p->moyenneDefinitive = p->moyenneBrute + 0.5f;
        else
            p->moyenneDefinitive = p->moyenneBrute;

        /* Sécurité : pas de note > 20 */
        if (p->moyenneDefinitive > 20.0f) 
            p->moyenneDefinitive = 20.0f;

        p++; // On décale le pointeur vers l'étudiant suivant en mémoire
    }
}

void afficher(Identifiant_etudiant *tab, int n) {
    Identifiant_etudiant *p = tab;
    Identifiant_etudiant *fin = tab + n;

    printf("\n╔══════════════════════════════════════════════╗");
    printf("\n║             RESULTATS - GROUPE 7             ║");
    printf("\n╚══════════════════════════════════════════════╝\n");

    while (p < fin) {
        printf("ID: %-8ld | Nom: %-15s | Moyenne: %.2f/20\n", 
                p->numCarte, p->nom, p->moyenneDefinitive);
        p++;
    }
}

/* ─────────────────────────────────────────────
 * PROGRAMME PRINCIPAL
 * ───────────────────────────────────────────── */
int main() {
    int n;

    printf("Nombre d'etudiants a gerer : ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erreur : Nombre invalide.\n");
        return 1;
    }
    viderBuffer();

    /* Allocation dynamique (Pointeur tab) */
    Identifiant_etudiant *tab = malloc(n * sizeof(Identifiant_etudiant));
    if (!tab) {
        perror("Erreur d'allocation memoire");
        return 1;
    }

    /* Remplissage via pointeur courant */
    for (int i = 0; i < n; i++) {
        printf("\nEtudiant %d/%d :\n", i + 1, n);
        saisirInformation(tab + i); // (tab + i) est l'adresse de la case i
    }

    /* Traitement et Affichage */
    calculerMoyennes(tab, n);
    afficher(tab, n);

    /* Libération propre de la mémoire */
    free(tab);
    
    printf("\n[ Travail termine par le Groupe 7 ]\n");
    return 0;
}
