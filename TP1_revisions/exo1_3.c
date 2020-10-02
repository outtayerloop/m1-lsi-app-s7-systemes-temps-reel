#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
// #include <time.h>		//pour utiliser le time()
#include <unistd.h>		//usleep
#include <semaphore.h>

#define TRUE 1
#define FALSE 0

#define T_TAMPON 5
#define NB_THREADS_LECTEUR	2
#define NB_THREADS_ECRIVAIN	2

/*******************
 *  MACRO FONCTIONS
 * *****************/
//juste pour avoir les mêmes notations qu'en ALGO
#define P(x) sem_wait(x)
#define V(x) sem_post(x)

/******************************************
 *  VARIABLES PARTAGEES ENTRE LES THREADS
 * ****************************************/
char tampon[T_TAMPON]; //partager entre les threads

int tete_lecture=0, tete_ecriture=0; //partager si plusieurs threads sinon peuvent être locales
sem_t cases_occ, cases_lib; 	 //nbr de cases occupées et nbr de cases libres


/*****************
 *  PROTOTYPES
 * ***************/
int mon_rand(int a, int b);
char lire_tampon();
void* lecteur();
void ecrire_tampon(char lettre);
void* ecrivain();

/************************
 *  FONCTION PRINCIPALE
 * **********************/
int main(void)
{
    pthread_t thread_lecteur;
    pthread_t thread_ecrivain;

    sem_init(&cases_occ,0,0);
    sem_init(&cases_lib,0,T_TAMPON);

    //dans ce programme il n'y a pas de warning car on cast un pointeur vers un pointeur
    pthread_create(&thread_ecrivain,NULL,ecrivain,NULL);
    pthread_create(&thread_lecteur,NULL,lecteur,NULL);

    pthread_join(thread_ecrivain,NULL);
    pthread_join(thread_lecteur,NULL);

    printf("\n");
    return 0;
}

/************************
 *  CODES DES THREADS
 * **********************/
char lire_tampon()
{
    //la manipulation de tete_lecture est à protéger s'il y a
    //plusieurs threads lecteur

    char lettre;

    usleep(mon_rand(100000,1000000)); //permet de "désynchroniser" les threads
    //on évite des lectures "par paquets"
    lettre = tampon[tete_lecture];
    printf("Je lis le %c\n",lettre); //lecture dans la case tete_lecture du tampon
    tete_lecture = (tete_lecture + 1) % T_TAMPON;

    return lettre;
}

void* lecteur()
{
    char lettre;
    do
    {
        P(&cases_occ);

        lettre=lire_tampon();

        V(&cases_lib);
    }while(lettre!='\0');

    printf("**Lecteur termine...**\n");
    return NULL;
}


void ecrire_tampon(char lettre)
{
    //la manipulation de tete_ecriture est à protéger s'il y a
    //plusieurs threads écrivain

    usleep(mon_rand(100000,1000000)); //permet de "désynchroniser" les threads
    //on évite des ecritures "par paquets"
    printf("\tJ ecris le %c\n",lettre); //ecriture dans la case tete_ecriture du tampon
    tampon[tete_ecriture] = lettre;
    tete_ecriture = (tete_ecriture + 1) % T_TAMPON;

    return;
}

void* ecrivain()
{
    char mot[]="Bonjour";
    int pos=0;
    int fin = FALSE;

    while(fin != TRUE)
    {
        if(mot[pos]=='\0')
            fin = TRUE;

        P(&cases_lib);

        ecrire_tampon(mot[pos]);

        V(&cases_occ);
        pos++;
    }

    printf("**Ecrivain termine...**\n");
    return NULL;
}

int mon_rand(int a, int b)
{
    //on suppose que b>a !
    return ( rand()%(b-a) ) + a;
}