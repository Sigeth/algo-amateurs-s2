#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "sauvegarde.h"
#include "moteur.h"
#include <string.h>
void initinfo(info a*){
a->x=0;
a->y=0;
a->previousX=0;
a->previousY=0;}
void sauvergarde(char* nomdesauvegarde,Astre *ptTerre,Astre *ptLune,Astre *ptSoleil,Astre *ptMercure,Astre *ptVenus,Astre *ptMars,Astre *ptJupiter,Astre *ptSaturne,Astre *ptNeptune,Astre *ptUranus ){
FILE* f=NULL;
f=fopen(nomdesauvegarde,"a");
if(f!=NULL){
fputs(nomdesauvegarde,f);
fclose(f);}
void nomdesauvegarde(){
	printf("nom de la sauvegarde :");
	char a[100];
	scanf("%s",a);
	FILE* f=NULL;
	f=fopen(a,"a");
	if(f!=NULL){
	fputs(a,f);
	fputs("\n",f);
	fclose(f);}
	FILE* fi=NULL;
}
void listesauvegarde(){
char a[100];
FILE* fi=fopen("pastouche","r");
if(fi!=NULL){
printf("voici la liste de vos sauvegarde :\n");
while(fscanf(fi,"%s",a) != EOF){
//fscanf(fi,"%s",a);
printf("%s \n",a);
}
fclose(fi);}}
