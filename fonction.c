#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonction.h"

const char * TabIntitules[8] = { "prenom","nom","ville","codepostal","telephone","email","profession","tout"};
const int espacement[] = { 25,25,25,10,20,45,20 };

REPERTOIRE Importer(char* nom_fichier)
{
	REPERTOIRE rep;
	rep.taille = 0;

	int i;
	//on ouvre le fichier
	FILE * fichier = fopen(nom_fichier, "r");

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

char* RecupereChamp(CLIENT c, int numerochamp) {
	switch (numerochamp) {
		case PRENOM:
			return(c.prenom);
			break;
		case NOM:
			return(c.nom);
			break;
		case VILLE:
			return(c.ville);
			break;
		case CP:
			return(c.code_postal);
			break;
		case TEL:
			return(c.telephone);
			break;
		case MAIL:
			return(c.email);
			break;
		case PROF:
			return(c.profession);
			break;
	}
	return NULL;
}

void Afficher(REPERTOIRE rep, int tabcol[], char* filtre) {

	/*Il faut en entrée :
		de quoi afficher juste les colonnes voulues (tableau de int)

		utiliser strstr(partie, chaine); pour le filtre et comparer avec toutes les cases du tableau

		plusieurs niveaux d'indentation !!

			( for ) premier niveau d'indentation : boucle pour toutes les lignes ( 1 ligne = 1 client )
				( if ) deuxieme niveau d'indentation : rechercher dans chaque ligne si on a la correspondance ( filtre sous fonction )
					( for ) avant dernier niveau d'icrementation : pour tout les champs les champs que l'on shouaite
					if je doit afficher switch bidule
						( switch ) dernier niveau d'intentation : pour afficher juste les bionnes colonnes*/

	int i,j;
	char* p;

	for (i = 0; i < rep.taille; i++) { // pour tous les clients
		int affiche = 0;
		for (j = 0; j < 7 && !affiche; j++) {

			p = strstr(RecupereChamp(rep.clients[rep.tabind[PRENOM][i]],j), filtre);
			if (p) {
				affiche = 1;
			}
		}
		if (affiche) {
			for (j = 0; j < 7; j++) {
				if (tabcol[j]) { // si on doit afficher ce champ
					printf(" %*s |", espacement[j], RecupereChamp(rep.clients[rep.tabind[PRENOM][i]], j));
				}
			}
			printf("\n");
		}
	}
}

void Afficher2(REPERTOIRE rep, char* valeur, int tab[])
{
	int i, v=0;
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
	return -1;
}

void triinsertion(REPERTOIRE rep, int champ)
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

void tripeigne(REPERTOIRE rep, int champ)
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

int numero(char * nom) {
	int champ = -1;
	int j;
	for (j = 0; j < 8; j++) {
		if (!strcmp(nom, TabIntitules[j])) {
			champ = j;
		}
	}
	return champ;
}

void retourchariot(char * chaine) {
	if (chaine[strlen(chaine) - 1] == '\n') {
		chaine[strlen(chaine) - 1] = '\0';
	}

	if (chaine[strlen(chaine) - 1] == ' ') {
		chaine[strlen(chaine) - 1] = '\0';
	}
}

void InterfaceTerminal(REPERTOIRE rep)
{
	int fin = 0;
	char commande[20];
	char arg[20];
	int * tabind;

	tabind = malloc(sizeof(int) * rep.taille);
	int tabtaille = rep.taille;


	printf("les differents commandes actuellement disponibles sont :\n");
	printf("    - close \n");
	printf("    - afficher2 \n");
	printf("    - afficher \n");
	printf("    - trier \n");
	printf("    - trier2 \n");
	printf("    - aide \n\n");

	do {

		int synt = 1;

		printf("*********************\n");
		printf("entrer une commande : ");
		fgets(commande, 20, stdin);
		//enlever le retour charriot
		retourchariot(commande);
		printf("\n");


		if (!strcmp(commande, "close")) {
			synt = 0;
			fin = 1;
		}

		if (!strcmp(commande, "afficher")) {
			synt = 0;
			interfaceaff(rep); /* on renvoi dans une nouvelle fct interface car ca va etre une grosse interface */
		}

		if (!strcmp(commande, "afficher2")) {

			synt = 0;
			printf("arguments pour affichage : \n");
			int i;
			for (i = 0; i < 8; i++) {
				printf("-   %s\n", TabIntitules[i]);
			}

			printf("entrer un argument : ");
			fgets(arg, 20, stdin);
			retourchariot(arg);

			Afficher2(rep, arg, rep.tabind[numero(arg)]);
		}

		if (!strcmp(commande, "trier2")) {

			synt = 0;
			int i;
			printf("arguments pour trier : \n");
			for (i = 0; i < 8; i++) {
				printf("-   %s\n", TabIntitules[i]);
			}

			printf("\nentrer un argument : ");
			fgets(arg, 20, stdin);
			retourchariot(arg);
			int champ = numero(arg);

			if (champ == -1) {
				printf("ERREUR SYNTAXE\n");
			}
			else {
				if (champ == 7) {
					int k;
					clock_t tic = clock();
					for (k = 0; k < 7; k++) {
						clock_t tac = clock();
						triinsertion(rep, k);
						clock_t tuc = clock();
						printf("Duree du %d tri : %lf ms\n",k+1, ((double)(tuc - tac) / CLOCKS_PER_SEC) * 1000);
					}
					clock_t toc = clock();
					printf("Duree de tri : %lf ms\n", ((double)(toc - tic) / CLOCKS_PER_SEC) * 1000);
				}
				else {
					clock_t tic = clock();
					triinsertion(rep, champ);
					clock_t toc = clock();
					printf("Duree de tri : %lf ms\n", ((double)(toc - tic) / CLOCKS_PER_SEC) * 1000);
				}
			}
		}

		if (!strcmp(commande, "trier")) {

			synt = 0;
			int i;
			printf("arguments pour trier : \n");
			for (i = 0; i < 8; i++) {
				printf("-   %s\n", TabIntitules[i]);
			}

			printf("\nentrer un argument : ");
			fgets(arg, 20, stdin);
			retourchariot(arg);
			int champ = numero(arg);

			if (champ == -1) {
				printf("ERREUR SYNTAXE\n");
			}
			else {
				if (champ == 7) {
					int k;
					clock_t tic = clock();
					for (k = 0; k < 7; k++) {
						clock_t tac = clock();
						tripeigne(rep, k);
						clock_t tuc = clock();
						printf("Duree du %d tri : %lf ms\n", k + 1, ((double)(tuc - tac) / CLOCKS_PER_SEC) * 1000);
					}
					clock_t toc = clock();
					printf("Duree de tri : %lf ms\n", ((double)(toc - tic) / CLOCKS_PER_SEC) * 1000);
				}
				else {
					clock_t tic = clock();
					tripeigne(rep, champ);
					clock_t toc = clock();
					printf("Duree de tri : %lf ms\n", ((double)(toc - tic) / CLOCKS_PER_SEC) * 1000);
				}
			}
		}

		if (!strcmp(commande, "aide")) {
			synt = 0;
			printf("les differents commandes actuellement disponibles sont :\n");
			printf("    - close \n");
			printf("    - afficher2 \n");
			printf("    - afficher \n");
			printf("    - trier \n");
			printf("    - aide \n\n");
		}

		if (!strcmp(commande, "nbc")) {
			synt = 0;
			printf("le nombre de clients est : %d\n", rep.taille);
		}

		if (synt == 1) printf("ERREUR SYNTAXE\n");

	} while (fin != 1);
}

void interfaceaff(REPERTOIRE rep) {


	char *arg = malloc(sizeof(char)*100);
	int* tabind;
	char* filtre = malloc(sizeof(char) * 30);
	int over = 0;
	int i, m, j=0;

	int tabcol[7];
	for (m = 0; m < 7; m++) {
		tabcol[m] = 0;
	}

	printf("Colonnes a afficher (enumerer une liste parmis ces choix) : \n");
	for (i = 0; i < 8; i++) {
		printf("-   %s\n", TabIntitules[i]);
	}

	printf("entrer une liste de colonnes : ");
	fgets(arg, 100, stdin);
	
	char* decoupe = arg;

	do {

		if (decoupe[0] == '\0') {
			over = 1;
		}
		else {

			j = 0;
			while (decoupe[j] != ' ' && decoupe[j] != '\n') {
				j++;
			}
			decoupe[j] = '\0';
			int champ = numero(decoupe);

			if (champ == -1) {
				printf("ERREUR SYNTAXE !!!\n");
				over = 1;
			}

			else if (champ == TOUT) {
				for (m = 0; m < 7; m++) {
					tabcol[m] = 1;
				}
				over = 1;
			}

			else {
				tabcol[champ] = 1;
			}

			decoupe = decoupe + j + 1;
		}

	} while (over != 1);

	for (m = 0; m < 7; m++) {
		printf("%d - ", tabcol[m]);
	}
	printf("\n");

	printf("Entrer un filtre a appliquer (ne rien mettre pour ne pas en appliquer) : ");
	fgets(filtre, 20, stdin);
	retourchariot(filtre);

	printf("%s\n", filtre);

	Afficher(rep, tabcol, filtre);

}