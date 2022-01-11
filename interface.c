#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonction.h"
#include "ansi.h"

REPERTOIRE InterfaceTerminal(REPERTOIRE rep) //responsable fonction : Guerin Toinon
{
	int fin = 0;
	char commande[20];
	char arg[20];
	int show = 0;
	CLIENT client = { client.prenom = 0, client.nom = 0, client.ville = 0, client.code_postal = 0, client.telephone = 0, client.email = 0, client.profession = 0 };

	setupConsole();
	setTextColor(YELLOW_TXT);
	printf("\n Bienvenu sur \"Annuaire 2000\" \n");
	printf("\n (taper \"aide\" pour afficher les commandes disponibles) \n\n");
	restoreConsole();

	do {

		int synt = 1;
		setupConsole();
		setTextColor(BLUE_TXT);
		printf("\n*************************\n");
		setTextColor(CYAN_TXT);
		printf("---> entrer une commande : ");
		restoreConsole();
		fgets(commande, 20, stdin);
		retourchariot(commande);
		printf("\n");


		if (!strcmp(commande, "fermer") || !strcmp(commande, "f")) {
			synt = 0;
			fin = 1;
		}

		if (!strcmp(commande, "afficher") || !strcmp(commande, "a")) {
			synt = 0;
			interfaceaff(rep); // on renvoi dans une nouvelle fct interface car ca va etre une grosse interface
		}

		if (!strcmp(commande, "nbclients") || !strcmp(commande, "nbc")) {
			synt = 0;
			setupConsole();
			setTextColor(YELLOW_TXT);
			printf("le nombre de clients est : %d\n\n", rep.taille);
			restoreConsole();
		}

		if (!strcmp(commande, "ajout") || !strcmp(commande, "+"))
		{
			synt = 0;
			CLIENT c = { c.prenom = 0, c.nom = 0, c.ville = 0, c.code_postal = 0, c.telephone = 0, c.email = 0, c.profession = 0 };
			char buffer[50];

			printf(" -> saisissez le prenom : ");
			fgets(buffer, 30, stdin);
			retourchariot(buffer);
			c.prenom = strdup(buffer);

			printf(" -> saisissez le nom : ");
			fgets(buffer, 30, stdin);
			retourchariot(buffer);
			c.nom = strdup(buffer);

			printf(" -> saisissez la ville : ");
			fgets(buffer, 20, stdin);
			retourchariot(buffer);
			c.ville = strdup(buffer);

			printf(" -> saisissez le code postal : ");
			fgets(buffer, 10, stdin);
			retourchariot(buffer);
			c.code_postal= strdup(buffer);

			printf(" -> saisissez le numero de telephonne : ");
			fgets(buffer, 20, stdin);
			retourchariot(buffer);
			c.telephone= strdup(buffer);

			printf(" -> saisissez l'email : ");
			fgets(buffer, 45, stdin);
			retourchariot(buffer);
			c.email= strdup(buffer);

			printf(" -> saisissez la profession : ");
			fgets(buffer, 30, stdin);
			retourchariot(buffer);
			c.profession= strdup(buffer);

			rep = ajout(rep, c);

			setupConsole();
			setTextColor(YELLOW_TXT);
			printf("\n vous avez ajoute 1 nouveau client\n\n");
			restoreConsole();

			int k;
			for (k = 0; k < 7; k++) {
				triinsertion(rep, k);
			}
		}

		if (!strcmp(commande, "show"))
		{
			synt = 0;
			if (show == 0) {
				show = 1;
				synt = 0;
			}
		}

		if (!strcmp(commande, "hide"))
		{
			synt = 0;
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
			setupConsole();
			setTextColor(YELLOW_TXT);
			if (show == 0) {
				printf(" les differents commandes actuellement disponibles sont :\n");
				printf("   -- afficher \n");
				printf("   -- rechercher\n");
				printf("   -- ajout\n");
				printf("   -- rechercher\n");
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
				printf("   -- rechercher\n");
				printf("	  - supprimer\n");
				printf("	  - modifier\n");
				printf("    - nbclients \n");
				printf("    - incomplet \n");
				printf("    - aide \n");
				printf("    - fermer \n");
				printf("    - (fonctions cachees) --> hide\n");
				printf("		- sauvegarder\n");
				printf("		- tripeigne\n");
				printf("		- triinser\n");
				printf("		- detrier\n");
				printf("		- (commande rapide) -> fast\n\n");
			}
			restoreConsole();
		}

		if (!strcmp(commande, "fast")) {

			synt = 0;
			setupConsole();
			setTextColor(YELLOW_TXT);
			printf(" les differentes commandes rapides sont : \n");
			printf("	- afficher   -> a\n");
			printf("	- rechercher -> r\n");
			printf("	- ajout      -> +\n");
			printf("	- supprimer  -> -\n");
			printf("	- incomplet  -> c\n");
			printf("	- fermer     -> f\n");
			printf("	- effacer    -> e\n");
			printf("	- nbclients  -> nbc\n");
			restoreConsole();
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

			setupConsole();
			setTextColor(YELLOW_TXT);
			printf("\n le nombre de clients dont la fiche est incomplete est : %d\n\n", val);
			restoreConsole();
		}

		if (!strcmp(commande, "detrier")) {

			synt = 0;
			int i, j;
			for (i = 0; i < 7; i++) {
				for (j = 0; j < rep.taille; j++)
					rep.tabind[i][j] = j;
			}

			setupConsole();
			setTextColor(YELLOW_TXT);
			printf("\n vous avez bien supprime le tri\n\n");
			restoreConsole();
		}

		if (!strcmp(commande, "rechercher") || !strcmp(commande, "r")) {
		
			synt = 0;
			CLIENT cl = { cl.prenom = 0, cl.nom = 0, cl.ville = 0, cl.code_postal = 0, cl.telephone = 0, cl.email = 0, cl.profession = 0 };
			char buffer[50];
			int dernier;
			int premier;
			int choix;

			printf(" -> Entrez le nom du client que vous recherchez : ");
			fgets(buffer, 30, stdin);
			retourchariot(buffer);
			cl.nom = strdup(buffer);

			printf(" -> Entrez le prenom du client que vous recherchez : ");
			fgets(buffer, 30, stdin);
			retourchariot(buffer);
			cl.prenom = strdup(buffer);

			premier = recherche(rep, cl, &dernier);


			if (premier == -1) {
				setupConsole();
				setTextColor(RED_TXT);
				printf(" \npas de clients trouves\n");
				restoreConsole();
			}
			else if (premier == dernier) {
				int i;
				for (i = 0; i < 7; i++) {
					printf(" %s  | ", RecupereChamp(rep.clients[rep.tabind[NOM][premier]], i));
				}
				printf("\n\n");

				choix = rep.tabind[NOM][premier];
			}
			else if (premier < dernier) {
				int j;
				for (j = premier; j <= dernier;j++) {
					int i;
					printf(" - client %d : ",j-premier+1);
					for (i = 0; i < 7; i++) {
						printf(" %s  | ", RecupereChamp(rep.clients[rep.tabind[NOM][j]], i));
					}
					printf("\n");
				}

				printf("\n");
				printf(" -> saisissez lequel choisir (son numero) : ");
				int retour = scanf("%d", &choix);
				retour = getchar();

				choix = rep.tabind[NOM][choix -1 + premier];
			}
			printf("\n");

			if (premier != -1) {
				char commande[10];
				printf(" -> vous pouvez desormais modifier / supprimer ce client (valeur par defaut -ne rien faire) : ");
				fgets(commande, 10, stdin);
				retourchariot(commande);

				if (commande[0] == '\0') {
					setupConsole();
					setTextColor(RED_TXT);
					printf(" \nabandon de la recherche\n");
					restoreConsole();
				}
				else if (!strcmp(commande, "modifier") || !strcmp(commande, "*")) {

					interfacemodiff(rep, choix);
				}
				else if (!strcmp(commande, "supprimer") || !strcmp(commande, "-")) {

					synt = 0;

					rep = suppression(rep, choix);

					int k;
					for (k = 0; k < 7; k++) {
						triinsertion(rep, k);
					}
				}
				printf("\n");
			}
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
					setupConsole();
					setTextColor(RED_TXT);
					printf(" ERREUR SYNTAXE\n");
					restoreConsole();
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
				setupConsole();
				setTextColor(RED_TXT);
				printf(" ERREUR SYNTAXE\n");
				restoreConsole();
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
		setupConsole();
		setTextColor(RED_TXT);
		if (synt == 1) printf(" ERREUR SYNTAXE\n");
		restoreConsole();
	} while (fin != 1);

	return rep;
}

void interfaceaff(REPERTOIRE rep) { //responsable fonction : Guerin Toinon


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
						setupConsole();
						setTextColor(RED_TXT);
						printf("\n ERREUR SYNTAXE\n\n");
						restoreConsole();
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
						setupConsole();
						setTextColor(RED_TXT);
						printf("\n ERREUR SYNTAXE\n\n");
						restoreConsole();
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
			setupConsole();
			setTextColor(RED_TXT);
			printf("\n ERREUR SYNTAXE\n\n");
			restoreConsole();
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

	setupConsole();
	setTextColor(YELLOW_TXT);
	printf("\n vous avez affiche %d client(s)\n\n", val);
	restoreConsole();
}

void interfacemodiff(REPERTOIRE rep, int item) {

	int tabelement[7] = { 0,0,0,0,0,0,0 };
	char elements[100];
	int m, j;
	int probleme = 0;
	int over = 0;

	printf("\n");
	int i;
	for (i = 0; i < 8; i++) {
		printf(" %s  | ", TabIntitules[i]);
	}
	printf("\n");
	for (i = 0; i < 7; i++) {
		printf(" %s  | ", RecupereChamp(rep.clients[rep.tabind[NOM][item]], i));
	}

	do {
		probleme = 0;
		for (m = 0; m < 7; m++) {
			tabelement[m] = 0;
		}


		printf("\n\n");
		printf(" -> entrez la liste d'elements que vous shouaitez modifier (valeur par defaut -tout) : ");
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
						setupConsole();
						setTextColor(RED_TXT);
						printf("\n ERREUR SYNTAXE\n\n");
						restoreConsole();
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

	char buffer[50];
	CLIENT cl = { cl.prenom = 0, cl.nom = 0, cl.ville = 0, cl.code_postal = 0, cl.telephone = 0, cl.email = 0, cl.profession = 0 };

	if (tabelement[0] == 1) {
		printf(" -> valeur actuelle pour le prenom : \"%s\", saisissez son remplacement : ", rep.clients[item].prenom);
		fgets(buffer, 30, stdin);
		retourchariot(buffer);
		cl.prenom = strdup(buffer);
	}

	if (tabelement[1] == 1) {
		printf(" -> valeur actuelle pour le nom : \"%s\", saisissez son remplacement : ", rep.clients[item].nom);
		fgets(buffer, 30, stdin);
		retourchariot(buffer);
		cl.nom = strdup(buffer);
	}

	if (tabelement[2] == 1) {
		printf(" -> valeur actuelle pour la ville : \"%s\", saisissez son remplacement : ", rep.clients[item].ville);
		fgets(buffer, 20, stdin);
		retourchariot(buffer);
		cl.ville = strdup(buffer);
	}

	if (tabelement[3] == 1) {
		printf(" -> valeur actuelle pour le code postal : \"%s\", saisissez son remplacement : ", rep.clients[item].code_postal);
		fgets(buffer, 10, stdin);
		retourchariot(buffer);
		cl.code_postal = strdup(buffer);
	}

	if (tabelement[4] == 1) {
		printf(" -> valeur actuelle pour le telephone : \"%s\", saisissez son remplacement : ", rep.clients[item].telephone);
		fgets(buffer, 20, stdin);
		retourchariot(buffer);
		cl.telephone = strdup(buffer);
	}

	if (tabelement[5] == 1) {
		printf(" -> valeur actuelle pour le mail : \"%s\", saisissez son remplacement : ", rep.clients[item].email);
		fgets(buffer, 20, stdin);
		retourchariot(buffer);
		cl.email = strdup(buffer);
	}

	if (tabelement[6] == 1) {
		printf(" -> valeur actuelle pour la profession : \"%s\", saisissez son remplacement : ", rep.clients[item].profession);
		fgets(buffer, 20, stdin);
		retourchariot(buffer);
		cl.profession = strdup(buffer);
	}

	rep = modifier(rep, item, tabelement, cl);

	setupConsole();
	setTextColor(YELLOW_TXT);
	printf("\n\n les informations concernant %s %s ont bien ete prises en compte\n", rep.clients[item].prenom, rep.clients[item].nom);
	restoreConsole();

	int k;
	for (k = 0; k < 7; k++) {
		triinsertion(rep, k);
	}
}