#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonction.h"

REPERTOIRE Importer(char nom_fichier[]) //responsable fonction : Guerin
{
	REPERTOIRE rep;
	rep.taille = 0;

	int i;
	//on ouvre le fichier
	FILE* fichier = fopen(nom_fichier, "r");

	//message d'erreur si fichier est vide ou non trouve
	if (fichier == NULL)
	{
		printf("Impossible d'ouvrir l'annuaire");
		exit(EXIT_FAILURE);
	}

	char buffer[300];
	do {
		fgets(buffer, 300, fichier);
		rep.taille++;
	} while (!feof(fichier));

	rep.taille--;

	//malloc allocation dynamique
	rep.clients = malloc(sizeof(CLIENT) * rep.taille);

	rewind(fichier);

	for (i = 0; i < rep.taille; i++) {
		fgets(buffer, 300, fichier);
		int j = 0;
		int k;
		for (k = 0; k < 6; k++) {
			int debut = j;
			while (buffer[j] != ',') {
				j++;
			}
			buffer[j] = '\0';
			char* champ = strdup(buffer + debut);
			switch (k) {
			case PRENOM:
				rep.clients[i].prenom = champ;
				break;
			case NOM:
				rep.clients[i].nom = champ;
				break;
			case VILLE:
				rep.clients[i].ville = champ;
				break;
			case CP:
				rep.clients[i].code_postal = champ;
				break;
			case TEL:
				rep.clients[i].telephone = champ;
				break;
			case MAIL:
				rep.clients[i].email = champ;
				break;
			}
			j++;
		}
		char* champ = strdup(buffer + j);
		retourchariot(champ);
		rep.clients[i].profession = champ;
	}
	fclose(fichier);
	// allocation et initialisation des tableaux d'indices
	rep.tabind = malloc(sizeof(int*) * 7);
	int j;
	for (i = 0; i < 7; i++) {
		rep.tabind[i] = malloc(sizeof(int) * rep.taille);
		for (j = 0; j < rep.taille; j++) {
			rep.tabind[i][j] = j;
		}
	}
	return rep;
}

void sauvegarder(REPERTOIRE rep) //responsable fonction : Toinon
{

	int v;
	FILE* fichier = fopen("annuaire5000.csv", "w");

	if (fichier == NULL)
	{
		printf(" impossible de sauvegarder");
		exit(EXIT_FAILURE);
	}

	for (v = 0; v < rep.taille; v++) {

		fprintf(fichier, "%s,", rep.clients[v].prenom);
		fprintf(fichier, "%s,", rep.clients[v].nom);
		fprintf(fichier, "%s,", rep.clients[v].ville);
		fprintf(fichier, "%s,", rep.clients[v].code_postal);
		fprintf(fichier, "%s,", rep.clients[v].telephone);
		fprintf(fichier, "%s,", rep.clients[v].email);
		fprintf(fichier, "%s\n", rep.clients[v].profession);
	}

	printf(" \nsauvegarde accomplie !\n\n");

	fclose(fichier);
}

REPERTOIRE liberte(REPERTOIRE rep) { //responsable fonction : Guerin Toinon

	int i;

	for (i = 0; i < 7; i++) {
		free(rep.tabind[i]);
	}

	free(rep.tabind);

	for (i = 0; i < rep.taille; i++) {
		free(rep.clients[i].prenom);
		free(rep.clients[i].nom);
		free(rep.clients[i].ville);
		free(rep.clients[i].code_postal);
		free(rep.clients[i].telephone);
		free(rep.clients[i].email);
		free(rep.clients[i].profession);
	}

	free(rep.clients);
	return rep;
}