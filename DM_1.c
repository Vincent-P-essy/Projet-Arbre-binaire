#include <stdlib.h>
#include <stdio.h>
#include "DM_1.h"

/* ===== FONCTIONS DE MANIPULATION DE LISTES ===== */
///////////////////
// entrée: un pointeur sur un noeud n
// sortie: un pointeur sur une nouvelle cellule contenant n
// ce que fait la fonction: alloue une nouvelle cellule en mémoire et initialise ses champs
///////////////////
Cellule *alloue_cellule(Noeud *n)
{
    Cellule *c = (Cellule *)malloc(sizeof(Cellule));
    if (c != NULL)
    {
        c->noeud = n;
        c->suivant = NULL;
    }
    return c;
}

///////////////////
// entrée: un pointeur sur une liste l, un pointeur sur une cellule c
// sortie: void
// ce que fait la fonction: insère la cellule c en tête de la liste l
///////////////////
void insere_en_tete(Liste *l, Cellule *c)
{
    if (c != NULL)
    {
        c->suivant = *l;
        *l = c;
    }
}

///////////////////
// entrée: un pointeur sur une liste l
// sortie: un pointeur sur la cellule extraite ou NULL
// ce que fait la fonction: extrait et retourne la première cellule de la liste
///////////////////
Cellule *extrait_tete(Liste *l)
{
    if (*l == NULL)
        return NULL;
    Cellule *temp = *l;
    *l = (*l)->suivant;
    temp->suivant = NULL;
    return temp;
}

///////////////////
// entrée: une liste lst
// sortie: void
// ce que fait la fonction: affiche récursivement les valeurs des noeuds dans l'ordre inverse
///////////////////
void affiche_liste_renversee(Liste lst)
{
    if (lst == NULL)
        return;
    affiche_liste_renversee(lst->suivant);
    printf("%d ", lst->noeud->valeur);
}

/* ===== FONCTIONS DE MANIPULATION DE FILES ===== */

///////////////////
// entrée: void
// sortie: un pointeur sur une nouvelle file
// ce que fait la fonction: initialise et retourne une file vide
///////////////////
File initialisation(void)
{
    File f = (File)malloc(sizeof(Queue));
    if (f != NULL)
    {
        f->debut = NULL;
        f->fin = NULL;
        f->taille = 0;
    }
    return f;
}

///////////////////
// entrée: une file f
// sortie: 1 si la file est vide, 0 sinon
// ce que fait la fonction: vérifie si une file est vide
///////////////////
int est_vide(File f)
{
    return (f == NULL || f->debut == NULL);
}

///////////////////
// entrée: une file f, un pointeur sur un noeud n
// sortie: 1 si l'opération réussit, 0 sinon
// ce que fait la fonction: ajoute un nouveau noeud en fin de file
///////////////////
int enfiler(File f, Noeud *n)
{
    if (f == NULL)
        return 0;

    Cellule *nouvelle = alloue_cellule(n);
    if (nouvelle == NULL)
        return 0;

    if (est_vide(f))
    {
        f->debut = f->fin = nouvelle;
    }
    else
    {
        f->fin->suivant = nouvelle;
        f->fin = nouvelle;
    }
    f->taille++;
    return 1;
}

///////////////////
// entrée: une file f, un pointeur double sur un noeud sortant
// sortie: 1 si l'opération réussit, 0 sinon
// ce que fait la fonction: retire le premier élément de la file et le stocke dans sortant
///////////////////
int defiler(File f, Noeud **sortant)
{
    if (est_vide(f))
        return 0;

    Cellule *temp = extrait_tete(&(f->debut));
    if (temp == NULL)
        return 0;

    *sortant = temp->noeud;
    if (f->debut == NULL)
    {
        f->fin = NULL;
    }
    f->taille--;
    free(temp);
    return 1;
}

