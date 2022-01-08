#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonction.h"

const char* TabIntitules[8] = { "prenom","nom","ville","codepostal","telephone","email","profession","tout" };
const int espacement[] = { 25,30,25,10,20,45,20 };


int numero(char* nom) {
	int champ = -1;
	int j;
	for (j = 0; j < 8; j++) {
		if (!strcmp(nom, TabIntitules[j])) {
			champ = j;
		}
	}
	return champ;
}

void retourchariot(char* chaine) {
	if (chaine[strlen(chaine) - 1] == '\n') {
		chaine[strlen(chaine) - 1] = '\0';
	}

	if (chaine[strlen(chaine) - 1] == ' ') {
		chaine[strlen(chaine) - 1] = '\0';
	}
}

char* RecupereChamp(CLIENT client, int numerochamp) { //responsable fonction : Guerin Toinon
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
	return -1;
}

int compare(CLIENT c1, CLIENT c2, int champ) { //responsable fonction : Guerin Toinon
	switch (champ) {
		case NOM:
			return strcmp(c1.nom, c2.nom);
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

int Afficher(REPERTOIRE rep, int tabcol[], int tabfiltre[], char* filtre, int champ) { //responsable fonction : Guerin Toinon

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

void Afficher2(REPERTOIRE rep, char* valeur, int tab[]) //responsable fonction : Guerin Toinon
{
	int i, v = 0;
	int valeurInt = numero(valeur);
	switch (valeurInt)
	{
	case PRENOM:
		for (i = 0; i < rep.taille; i++) {
			printf("%s \n", rep.clients[tab[i]].prenom);
		}
		break;
	case NOM:
		for (i = 0; i < rep.taille; i++) {
			printf("%s \n", rep.clients[tab[i]].nom);
		}
		break;
	case VILLE:
		for (i = 0; i < rep.taille; i++) {
			printf("%s \n", rep.clients[tab[i]].ville);
		}
		break;
	case CP:
		for (i = 0; i < rep.taille; i++) {
			printf("%s \n", rep.clients[tab[i]].code_postal);
		}
		break;
	case TEL:
		for (i = 0; i < rep.taille; i++) {
			printf("%s \n", rep.clients[tab[i]].telephone);
		}
		break;
	case MAIL:
		for (i = 0; i < rep.taille; i++) {
			printf("%s \n", rep.clients[tab[i]].email);
		}
		break;
	case PROF:
		for (i = 0; i < rep.taille; i++) {
			printf("%s \n", rep.clients[tab[i]].profession);
		}
		break;
	case TOUT:
		for (i = 0; i < rep.taille; i++) {
			printf("%25s", rep.clients[i].prenom);
			printf("%25s", rep.clients[i].nom);
			printf("%25s", rep.clients[i].ville);
			printf("%10s", rep.clients[i].code_postal);
			printf("%20s", rep.clients[i].telephone);
			printf("%45s", rep.clients[i].email);
			printf("%20s\n", rep.clients[i].profession);
		}
		break;
	default:

		printf("ERREUR SYNTAXE 2\n");
	}
}

void triinsertion(REPERTOIRE rep, int champ) //responsable fonction : Guerin Toinon
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

void tripeigne(REPERTOIRE rep, int champ) //responsable fonction : Guerin Toinon
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

REPERTOIRE ajout(REPERTOIRE rep) //responsable fonction : Guerin Toinon
{

	rep.taille++;
	rep.clients = realloc(rep.clients, sizeof(CLIENT) * rep.taille);

	if (rep.clients == NULL) {
		printf(" echec de reallocation\n");
		free(rep.clients);
		exit(EXIT_FAILURE);
	}

	int j;
	for (j = 0; j < 7; j++) {
		rep.tabind[j] = realloc(rep.tabind[j], sizeof(int) * rep.taille);
		rep.tabind[j][rep.taille - 1] = rep.taille - 1;
	}

	char buffer[50];

	printf(" -> saisissez le prenom : ");
	fgets(buffer, 30, stdin);
	retourchariot(buffer);
	rep.clients[rep.taille - 1].prenom = strdup(buffer);

	printf(" -> saisissez le nom : ");
	fgets(buffer, 30, stdin);
	retourchariot(buffer);
	rep.clients[rep.taille - 1].nom = strdup(buffer);

	printf(" -> saisissez la ville : ");
	fgets(buffer, 20, stdin);
	retourchariot(buffer);
	rep.clients[rep.taille - 1].ville = strdup(buffer);

	printf(" -> saisissez le code postal : ");
	fgets(buffer, 10, stdin);
	retourchariot(buffer);
	rep.clients[rep.taille - 1].code_postal = strdup(buffer);

	printf(" -> saisissez le numero de telephonne : ");
	fgets(buffer, 15, stdin);
	retourchariot(buffer);
	rep.clients[rep.taille - 1].telephone = strdup(buffer);

	printf(" -> saisissez l'email : ");
	fgets(buffer, 40, stdin);
	retourchariot(buffer);
	rep.clients[rep.taille - 1].email = strdup(buffer);

	printf(" -> saisissez la profession : ");
	fgets(buffer, 30, stdin);
	retourchariot(buffer);
	rep.clients[rep.taille - 1].profession = strdup(buffer);

	printf("\n vous avez ajoute 1 nouveau client\n\n");
	return rep;
}

REPERTOIRE suppression(REPERTOIRE rep, int inditem) { // en construction

	
	rep.taille--;

	rep.clients[inditem].prenom = strdup(rep.clients[rep.taille].prenom);
	rep.clients[inditem].nom = strdup(rep.clients[rep.taille].nom);
	rep.clients[inditem].ville = strdup(rep.clients[rep.taille].ville);
	rep.clients[inditem].code_postal = strdup(rep.clients[rep.taille].code_postal);
	rep.clients[inditem].telephone = strdup(rep.clients[rep.taille].telephone);
	rep.clients[inditem].email = strdup(rep.clients[rep.taille].email);
	rep.clients[inditem].profession = strdup(rep.clients[rep.taille].profession);

	rep.clients[inditem] = rep.clients[rep.taille];

	rep.clients = realloc(rep.clients, sizeof(CLIENT) * rep.taille);

	if (rep.clients == NULL)
	{
		printf(" echec de reallocation\n");
		free(rep.clients);
		exit(EXIT_FAILURE);
	}


	int j;
	for (j = 0; j < 7; j++) {
		rep.tabind[j][inditem] = rep.tabind[j][rep.taille];
	}
	for (j = 0; j < 7; j++) {
		rep.tabind[j] = realloc(rep.tabind[j], sizeof(int) * rep.taille);
	}

	return rep;
}