#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"



REPERTOIRE Importer(char * nom_fichier) {
    REPERTOIRE rep;
    CLIENT client;
    rep.taille = 0;

//on ouvre le fichier
    FILE * fichier = fopen(nom_fichier, "r");

//message d'erreur si fichier est vide ou non trouv�
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

void Afficher(REPERTOIRE rep) {
    int i;
    for (i=0;i<rep.taille;i++) {
        printf("%s ",rep.clients[i].prenom);
        printf("%s ",rep.clients[i].nom);
        printf("%s ",rep.clients[i].ville);
        printf("%s ",rep.clients[i].code_postal);
        printf("%s ",rep.clients[i].telephone);
        printf("%s ",rep.clients[i].email);
        printf("%s ",rep.clients[i].profession);
    }
}