/* ===== FONCTIONS DE MANIPULATION D'ARBRES ===== */
///////////////////
// entrée: une valeur val, deux arbres fg et fd
// sortie: un pointeur sur un nouveau noeud
// ce que fait la fonction: crée un nouveau noeud avec la valeur et les fils spécifiés
///////////////////
Noeud *alloue_noeud(int val, Arbre fg, Arbre fd)
{
    Noeud *n = (Noeud *)malloc(sizeof(Noeud));
    if (n != NULL)
    {
        n->valeur = val;
        n->fg = fg;
        n->fd = fd;
    }
    return n;
}

///////////////////
// entrée: une hauteur h, un pointeur sur un arbre a
// sortie: 1 si la construction réussit, 0 sinon
// ce que fait la fonction: construit un arbre binaire complet de hauteur h
///////////////////
int construit_complet(int h, Arbre *a) {
    int valeur = 1;  // Réinitialisation à chaque appel

    if (h < 0) {
        *a = NULL;
        return 1;
    }

    *a = alloue_noeud(valeur++, NULL, NULL);
    if (*a == NULL) return 0;

    if (h > 0) {
        if (!construit_complet(h - 1, &((*a)->fg))) {
            free(*a);
            *a = NULL;
            return 0;
        }
        if (!construit_complet(h - 1, &((*a)->fd))) {
            free(*a);
            *a = NULL;
            return 0;
        }
    }

    return 1;
}

///////////////////
// entrée: une hauteur h, un pointeur sur un arbre a, un entier graine
// sortie: 1 si la construction réussit, 0 sinon
// ce que fait la fonction: construit un arbre filiforme aléatoire de hauteur h
///////////////////
int construit_filiforme_aleatoire(int h, Arbre *a, int graine) {
    int valeur = 1;  // Réinitialisation locale
    srand(graine);    // Initialisation de la graine

    if (h < 0) {
        *a = NULL;
        return 1;
    }

    *a = alloue_noeud(valeur++, NULL, NULL);
    if (*a == NULL) return 0;

    if (h > 0) {
        int direction = rand() % 2;  // 0 -> gauche, 1 -> droite

        if (direction) {
            if (!construit_filiforme_aleatoire(h - 1, &((*a)->fg), graine)) {
                free(*a);
                *a = NULL;
                return 0;
            }
        } else {
            if (!construit_filiforme_aleatoire(h - 1, &((*a)->fd), graine)) {
                free(*a);
                *a = NULL;
                return 0;
            }
        }
    }

    return 1;
}

///////////////////
// entrée: un arbre a, un niveau niv, un pointeur sur une liste lst
// sortie: 1 si l'insertion réussit, 0 sinon
// ce que fait la fonction: insère dans lst tous les noeuds du niveau niv de l'arbre
///////////////////
int insere_niveau(Arbre a, int niv, Liste *lst)
{
    if (a == NULL)
        return 1;
    if (niv < 0)
        return 1;

    if (niv == 0)
    {
        Cellule *c = alloue_cellule(a);
        if (c == NULL)
            return 0;
        insere_en_tete(lst, c);
        return 1;
    }

    return insere_niveau(a->fg, niv - 1, lst) &&
           insere_niveau(a->fd, niv - 1, lst);
}

///////////////////
// entrée: un arbre a, un pointeur sur une liste lst
// sortie: 1 si le parcours réussit, 0 sinon
// ce que fait la fonction: effectue un parcours en largeur naïf de l'arbre
///////////////////
int parcours_largeur_naif(Arbre a, Liste *lst)
{
    if (a == NULL)
        return 1;

    int hauteur = 0;
    Arbre temp = a;
    while (temp != NULL)
    {
        hauteur++;
        temp = temp->fg ? temp->fg : temp->fd;
    }

    for (int niveau = 0; niveau < hauteur; niveau++)
    {
        if (!insere_niveau(a, niveau, lst))
            return 0;
    }
    return 1;
}

