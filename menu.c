#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

int main(void) 
{
	int a=0;
	printf("1 - Lancer simulation\n");
	printf("2 - Reprendre simulation\n");
	printf("3 - Sauvegarder simulation\n");
	printf("4 - Charger simulation\n");
	printf("5 - Quitter\n");
	printf("que voulez vous faire ?");
	scanf("%d",&a);
	switch(a)
	{
		case 1:
			lancer_simulation();
			break;

		case 2:
			reprendre()
			break;

		case 3:
			sauvegarde()
			break;

		case 4:
			charger()
			break;

		case 5:
			quitter()
			break;

	}
}
