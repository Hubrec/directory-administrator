#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonction.h"

const char* TabIntitules[8] = { "prenom","nom","ville","codepostal","telephone","email","profession","tout" };
const int espacement[] = { 25,30,25,10,20,45,20 };


int numero(char* nom) { //responsable fonction : Guerin
	int champ = -1;
	int j;
	for (j = 0; j < 8; j++) {
		if (!strcmp(nom, TabIntitules[j])) {
			champ = j;
		}
	}
	return champ;
} 

void retourchariot(char* chaine) { //responsable fonction : Guerin
	if (chaine[strlen(chaine) - 1] == '\n') {
		chaine[strlen(chaine) - 1] = '\0';
	}

	if (chaine[strlen(chaine) - 1] == ' ') {
		chaine[strlen(chaine) - 1] = '\0';
	}
}

char* RecupereChamp(CLIENT client, int numerochamp) { //responsable fonction : Guerin
	switch (numerochamp) {
		case PRENOM:
			return(client.prenom);
			break;
		case NOM:
			return(client.nom);
			break;
		case VILLE:
			return(client.ville);
			break;
		case CP:
			return(client.code_postal);
			break;
		case TEL:
			return(client.telephone);
			break;
		case MAIL:
			return(client.email);
			break;
		case PROF:
		default:
			return(client.profession);
			break;
	}
	return NULL;
}

int compare(CLIENT c1, CLIENT c2, int champ) { //responsable fonction : Guerin
	int resultat;
	switch (champ) {
		case NOM:
			resultat = strcmp(c1.nom, c2.nom);
			if (resultat)
				return resultat;
			return strcmp(c1.prenom, c2.prenom);
		case PRENOM:
			return strcmp(c1.prenom, c2.prenom);
		case VILLE:
			return strcmp(c1.ville, c2.ville);
		case CP:
			return strcmp(c1.code_postal, c2.code_postal);
		case TEL:
			return strcmp(c1.telephone, c2.telephone);
		case MAIL:
			return strcmp(c1.email, c2.email);
		case PROF:
			return strcmp(c1.profession, c2.profession);
			
	}
	return -1;
}

int Afficher(REPERTOIRE rep, int tabcol[], int tabfiltre[], char* filtre, int champ) { //responsable fonction : Guerin

	int i, j, q;
	int combien = 0;

	for (i = 0; i < rep.taille; i++) { // pour tous les clients

		int affiche = 0;

		for (j = 0; j < 7 && !affiche; j++) {
			if (filtre == NULL) {
				if (RecupereChamp(rep.clients[rep.tabind[champ][i]], j)[0] == '\0') {
					affiche = 1;
				}
			}
			else if (tabfiltre[j] == 1) {
				if (strstr(RecupereChamp(rep.clients[rep.tabind[champ][i]], j), filtre)) {
					affiche = 1;
				}
			}
		}
		if (affiche) {
			for (j = 0; j < 7; j++) {
				if (tabcol[j]) { // si on doit afficher ce champ
					printf(" %*s |", espacement[j], RecupereChamp(rep.clients[rep.tabind[champ][i]], j));
				}
			}
			combien++;
			printf("\n");
		}
	}
	return combien;
}

void triinsertion(REPERTOIRE rep, int champ) //responsable fonction : Toinon
{
	//CLIENT client;
	int i, j, tmp;

	//tri insertion
	for (i = 1; i < rep.taille; i++) {

		j = i;

		while (j > 0 && compare(rep.clients[rep.tabind[champ][j - 1]], rep.clients[rep.tabind[champ][j]], champ) > 0) {
		
			tmp = rep.tabind[champ][j];
			rep.tabind[champ][j] = rep.tabind[champ][j - 1];
			rep.tabind[champ][j - 1] = tmp;
			j--;
		}
	}
}

void tripeigne(REPERTOIRE rep, int champ) //responsable fonction : Guerin
{
	
	int interval = rep.taille;
	int echange = 0;
	int tmp = 0;

	while (interval > 1 || echange) {
		interval = (interval / (4./3.));

		if (interval < 1) interval = 1;

		int i = 0;
		echange = 0;

		while (i < rep.taille - interval) {
			if ( compare(rep.clients[rep.tabind[champ][i]], rep.clients[rep.tabind[champ][i + interval]], champ) > 0 ) {

				tmp = rep.tabind[champ][i];
				rep.tabind[champ][i] = rep.tabind[champ][i + interval];
				rep.tabind[champ][i + interval] = tmp;

				echange = 1;
			}
			i++;
		}
	}
}

