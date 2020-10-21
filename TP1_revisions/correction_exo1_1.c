#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>		//pour utiliser le rand() => "man 3 rand" pour accéder aux pages du manuel sinon c'est la commande rand
#include <time.h>		//pour utiliser le time()
#include <unistd.h>		//usleep
#include <semaphore.h>  //uniquement pour version avec semaphore
#include <pthread.h>    //pour la gestion des threads et pour les mutex

int mon_rand(int a, int b);

/* VERSION AVEC MUTEX*/
pthread_mutex_t m1;
pthread_mutex_t m2;

void version_avec_mutex(void);
void* thread_1_mutex();
void* thread_2_mutex();

/* VERSION AVEC SEMAPHORE*/
void version_avec_sem(void);
void* thread_1_sem();
void* thread_2_sem();


int main(void)
{
	pthread_t mes_threads[2];

	srand(time(NULL));

	//il faut bloquer le premier thread dès le départ
	pthread_mutex_lock(&m1);
	pthread_mutex_lock(&m2);

    //on peut également tester en inversant les lancements
	pthread_create(&mes_threads[0],NULL,thread_1,NULL);
	usleep(mon_rand(10000,1000000)); //vérifier que tout fonctionne bien
	pthread_create(&mes_threads[1],NULL,thread_2,NULL);

	pthread_join(mes_threads[0],NULL);
	pthread_join(mes_threads[1],NULL);

	printf("\n");
	return 0;
}

int mon_rand(int a, int b)
{
	//on suppose que b>a !
	return ( rand()%(b-a) ) + a;
}

void* thread_1_mutex()
{
	usleep(mon_rand(10000,1000000));
	printf("je ");
	pthread_mutex_unlock(&m1);
	pthread_mutex_lock(&m2);
	usleep(mon_rand(10000,1000000));
	printf("mes ");
	pthread_mutex_unlock(&m1);

	return NULL;
}

void* thread_2_mutex()
{
	pthread_mutex_lock(&m1);
	usleep(mon_rand(10000,1000000));
	printf("synchronise ");
	pthread_mutex_unlock(&m2);
	pthread_mutex_lock(&m1);
	usleep(mon_rand(10000,1000000));
	printf("threads ");

	return NULL;
}

void* thread_1_sem()
{
	usleep(mon_rand(10000,1000000));
	printf("je ");
	pthread_mutex_unlock(&m1);
	pthread_mutex_lock(&m2);
	usleep(mon_rand(10000,1000000));
	printf("mes ");
	pthread_mutex_unlock(&m1);

	return NULL;
}

void* thread_2_sem()
{
	pthread_mutex_lock(&m1);
	usleep(mon_rand(10000,1000000));
	printf("synchronise ");
	pthread_mutex_unlock(&m2);
	pthread_mutex_lock(&m1);
	usleep(mon_rand(10000,1000000));
	printf("threads ");

	return NULL;
}
/*
sem_init(&caselibre,0,BUFFER_SIZE);
sem_init(&caseocc,0,0);
*/