#include <stdlib.h>
#include <malloc.h>

typedef struct maillon {
    int x;
    struct maillon* suiv;
}maillon_t;

maillon_t* ajouter_fin(maillon_t *pliste, int val);
maillon_t* supprimer_debut(maillon_t *pliste, int *pval);

maillon_t* ajouter_fin(maillon_t *pliste, int val){

    //S'il n'y a aucun élément dans la liste chaînée
    if (pliste == NULL) {
        pliste = (maillon_t*)malloc(sizeof(maillon_t));
        pliste->x = val;
        pliste->suiv = NULL;
        return pliste;
    }

    maillon_t* tmp = pliste->suiv;

    //S'il n'y a qu'un seul élément dans la liste chaînée
    if (tmp == NULL) {
        tmp = (maillon_t*)malloc(sizeof(maillon_t));
        tmp->x = val;
        tmp->suiv = NULL;
        pliste->suiv = tmp;
        return pliste;
    }

    maillon_t* tmp2 = tmp->suiv;

    //S'il y a plus d'un élément dans la liste chaînée
    while (tmp != NULL) {

        if (tmp2 == NULL) {
            tmp2 = (maillon_t*)malloc(sizeof(maillon_t));
            tmp2->x = val;
            tmp->suiv = tmp2;
            tmp2->suiv = NULL;
            return pliste;
        }
        tmp = tmp->suiv;
        tmp2 = tmp->suiv;
    }
}

//*pval sert à modifier la valeur du pval passé en argument de la fonction appelée
maillon_t*supprimer_debut(maillon_t *pliste, int *pval) {

    //S'il n'y a aucun élément ou 1 seul dans la liste
    if (pliste == NULL || pliste->suiv == NULL) {
        if (pliste != NULL) {
            *pval = pliste->x;
            free(pliste);
            return NULL;
        }
        //Valeur -999 = n'importe quoi, quand on s'amuse à afficher la valeur supprimée d'une liste vide
        *pval = -999;
        return NULL;
    }

    //S'il y a plus d'1 élément
    maillon_t* tmp = pliste->suiv;

    *pval = pliste->x;//On modifie la valeur de pval avec celle de la valeur détachée

    free(pliste);

    return tmp;
}