REPERTOIRE ajout(REPERTOIRE rep, CLIENT c) //responsable fonction : Guerin
{

	rep.taille++;
	rep.clients = realloc(rep.clients, sizeof(CLIENT) * rep.taille);

	if (rep.clients == NULL) {
		free(rep.clients);
		exit(EXIT_FAILURE);
	}

	int j;
	for (j = 0; j < 7; j++) {
		rep.tabind[j] = realloc(rep.tabind[j], sizeof(int) * rep.taille);
		rep.tabind[j][rep.taille - 1] = rep.taille - 1;
	}

	rep.clients[rep.taille - 1].prenom = strdup(c.prenom);
	rep.clients[rep.taille - 1].nom = strdup(c.nom);
	rep.clients[rep.taille - 1].ville = strdup(c.ville);
	rep.clients[rep.taille - 1].code_postal = strdup(c.code_postal);
	rep.clients[rep.taille - 1].telephone = strdup(c.telephone);
	rep.clients[rep.taille - 1].email = strdup(c.email);
	rep.clients[rep.taille - 1].profession = strdup(c.profession);

	return rep;
}

REPERTOIRE suppression(REPERTOIRE rep, int inditem) { //responsable fonction : Guerin

	rep.taille--;
	rep.clients[inditem] = rep.clients[rep.taille];

	rep.clients = realloc(rep.clients, sizeof(CLIENT) * rep.taille);

	if (rep.clients == NULL) {
		free(rep.clients);
		exit(EXIT_FAILURE);
	}

	int j;
	for (j = 0; j < 7; j++) {
		rep.tabind[j] = realloc(rep.tabind[j], sizeof(int) * rep.taille);
	}

	int i;
	for (i = 0; i < 7; i++) {
		for (j = 0; j < rep.taille; j++)
			rep.tabind[i][j] = j;
	}

	for (i = 0; i < 7; i++) {
		tripeigne(rep, i);
	}

	return rep;
}

REPERTOIRE modifier(REPERTOIRE rep, int inditem, int tabelement[], CLIENT cl) { //responsable fonction : Toinon

	if (tabelement[0] == 1) {
		if (cl.prenom[0] != '\O') rep.clients[inditem].prenom = strdup(cl.prenom);
	}

	if (tabelement[1] == 1) {
		if (cl.nom[0] != '\O') rep.clients[inditem].nom = strdup(cl.nom);
	}

	if (tabelement[2] == 1) {
		if (cl.ville[0] != '\O') rep.clients[inditem].ville = strdup(cl.ville);
	}

	if (tabelement[3] == 1) {
		if (cl.code_postal[0] != '\O') rep.clients[inditem].code_postal = strdup(cl.code_postal);
	}

	if (tabelement[4] == 1) {
		if (cl.telephone[0] != '\O') rep.clients[inditem].telephone = strdup(cl.telephone);
	}

	if (tabelement[5] == 1) {
		if (cl.email[0] != '\O') rep.clients[inditem].email = strdup(cl.email);
	}

	if (tabelement[6] == 1) {
		if (cl.profession[0] != '\O') rep.clients[inditem].profession = strdup(cl.profession);
	}

	return rep;
}

int recherche(REPERTOIRE rep, CLIENT c, int * dernier) { //responsable fonction : Toinon

	int indicedep = 0;
	int indicefin = rep.taille - 1;
	int milieu = rep.taille / 2;

	while (indicedep < indicefin)
	{
		milieu = (indicedep + indicefin) / 2;
		if (compare(rep.clients[rep.tabind[NOM][milieu]], c, NOM) == 0) {
			int premier = milieu;
			while (premier>=0 && compare(rep.clients[rep.tabind[NOM][premier]], c, NOM) == 0) {
				premier--;
			}
			premier++;
			*dernier = premier + 1;
			while (*dernier < rep.taille && compare(rep.clients[rep.tabind[NOM][*dernier]], c, NOM) == 0) {
				(*dernier)++;
			}
			(*dernier)--;
			return(premier);
		}
		else if (compare(rep.clients[rep.tabind[NOM][milieu]], c, NOM) < 0)
		{
			indicedep = milieu + 1;
		}
		else indicefin = milieu - 1;
	}
	return(-1);
}