///////////////////
// entrée: un arbre a, un pointeur sur une liste lst
// sortie: 1 si le parcours réussit, 0 sinon
// ce que fait la fonction: effectue un parcours en largeur de l'arbre en utilisant une file
///////////////////
int parcours_largeur(Arbre a, Liste *lst)
{
    if (a == NULL)
        return 1;

    File f = initialisation();
    if (f == NULL)
        return 0;

    if (!enfiler(f, a))
    {
        free(f);
        return 0;
    }

    while (!est_vide(f))
    {
        Noeud *n;
        if (!defiler(f, &n))
        {
            free(f);
            return 0;
        }

        Cellule *c = alloue_cellule(n);
        if (c == NULL)
        {
            free(f);
            return 0;
        }
        insere_en_tete(lst, c);

        if (n->fg && !enfiler(f, n->fg))
        {
            free(f);
            return 0;
        }
        if (n->fd && !enfiler(f, n->fd))
        {
            free(f);
            return 0;
        }
    }

    free(f);
    return 1;
}

///////////////////
// entrée: un arbre a, un niveau niv, un pointeur sur une liste lst, un pointeur sur un compteur nb_visite
// sortie: 1 si l'insertion réussit, 0 sinon
// ce que fait la fonction: insère les noeuds du niveau niv dans lst et compte le nombre de noeuds visités
///////////////////
int insere_niveau_V2(Arbre a, int niv, Liste *lst, int *nb_visite)
{
    (*nb_visite)++;
    if (a == NULL)
        return 1;
    if (niv < 0)
        return 1;

    if (niv == 0)
    {
        Cellule *c = alloue_cellule(a);
        if (c == NULL)
            return 0;
        insere_en_tete(lst, c);
        return 1;
    }

    return insere_niveau_V2(a->fg, niv - 1, lst, nb_visite) &&
           insere_niveau_V2(a->fd, niv - 1, lst, nb_visite);
}

///////////////////
// entrée: un arbre a, un pointeur sur une liste lst, un pointeur sur un compteur nb_visite
// sortie: 1 si le parcours réussit, 0 sinon
// ce que fait la fonction: effectue un parcours en largeur naïf et compte les noeuds visités
///////////////////
int parcours_largeur_naif_V2(Arbre a, Liste *lst, int *nb_visite)
{
    *nb_visite = 0;
    if (a == NULL)
        return 1;

    int hauteur = 0;
    Arbre temp = a;
    while (temp != NULL)
    {
        hauteur++;
        temp = temp->fg ? temp->fg : temp->fd;
    }

    for (int niveau = 0; niveau < hauteur; niveau++)
    {
        if (!insere_niveau_V2(a, niveau, lst, nb_visite))
            return 0;
    }
    return 1;
}

///////////////////
// entrée: un arbre a, un pointeur sur une liste lst, un pointeur sur un compteur nb_visite
// sortie: 1 si le parcours réussit, 0 sinon
// ce que fait la fonction: effectue un parcours en largeur avec une file et compte les noeuds visités
///////////////////
int parcours_largeur_V2(Arbre a, Liste *lst, int *nb_visite)
{
    *nb_visite = 0;
    if (a == NULL)
        return 1;

    File f = initialisation();
    if (f == NULL)
        return 0;

    if (!enfiler(f, a))
    {
        free(f);
        return 0;
    }

    while (!est_vide(f))
    {
        Noeud *n;
        if (!defiler(f, &n))
        {
            free(f);
            return 0;
        }

        (*nb_visite)++;
        Cellule *c = alloue_cellule(n);
        if (c == NULL)
        {
            free(f);
            return 0;
        }
        insere_en_tete(lst, c);

        if (n->fg && !enfiler(f, n->fg))
        {
            free(f);
            return 0;
        }
        if (n->fd && !enfiler(f, n->fd))
        {
            free(f);
            return 0;
        }
    }

    free(f);
    return 1;
}