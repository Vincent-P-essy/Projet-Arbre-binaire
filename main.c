#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "DM_1.h"

/* Fonction pour libérer un arbre */
void libere_arbre(Arbre a)
{
    if (a != NULL)
    {
        libere_arbre(a->fg);
        libere_arbre(a->fd);
        free(a);
    }
}

/* Fonction pour libérer une liste */
void libere_liste(Liste l)
{
    while (l != NULL)
    {
        Liste temp = l;
        l = l->suivant;
        free(temp);
    }
}

/* Fonction pour afficher un arbre (pour debugging) */
void affiche_arbre(Arbre a, int niveau)
{
    if (a != NULL)
    {
        for (int i = 0; i < niveau; i++)
            printf("  ");
        printf("%d\n", a->valeur);
        affiche_arbre(a->fg, niveau + 1);
        affiche_arbre(a->fd, niveau + 1);
    }
}

/* Test des fonctions de base de la liste */
void test_liste()
{
    printf("\n=== Test des fonctions de liste ===\n");

    // Test allocation cellule
    Noeud *n = alloue_noeud(42, NULL, NULL);
    Cellule *c = alloue_cellule(n);
    if (c != NULL && c->noeud->valeur == 42)
        printf("Test alloue_cellule: OK\n");
    else
        printf("Test alloue_cellule: ECHEC\n");

    // Test insertion en tête
    Liste l = NULL;
    insere_en_tete(&l, c);
    if (l != NULL && l->noeud->valeur == 42)
        printf("Test insere_en_tete: OK\n");
    else
        printf("Test insere_en_tete: ECHEC\n");

    // Nettoyage
    libere_liste(l);
    free(n);
}

/* Test des fonctions de la file */
void test_file()
{
    printf("\n=== Test des fonctions de file ===\n");

    File f = initialisation();
    if (f != NULL && est_vide(f))
        printf("Test initialisation et est_vide: OK\n");
    else
        printf("Test initialisation et est_vide: ECHEC\n");

    // Test enfilement/défilement
    Noeud *n1 = alloue_noeud(1, NULL, NULL);
    Noeud *n2 = alloue_noeud(2, NULL, NULL);

    if (enfiler(f, n1) && enfiler(f, n2))
        printf("Test enfiler: OK\n");
    else
        printf("Test enfiler: ECHEC\n");

    Noeud *sortant;
    if (defiler(f, &sortant) && sortant->valeur == 1)
        printf("Test defiler: OK\n");
    else
        printf("Test defiler: ECHEC\n");

    // Nettoyage
    free(n1);
    free(n2);
    free(f);
}

/* Test de construction d'arbres */
void test_construction_arbres()
{
    printf("\n=== Test de construction d'arbres ===\n");

    Arbre a1 = NULL, a2 = NULL;

    // Test arbre complet
    if (construit_complet(2, &a1))
    {
        printf("Construction arbre complet h=2:\n");
        affiche_arbre(a1, 0);
    }

    // Test arbre filiforme
    if (construit_filiforme_aleatoire(3, &a2, 42))
    {
        printf("\nConstruction arbre filiforme h=3:\n");
        affiche_arbre(a2, 0);
    }

    // Nettoyage
    libere_arbre(a1);
    libere_arbre(a2);
}

/* Comparaison des méthodes de parcours */
void test_parcours()
{
    printf("\n=== Test des parcours en largeur ===\n");

    Arbre a = NULL;
    construit_complet(3, &a);

    Liste l1 = NULL, l2 = NULL;
    int visites1 = 0, visites2 = 0;

    // Test parcours naïf
    if (parcours_largeur_naif_V2(a, &l1, &visites1))
    {
        printf("Parcours naif: ");
        affiche_liste_renversee(l1);
        printf("\nNombre de visites: %d\n", visites1);
    }

    // Test parcours avec file
    if (parcours_largeur_V2(a, &l2, &visites2))
    {
        printf("Parcours avec file: ");
        affiche_liste_renversee(l2);
        printf("\nNombre de visites: %d\n", visites2);
    }

    // Nettoyage
    libere_arbre(a);
    libere_liste(l1);
    libere_liste(l2);
}

/* Test de performance */
void test_performance()
{
    printf("\n=== Test de performance ===\n");

    int hauteurs[] = {5, 7, 10};
    int nb_tests = sizeof(hauteurs) / sizeof(hauteurs[0]);

    for (int i = 0; i < nb_tests; i++)
    {
        Arbre a = NULL;
        construit_complet(hauteurs[i], &a);

        Liste l1 = NULL, l2 = NULL;
        int visites1 = 0, visites2 = 0;

        clock_t debut, fin;

        // Test méthode naïve
        debut = clock();
        parcours_largeur_naif_V2(a, &l1, &visites1);
        fin = clock();
        double temps1 = ((double)(fin - debut)) / CLOCKS_PER_SEC;

        // Test méthode avec file
        debut = clock();
        parcours_largeur_V2(a, &l2, &visites2);
        fin = clock();
        double temps2 = ((double)(fin - debut)) / CLOCKS_PER_SEC;

        printf("\nHauteur %d:\n", hauteurs[i]);
        printf("Methode naive: %d visites, %.6f secondes\n", visites1, temps1);
        printf("Methode file: %d visites, %.6f secondes\n", visites2, temps2);

        // Nettoyage
        libere_arbre(a);
        libere_liste(l1);
        libere_liste(l2);
    }
}

int main()
{
    test_liste();
    test_file();
    test_construction_arbres();
    test_parcours();
    test_performance();

    return 0;
}