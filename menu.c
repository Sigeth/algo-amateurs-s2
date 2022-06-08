#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

int menu(int choix) 
{
	switch(choix)
	{
		case 1:
			lancer_simulation();
			break;

		case 2:
			reprendre();
			break;

		case 3:
			sauvegarde();
			break;

		case 4:
			charger();
			break;

		case 5:
			quitter();
			break;
	}
	return 0;
}
