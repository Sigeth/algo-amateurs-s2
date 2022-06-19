typedef struct info{
	float x;
	float y;
 	float previousX;
    	float previousY;}info;
void nomdesauvegarde(ElementAstre *ptElementAstreInitial);
void listesauvegarde();
void delsauvegarde();
void sauvegarde(char a,ElementAstre *ptElementAstreInitial);
ElementAstre* loadsave(char a,ElementAstre *ptElementAstreInitial);
