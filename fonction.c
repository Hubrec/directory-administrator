#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonction.h"

const char * TabIntitules[8] = { "prenom","nom","ville","codepostal","telephone","email","profession","tout"};
const int espacement[] = { 25,25,25,10,20,45,20 };

REPERTOIRE Importer(char* nom_fichier) //responsable fonction : Guerin Toinon
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
}

int Afficher(REPERTOIRE rep, int tabcol[], int tabfiltre[], char* filtre, int champ) { //responsable fonction : Guerin Toinon

	int i,j,q;
	int combien = 0;

	for (i = 0; i < rep.taille; i++) { // pour tous les clients
		
		int affiche = 0;

		for (j = 0; j < 7 && !affiche; j++) {
			if (filtre == NULL) {
				if (RecupereChamp(rep.clients[rep.tabind[champ][i]], j)[0] == '\0') {
					affiche = 1;
				}
			} else if (tabfiltre[j] == 1) {
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

void InterfaceTerminal(REPERTOIRE rep) //responsable fonction : Guerin Toinon
{
	int fin = 0;
	char commande[20];
	char arg[20];
	int * tabind;
	int show = 0;

	tabind = malloc(sizeof(int) * rep.taille);

	printf("\n Bienvenu sur \"Annuaire 2000\" \n");
	printf("\n (taper \"aide\" pour afficher les commandes disponibles) \n\n");

	do {

		int synt = 1;

		printf("*************************\n");
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
				tripeigne(rep, k);
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

		if (!strcmp(commande, "aide") || !strcmp(commande, "\0")) {
			
			synt = 0;

			if (show == 0) {
				printf(" les differents commandes actuellement disponibles sont :\n");
				printf("   -- afficher \n");
				printf("   -- rechercher\n");
				printf("   -- ajout\n");
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
				printf("    - nbclients \n");
				printf("    - incomplet \n");
				printf("    - aide \n");
				printf("    - fermer \n");
				printf("    - (fonctions cachees) --> hide\n");
				printf("		- tripeigne\n");
				printf("		- triinser\n");
				printf("		- detrier\n");
				printf("		- afficher2\n");
				printf("		- (commande rapide) -> fast\n\n");
			}
		}

		if (!strcmp(commande, "fast")) {
			
			synt = 0;

			printf(" les diff�rentes commandes rapides sont : \n");
			printf("	- afficher   -> a\n");
			printf("	- rechercher -> r\n");
			printf("	- ajout		 -> +\n");
			printf("	- nbclients  -> nbc\n");
			printf("	- incomplet  -> c\n");
			printf("	- fermer     -> f\n");

		}

		if (!strcmp(commande, "rechercher") || !strcmp(commande, "r")) {
			
			synt = 0;
			int index_mot_recherchee;
			index_mot_recherchee = recherche(rep, champ);
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
			int i,j;
			for (i = 0; i < 7; i++) {
				for (j = 0; j < rep.taille; j++)
					rep.tabind[i][j] = j;
			}

			printf(" vous avez bien supprime le tri");

		}

		if (!strcmp(commande, "tripeigne")) {

			synt = 0;
			int i;
			int champ;
			printf(" arguments pour trier : \n");
			for (i = 0; i < 8; i++) {
				printf("	- %s\n", TabIntitules[i]);
			}

			printf("\n -> entrer un argument (valeur de base -tout) : ");
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

			printf(" -> entrer un argument : ");
			fgets(arg, 20, stdin);
			retourchariot(arg);

			Afficher2(rep, arg, rep.tabind[numero(arg)]);
		}

		//code inutilis� mais a garder au cas ou
		if (!strcmp(commande, "triinser")) {

			synt = 0;
			int i;
			printf(" arguments pour trier : \n");
			for (i = 0; i < 8; i++) {
				printf("	- %s\n", TabIntitules[i]);
			}

			printf("\n -> entrer un argument : ");
			fgets(arg, 20, stdin);
			retourchariot(arg);
			int champ = numero(arg);

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
}

void interfaceaff(REPERTOIRE rep, int * tabind) { //responsable fonction : Guerin Toinon


	char arg[100];
	char filtre[30];
	int over = 0;
	int i, m, j=0;
	char champsaisi[30];

	int tabcol[7];
	for (m = 0; m < 7; m++) {
		tabcol[m] = 0;
	}

	int tabfiltre[7];
	for (m = 0; m < 7; m++) {
		tabfiltre[m] = 1;
	}

	printf(" Colonnes a afficher (enumerer une liste parmis ces choix) : \n");
	for (i = 0; i < 8; i++) {
		printf("	- %s\n", TabIntitules[i]);
	}

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
					printf(" ERREUR SYNTAXE\n");
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
		}
		while (over != 1);
	}

	printf(" -> Entrer un filtre a appliquer (valeur par defaut -pas de filtre) : ");
	fgets(filtre, 30, stdin);
	retourchariot(filtre);

	printf(" -> Entrer selon quel colonne vous voulez l'afficher (valeur par defaut -prenom) : ");
	fgets(champsaisi, 30, stdin);
	retourchariot(champsaisi);

	int lechamp;
	if (champsaisi[0] == '\0') {
		lechamp = 0;
	}
	else {
		lechamp = numero(champsaisi);
	}


	int val = Afficher(rep, tabcol, tabfiltre, filtre, lechamp);

	printf("\n vous avez affiche %d client(s)\n\n", val);

}

REPERTOIRE ajout(REPERTOIRE rep) //responsable fonction : Guerin Toinon
{

	rep.taille++;
	rep.clients = realloc(rep.clients, sizeof(CLIENT) * rep.taille);

	if (rep.clients == NULL)
	{
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
	fgets(buffer, 7, stdin);
	retourchariot(buffer);
	rep.clients[rep.taille - 1].code_postal = strdup(buffer);

	printf(" -> saisissez le numero de telephonne : ");
	fgets(buffer, 10, stdin);
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

	
	rep.clients[inditem] = rep.clients[rep.taille - 1];



	
	rep.taille--;
	rep.clients = realloc(rep.clients, sizeof(CLIENT) * rep.taille);

	if (rep.clients == NULL)
	{
		printf(" echec de reallocation\n");
		free(rep.clients);
		exit(EXIT_FAILURE);
	}

	int j;
	for (j = 0; j < 7; j++) {
		rep.tabind[j][inditem] = rep.tabind[j][rep.taille - 1];
		rep.tabind[j] = realloc(rep.tabind[j], sizeof(int) * rep.taille);
	}

	return rep;
}

void sauvegarder(REPERTOIRE rep) //fonction a revoir pour qu'elle marche
{

	FILE* fichier = fopen("annuaire5000.csv", "a");
	int tmp = rep.taille;

	if (fichier == NULL)
	{
		printf(" impossible d'ouvrir l'annuaire");
		exit(EXIT_FAILURE);
	}

	while (rep.taille < tmp)
	{
		fprintf(fichier, "\n");
		fprintf(fichier, "%s", rep.clients[tmp].nom);
		tmp++;
	}
	printf(" sauvegarde accomplie !");
}

void liberte(REPERTOIRE rep) { //responsable fonction : Guerin Toinon

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
}

int recherche(REPERTOIRE rep, int champ) {
	int indicedep = 0;
	int indicefin = rep.taille -1;
	int milieu;

	while(indicedep < indicefin)
	{
		milieu = (indicedep + indicefin) / 2;

		if(motrechercher < rep.clients->prenom[rep.tabind[champ][milieu]] || motrechercher > rep.clients->prenom[rep.tabind[champ][milieu]])
		{
			return (-1);
		}
		
		if(rep.clients->prenom[rep.tabind[champ][milieu]] == motrechercher)
		{
			return(milieu);
		}
		else if(rep.clients->prenom[rep.tabind[champ][milieu]] < motrechercher){
			indicedep = milieu;
		}
		else indicefin = milieu;
	}
}