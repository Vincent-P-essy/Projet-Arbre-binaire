#ifndef STRUCTURES_ET_PROTOTYPES  // Garde d'inclusion
#define STRUCTURES_ET_PROTOTYPES

// Structure pour un nœud d'arbre binaire
typedef struct _noeud {
   int valeur;  // Valeur stockée dans le nœud
   struct _noeud *fg, *fd;  // Pointeurs vers fils gauche et droit
} Noeud, *Arbre;

// Structure pour un maillon de liste chaînée
typedef struct cell {
   Noeud *noeud;  // Pointeur vers un nœud d'arbre 
   struct cell *suivant;  // Pointeur vers le maillon suivant
} Cellule, *Liste;

// Structure pour une file d'attente
typedef struct file {
   Liste debut;  // Pointeur vers le début de la file (sortie)
   Liste fin;    // Pointeur vers la fin de la file (entrée)
   int taille;   // Nombre d'éléments dans la file
} Queue, *File;

// Fonctions de manipulation de listes
Cellule *alloue_cellule(Noeud *n);  // Alloue une nouvelle cellule
void insere_en_tete(Liste *l, Cellule *c);  // Insère une cellule en tête
Cellule *extrait_tete(Liste *l);  // Extrait la première cellule
void affiche_liste_renversee(Liste l);  // Affiche la liste à l'envers

// Fonctions de manipulation de files
File initialisation();  // Crée une file vide
int est_vide(File f);  // Teste si la file est vide
int enfiler(File f, Noeud *n);  // Ajoute un nœud en fin de file
int defiler(File f, Noeud **sortant);  // Retire le premier nœud

// Fonctions de manipulation d'arbres
Noeud *alloue_noeud(int val, Arbre fg, Arbre fd);  // Crée un nœud
int construit_complet(int h, Arbre *a);  // Construit un arbre complet
int construit_filiforme_aleatoire(int h, Arbre *a, int graine);  // Construit un arbre filiforme

// Fonctions de parcours
int insere_niveau(Arbre a, int niv, Liste *lst);  // Insère les nœuds d'un niveau
int parcours_largeur_naif(Arbre a, Liste *lst);  // Parcours naïf
int parcours_largeur(Arbre a, Liste *lst);  // Parcours avec file

// Versions avec comptage des visites
int insere_niveau_V2(Arbre a, int niv, Liste *lst, int *nb_visite);
int parcours_largeur_naif_V2(Arbre a, Liste *lst, int *nb_visite);
int parcours_largeur_V2(Arbre a, Liste *lst, int *nb_visite);

#endif