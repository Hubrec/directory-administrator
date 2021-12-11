#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "fonction.h"

const char* TabIntitules[7] = { "prenom","nom","ville","codePostal","telephone","email","profession" };

REPERTOIRE Importer(char* nom_fichier)
{
	REPERTOIRE rep;
	CLIENT client;
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
	rep.tabind = (int**)malloc(sizeof(int*) * 7);
	int j;
	for (i = 0; i < 7; i++) {
		rep.tabind[i] = (int*)malloc(sizeof(int) * rep.taille);
		for (j = 0; j < rep.taille; j++) {
			rep.tabind[i][j] = j;
		}
	}


	return rep;
}


void Afficher(REPERTOIRE rep, char* valeur, int tabind[])
{
	int i;
	int valeurInt = numero(valeur);
	switch (valeurInt)
	{
	case PRENOM:
		for (i = 0; i < rep.taille; i++) {
			printf("%s \n", rep.clients[tabind[i]].prenom);
		}
		break;
	case NOM:
		for (i = 0; i < rep.taille; i++) {
			printf("%s \n", rep.clients[tabind[i]].nom);
		}
		break;
	case VILLE:
		for (i = 0; i < rep.taille; i++) {
			printf("%s \n", rep.clients[tabind[i]].ville);
		}
		break;
	case CP:
		for (i = 0; i < rep.taille; i++) {
			printf("%s \n", rep.clients[tabind[i]].code_postal);
		}
		break;
	case TEL:
		for (i = 0; i < rep.taille; i++) {
			printf("%s \n", rep.clients[tabind[i]].telephone);
		}
		break;
	case MAIL:
		for (i = 0; i < rep.taille; i++) {
			printf("%s \n", rep.clients[tabind[i]].email);
		}
		break;
	case PROF:
		for (i = 0; i < rep.taille; i++) {
			printf("%s \n", rep.clients[tabind[i]].profession);
		}
		break;
	default:
		for (i = 0; i < rep.taille; i++) {
			printf("%s \n", rep.clients[tabind[i]].prenom);
			printf("%s ", rep.clients[tabind[i]].nom);
			printf("%s ", rep.clients[tabind[i]].ville);
			printf("%s ", rep.clients[tabind[i]].code_postal);
			printf("%s ", rep.clients[tabind[i]].telephone);
			printf("%s ", rep.clients[tabind[i]].email);
			printf("%s ", rep.clients[tabind[i]].profession);
		}
		break;
	}
}

int compare(CLIENT c1, CLIENT c2, int champ) {
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
}

void triindirecte(REPERTOIRE rep, int champ)
{
	CLIENT client;
	int i, j, tmp, f;

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

int numero(char* nom) {
	int champ;
	int j;
	for (j = 0; j < 7; j++) {
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
}

void InterfaceTerminal(REPERTOIRE rep)
{
	int fin = 0;
	char commande[20];
	char arg[20];
	CLIENT client;
	int* tabind;

	tabind = malloc(sizeof(int) * rep.taille);
	int tabtaille = rep.taille;


	do {
		printf("les differents commandes actuellement disponibles sont :\n");
		printf("    - close \n");
		printf("    - afficher \n");
		printf("    - trier \n\n");
		printf("*********************\n");
		printf("entrer une commande : ");
		fgets(commande, 20, stdin);

		//enlever le retour charriot
		retourchariot(commande);
		printf("\n");


		if (!strcmp(commande, "close")) {
			printf("ca marche");
			fin = 1;
		}

		if (!strcmp(commande, "afficher")) {

			printf("arguments pour affichage : \n");
			int i;
			for (i = 0; i < 7; i++) {
				printf("-   %s\n", TabIntitules[i]);
			}

			printf("entrer un argument : ");
			fgets(arg, 20, stdin);
			if (arg[strlen(arg) - 1] == '\n') {
				arg[strlen(arg) - 1] = '\0';
			}

			Afficher(rep, arg, rep.tabind[numero(arg)]);
		}

		if (!strcmp(commande, "trier")) {
			fgets(arg, 20, stdin);
			if (arg[strlen(arg) - 1] == '\n') {
				arg[strlen(arg) - 1] = '\0';
			}
			int champ = numero(arg);
			triindirecte(rep, champ);
			printf("le tableau a bien ete trie\n\n");
		}

	} while (fin != 1);
}
