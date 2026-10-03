# DM1 – Parcours en largeur d’arbres binaires

Ce projet, réalisé dans le cadre du DM1 de L2 Informatique, compare deux méthodes de parcours en largeur d’un arbre binaire :  
- **Parcours naïf** (niveau par niveau)  
- **Parcours optimisé** (avec file chaînée)

---

##  Arborescence du dépôt

```
.
├── DM_1.h                # Structures et prototypes
├── DM_1.c                # Implémentation des parcours et de la file
├── main.c                # Programme de test et banc d’essais
├── Rapport.pdf           # Rapport détaillé (complexités, résultats)
```

---

##  Compilation

Vous pouvez compiler manuellement avec **clang** ou **gcc** :

```bash
# Génération des fichiers objets
gcc -Wall -Wextra DM_1.c main.c -o DM_1
```



---

## ▶ Exécution

```bash
./DM_1
```

Cela lancera :
1. Les tests unitaires de **liste** et **file**  
2. La construction et l’affichage d’arbres (complet / filiforme)  
3. La comparaison des deux parcours (nombre de visites et ordre)  
4. Les tests de performance pour différentes hauteurs

---

##  Résultats clés

| Arbre       | Taille/Hauteur | Visites (file) | Visites (naïf) | Temps naïf (s) | Temps file (s) |
|-------------|----------------|----------------|----------------|----------------|----------------|
| Complet     | h = 5          | 31             | 45             | …              | …              |
| Complet     | h = 7          | 127            | …              | …              | …              |
| Complet     | h = 10         | 2047           | …              | …              | …              |

> **Observations** :  
> - Le parcours **optimisé** visite chaque nœud **exactement une fois** → O(n)  
> - Le parcours **naïf** peut atteindre O(n²) sur arbres filiformes  

(Consultez `Rapport.pdf` pour le tableau complet et l’analyse détaillée.)

---

##  Concepts et structures

- **Structures** :  
  - `Noeud` / `Arbre`       → nœuds et sous-arbres  
  - `Cellule` / `Liste`     → maillons pour implémenter la file  
  - `File` (Queue)          → file chaînée (front/back, taille)  

- **Fonctions principales** :  
  - `parcours_largeur_naif`  
  - `parcours_largeur`  
  - Versions **_V2** pour **comptage** des visites (`parcours_largeur_naif_V2`, `parcours_largeur_V2`)

---

##  Auteur

**Vincent PLESSY**  
Étudiant en L2 Informatique (année 2024–2025)
