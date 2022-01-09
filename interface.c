#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonction.h"

REPERTOIRE InterfaceTerminal(REPERTOIRE rep) //responsable fonction : Guerin Toinon
{
	int fin = 0;
	char commande[20];
	char arg[20];
	int* tabind;
	int show = 0;

	tabind = malloc(sizeof(int) * rep.taille);

	printf("\n Bienvenu sur \"Annuaire 2000\" \n");
	printf("\n (taper \"aide\" pour afficher les commandes disponibles) \n\n");

	do {

		int synt = 1;

		printf("\n*************************\n");
		printf("---> entrer une commande : ");
		fgets(commande, 20, stdin);
		retourchariot(commande);
		printf("\n");


		if (!strcmp(commande, "fermer") || !strcmp(commande, "f")) {
			synt = 0;
			fin = 1;
		}

		if (!strcmp(commande, "afficher") || !strcmp(commande, "a")) {
			synt = 0;
			interfaceaff(rep, tabind); // on renvoi dans une nouvelle fct interface car ca va etre une grosse interface
		}

		if (!strcmp(commande, "nbclients") || !strcmp(commande, "nbc")) {
			synt = 0;
			printf("le nombre de clients est : %d\n\n", rep.taille);
		}

		if (!strcmp(commande, "ajout") || !strcmp(commande, "+"))
		{
			synt = 0;
			rep = ajout(rep);

			int k;
			for (k = 0; k < 7; k++) {
				triinsertion(rep, k);
			}
		}

		if (!strcmp(commande, "supprimer") || !strcmp(commande, "-")) {

			synt = 0;
			int item;

			printf(" -> selectionner un numero (temporaire) : ");
			int retour = scanf("%d", &item);
			retour = getchar();

			rep = suppression(rep,item);

			int k;
			for (k = 0; k < 7; k++) {
				triinsertion(rep, k);
			}
		}

		if (!strcmp(commande, "modifier") || !strcmp(commande, "*")) {
			
			synt = 0;
			int item;
			printf(" -> selectionner un numero (temporaire) : ");
			int retour = scanf("%d", &item);
			retour = getchar();

			int tabelement[7] = { 0,0,0,0,0,0,0 };
			char elements[100];
			int m,j;
			int probleme = 0;
			int over = 0;

			do {
				probleme = 0;
				for (m = 0; m < 7; m++) {
					tabelement[m] = 0;
				}

				int i;
				for (i = 0; i < 8; i++) {
					printf(" %s  | ", TabIntitules[i]);
				}
				printf("\n\n");

				printf(" -> entrez la liste d'elements que vous shouaitez modifier (valeur par fefaut -tout) : ");
				fgets(elements, 100, stdin);

				if (elements[0] == '\n') {
					for (m = 0; m < 7; m++) {
						tabelement[m] = 1;
					}
				}
				else {
					char* decoupe = elements;
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
								printf("\n ERREUR SYNTAXE\n\n");
								probleme = 1;
								over = 1;
							}
							else if (champ == TOUT) {
								for (m = 0; m < 7; m++) {
									tabelement[m] = 1;
								}
								over = 1;
							}
							else {
								tabelement[champ] = 1;
							}
							decoupe = decoupe + j + 1;
						}
					} while (over != 1);
				}
			} while (probleme == 1);

			printf(" tips : si vous ne voulez plus modifier tapez simplement entree\n\n");

			rep = modifier(rep, item, tabelement);

			int k;
			for (k = 0; k < 7; k++) {
				triinsertion(rep, k);
			}
		}

		if (!strcmp(commande, "show"))
		{
			if (show == 0) {
				show = 1;
				synt = 0;
			}
		}

		if (!strcmp(commande, "hide"))
		{
			if (show == 1) {
				show = 0;
				synt = 0;
			}
		}

		if (!strcmp(commande, "sauvegarder")) {

			synt = 0;
			sauvegarder(rep);
		}

		if (!strcmp(commande, "aide") || !strcmp(commande, "\0")) {

			synt = 0;

			if (show == 0) {
				printf(" les differents commandes actuellement disponibles sont :\n");
				printf("   -- afficher \n");
				printf("   -- rechercher\n");
				printf("   -- ajout\n");
				printf("   -- supprimer\n");
				printf("    - nbclients \n");
				printf("    - incomplet \n");
				printf("    - aide \n");
				printf("    - fermer \n");
				printf("    - (fonctions cachees) --> show\n\n");
			}
			else {
				printf(" les differents commandes actuellement disponibles sont :\n");
				printf("   -- afficher \n");
				printf("   -- rechercher\n");
				printf("   -- ajout\n");
				printf("   -- supprimer\n");
				printf("    - nbclients \n");
				printf("    - incomplet \n");
				printf("    - aide \n");
				printf("    - fermer \n");
				printf("    - (fonctions cachees) --> hide\n");
				printf("		- sauvegarder\n");
				printf("		- tripeigne\n");
				printf("		- triinser\n");
				printf("		- detrier\n");
				printf("		- afficher2\n");
				printf("		- (commande rapide) -> fast\n\n");
			}
		}

		if (!strcmp(commande, "fast")) {

			synt = 0;

			printf(" les differentes commandes rapides sont : \n");
			printf("	- afficher   -> a\n");
			printf("	- rechercher -> r\n");
			printf("	- ajout		 -> +\n");
			printf("	- supprimer  -> -\n");
			printf("	- nbclients  -> nbc\n");
			printf("	- incomplet  -> c\n");
			printf("	- fermer     -> f\n");
			printf("	- effacer    -> e\n");

		}

		if (!strcmp(commande, "rechercher") || !strcmp(commande, "r")) {

			synt = 0;
		}

		if (!strcmp(commande, "effacer") || !strcmp(commande, "e")) {
			
			synt = 0;
			system("cls");
		}

		if (!strcmp(commande, "incomplet") || !strcmp(commande, "c")) {

			synt = 0;
			char* filtre = NULL;
			int tabcol[7];
			int tabfiltre[7];
			int m;
			for (m = 0; m < 7; m++) {
				tabcol[m] = 1;
			}
			for (m = 0; m < 7; m++) {
				tabfiltre[m] = 1;
			}

			int champ = PRENOM;

			int val = Afficher(rep, tabcol, tabfiltre, filtre, champ);

			printf("\n le nombre de clients dont la fiche est incomplete est : %d\n\n", val);
		}

		if (!strcmp(commande, "detrier")) {

			synt = 0;
			int i, j;
			for (i = 0; i < 7; i++) {
				for (j = 0; j < rep.taille; j++)
					rep.tabind[i][j] = j;
			}

			printf("\n vous avez bien supprime le tri\n\n");
		}

		if (!strcmp(commande, "tripeigne")) {

			synt = 0;
			int i;
			int champ;
			printf(" arguments pour trier : \n");
			for (i = 0; i < 8; i++) {
				printf("	- %s\n", TabIntitules[i]);
			}

			printf("\n -> entrer un argument (valeur par defaut -tout) : ");
			fgets(arg, 20, stdin);
			retourchariot(arg);
			if (arg[0] == '\0') {
				champ = 7;
			}
			else {
				champ = numero(arg);

				if (champ == -1) {
					printf(" ERREUR SYNTAXE\n");
				}
			}

			if (champ == 7) {
				int k;
				clock_t tic = clock();
				for (k = 0; k < 7; k++) {
					clock_t tac = clock();
					tripeigne(rep, k);
					clock_t tuc = clock();
					printf(" Duree du %d tri : %lf ms\n", k + 1, ((double)(tuc - tac) / CLOCKS_PER_SEC) * 1000);
				}
				clock_t toc = clock();
				printf(" Duree de tri : %lf ms\n", ((double)(toc - tic) / CLOCKS_PER_SEC) * 1000);
			}
			else {
				clock_t tic = clock();
				tripeigne(rep, champ);
				clock_t toc = clock();
				printf(" Duree de tri : %lf ms\n", ((double)(toc - tic) / CLOCKS_PER_SEC) * 1000);
			}
		}

		//a supprimer pour la version finale 
		if (!strcmp(commande, "afficher2")) {

			synt = 0;
			printf(" arguments pour affichage : \n");
			int i;
			for (i = 0; i < 8; i++) {
				printf("	- %s\n", TabIntitules[i]);
			}

			printf(" -> entrer un argument (valeur par defaut -tout) : ");
			fgets(arg, 20, stdin);
			retourchariot(arg);

			Afficher2(rep, arg, rep.tabind[numero(arg)]);
		}

		if (!strcmp(commande, "triinser")) {

			synt = 0;
			int i;
			printf(" arguments pour trier : \n");
			for (i = 0; i < 8; i++) {
				printf("	- %s\n", TabIntitules[i]);
			}

			printf("\n -> entrer un argument (valeur par defaut -tout) : ");
			fgets(arg, 20, stdin);
			retourchariot(arg);
			int champ = numero(arg);
			if (arg[0] == '\0') {
				champ = 7;
			}
			if (champ == -1) {
				printf(" ERREUR SYNTAXE\n");
			}
			else {
				if (champ == 7) {
					int k;
					clock_t tic = clock();
					for (k = 0; k < 7; k++) {
						clock_t tac = clock();
						triinsertion(rep, k);
						clock_t tuc = clock();
						printf(" Duree du %d tri : %lf ms\n", k + 1, ((double)(tuc - tac) / CLOCKS_PER_SEC) * 1000);
					}
					clock_t toc = clock();
					printf(" Duree de tri : %lf ms\n", ((double)(toc - tic) / CLOCKS_PER_SEC) * 1000);
				}
				else {
					clock_t tic = clock();
					triinsertion(rep, champ);
					clock_t toc = clock();
					printf(" Duree de tri : %lf ms\n", ((double)(toc - tic) / CLOCKS_PER_SEC) * 1000);
				}
			}
		}

		if (synt == 1) printf(" ERREUR SYNTAXE\n");

	} while (fin != 1);

	return rep;
}

