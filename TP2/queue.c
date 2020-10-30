#include "linkedList.c"

typedef struct queue {
    maillon_t* bottom;
}queue_t;

void init_queue(queue_t*);
int push_queue(queue_t *, int);
int pop_queue(queue_t *, int *);
void display_queue(queue_t *);
void display_queue_recursive(queue_t* q, maillon_t* qCurr);
int is_empty(queue_t* q);

//Initialise la file
void init_queue(queue_t* q) {
    q->bottom = NULL;
}

//Ajoute un nouvel entier à la file
int push_queue(queue_t* q, int val) {
    q->bottom = ajouter_fin(q->bottom, val);
    return 1;
}

//Supprime le 1er élément de la file
int pop_queue(queue_t* q, int* pval) {
    q->bottom = supprimer_debut(q->bottom, pval);
    //-999 est la valeur affectée à pval par supprimer_début au cas où on chercherait à supprimer un élément d'une liste vide
    if(*pval == -999)
        return 0;
    return 1;
}

//Determines wether the queue is empty or not
int is_empty(queue_t* q){
    return q->bottom == NULL;
}