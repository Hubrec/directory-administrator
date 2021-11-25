#include <stdio.h>
#include <stdlib.h>
// #include "fonction.h"

typedef struct client {
   char * prenom;
   char * nom;
   char * ville;
   char * code_postal;
   char * telephone;
   char * email;
   char * profession;
} CLIENT;

typedef struct repertoire {
    CLIENT * clients;
    int taille;
} REPERTOIRE;

REPERTOIRE Importer(char * nom_fichier);
void Afficher(REPERTOIRE rep);
void InterfaceTerminal();


/* fonction principale */
/* ************************************ */
int main()
{
    REPERTOIRE rep;

    rep = Importer("annuaire5000.csv");

    // Afficher(rep);

    InterfaceTerminal();

    return 0;
}
/* ************************************ */



REPERTOIRE Importer(char * nom_fichier)
{
    REPERTOIRE rep;
    CLIENT client;
    rep.taille = 0;

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
        fgets(buffer,300,fichier);
        rep.taille++;
    }
    while (! feof(fichier));

    rep.taille--;

//mallco allocation dynamique
    rep.clients = malloc(sizeof(CLIENT)*rep.taille);

    rewind(fichier);

    int i;

    for(i=0;i<rep.taille;i++) {
        fgets(buffer,300,fichier);
        int j=0;
        int k;
        for (k=0;k<6;k++) {
            int debut=j;
            while(buffer[j]!=',') {
                j++;
            }
            buffer[j] = '\0';
            char * champ = strdup(buffer+debut);
            switch (k) {
                case 0:
                    rep.clients[i].prenom = champ;
                    break;
                case 1:
                    rep.clients[i].nom = champ;
                    break;
                case 2:
                    rep.clients[i].ville = champ;
                    break;
                case 3:
                    rep.clients[i].code_postal = champ;
                    break;
                case 4:
                    rep.clients[i].telephone = champ;
                    break;
                case 5:
                    rep.clients[i].email = champ;
                    break;
            }
            j++;
        }
        char * champ = strdup(buffer+j);
        rep.clients[i].profession = champ;
    }
    fclose(fichier);
    return rep;
}



void Afficher(REPERTOIRE rep)
{
    int i;
    for (i=0;i<rep.taille;i++) {
        printf("%s \n",rep.clients[i].prenom);
        printf("%s ",rep.clients[i].nom);
        printf("%s ",rep.clients[i].ville);
        printf("%s ",rep.clients[i].code_postal);
        printf("%s ",rep.clients[i].telephone);
        printf("%s ",rep.clients[i].email);
        printf("%s ",rep.clients[i].profession);
    }
}



void InterfaceTerminal()
{
    int fin=0;
    char commande[10];
    char arg[10];
    CLIENT client;
    REPERTOIRE rep;


    printf("comment fonctionne une commande ?\n");
    printf("dans le terminal quand on affiche \" entrer une commande :\"\n");
    printf("on la rentre sous la forme : commande argument\n");
    printf("quand on a pas d'agruments a mettre on pourra ecrire 0 pour le signifier\n\n");

    printf("les differents commandes actuellement disponibles sont :\n");
    printf("    - close  (pas d'arguments) \n");

    printf("entrer une commande : ");
    // fgets(commande,10, stdin);
    // fgets(arg,10, stdin);

    do {
        scanf("%d", &commande);

        if(commande == 1) {
            printf("ca marche");
            fin=1;
        }

        if(commande == 2) {
            printf("ca marche");
            Afficher(rep);
        }
    }
    while(fin != 1);
}
