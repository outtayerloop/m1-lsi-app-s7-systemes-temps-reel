/*Correction MODULE SYSTEMES TEMPS REEL - EFREI - CALCADO FABIEN*/

#define CONSTANT_PROC 710000000 //A determiner pour votre machine ! ==>
//peut etre fait de maniere automatique mais ce n'est pas le sujet du TP

void do_work(unsigned int nb_secondes);

/*fonction simulant un travail a effectuer (attente active)*/
void do_work(unsigned int nb_secondes)
{
	unsigned int i = CONSTANT_PROC * nb_secondes; //attention a ne pas utiliser un int pour eviter un overflow

	while(i>0)
	{
		asm volatile("nop");
		i--;
	}

	return;
}

/* MAIN */
int main()
{
    //ne pas faire d'affichage avec un printf("") sinon il y aura des fluctuations encore plus importantes sur le temps d'execution
    do_work(1u);

	return 0;
}