void interfaceaff(REPERTOIRE rep, int* tabind) { //responsable fonction : Guerin Toinon


	char arg[100];
	char filtre[30];
	char coll[30];
	int over = 0;
	int i, m, j = 0;
	char champsaisi[30];
	int probleme = 0;

	int tabcol[7] = {0,0,0,0,0,0,0};

	int tabfiltre[7] = {0,0,0,0,0,0,0};

	do {
		probleme = 0;
		for (m = 0; m < 7; m++) {
			tabcol[m] = 0;
		}

		for (i = 0; i < 8; i++) {
			printf(" %s  | ", TabIntitules[i]);
		}
		printf("\n\n");

		printf(" -> entrer une liste de colonnes (valeur par defaut -tout) : ");
		fgets(arg, 100, stdin);

		if (arg[0] == '\n') {
			for (m = 0; m < 7; m++) {
				tabcol[m] = 1;
			}
		}
		else {
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
						printf("\n ERREUR SYNTAXE\n\n");
						probleme = 1;
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
		}
	} while (probleme == 1);
	probleme = 0;

	over = 0;
	i, m, j = 0;

	do {
		probleme = 0;
		for (m = 0; m < 7; m++) {
			tabfiltre[m] = 0;
		}

		printf(" -> entrer une liste de colonnes sur lesquelles appliquer un filtre (valeur par defaut -tout) : ");
		fgets(arg, 100, stdin);

		if (arg[0] == '\n') {
			for (m = 0; m < 7; m++) {
				tabfiltre[m] = 1;
			}
		}
		else {
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
						printf("\n ERREUR SYNTAXE\n\n");
						probleme = 1;
						over = 1;
					}
					else if (champ == TOUT) {
						for (m = 0; m < 7; m++) {
							tabfiltre[m] = 1;
						}
						over = 1;
					}
					else {
						tabfiltre[champ] = 1;
					}
					decoupe = decoupe + j + 1;
				}
			} while (over != 1);
		}
	} while (probleme == 1);
	probleme = 0;


	printf(" -> Entrer un filtre a appliquer (valeur par defaut -pas de filtre) : ");
	fgets(filtre, 30, stdin);
	retourchariot(filtre);

	int lechamp = 0;;
	do {
		if (lechamp == -1) {
			printf("\n ERREUR SYNTAXE\n\n");
		}
		printf(" -> Entrer selon quel colonne vous voulez l'afficher (valeur par defaut -prenom) : ");
		fgets(champsaisi, 30, stdin);
		retourchariot(champsaisi);

		if (champsaisi[0] == '\0') {
			lechamp = 0;
		}
		else {
			lechamp = numero(champsaisi);
		}
	} while (lechamp == -1);


	int val = Afficher(rep, tabcol, tabfiltre, filtre, lechamp);

	printf("\n vous avez affiche %d client(s)\n\n", val);

}