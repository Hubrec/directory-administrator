#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"

const char * TabIntitules[7] = { "prenom","nom","ville","codePostal","telephone","email","profession"};

REPERTOIRE Importer(char* nom_fichier)
{
    REPERTOIRE rep;
    CLIENT client;
    rep.taille = 0;

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

    //mallco allocation dynamique
    rep.clients = malloc(sizeof(CLIENT) * rep.taille);

    rewind(fichier);

    int i;

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
        char* champ = strdup(buffer + j);
        rep.clients[i].profession = champ;
    }
    fclose(fichier);
    return rep;
}


void Afficher(REPERTOIRE rep, char * valeur)
{
    int i;
    int valeurInt = -1;
    for (int j = 0; j < 7; j++) {
        if (!strcmp(valeur, TabIntitules[j])) {
            valeurInt = j;
        }
    }
    switch(valeurInt)
    {
        case PRENOM:
            for (i = 0; i < rep.taille; i++) {
                printf("%s \n", rep.clients[i].prenom);
            }
            break;
        case NOM:
            for (i = 0; i < rep.taille; i++) {
                printf("%s \n", rep.clients[i].nom);
            }
            break;
        case VILLE:
            for (i = 0; i < rep.taille; i++) {
                printf("%s \n", rep.clients[i].ville);
            }
            break;
        case CP:
            for (i = 0; i < rep.taille; i++) {
                printf("%s \n", rep.clients[i].code_postal);
            }
            break;
        case TEL:
            for (i = 0; i < rep.taille; i++) {
                printf("%s \n", rep.clients[i].telephone);
            }
            break;
        case MAIL:
            for (i = 0; i < rep.taille; i++) {
                printf("%s \n", rep.clients[i].email);
            }
            break;
        case PROF:
            for (i = 0; i < rep.taille; i++) {
                printf("%s \n", rep.clients[i].profession);
            }
            break;
        default :
            for (i = 0; i < rep.taille; i++) {
                printf("%s \n", rep.clients[i].prenom);
                printf("%s ", rep.clients[i].nom);
                printf("%s ", rep.clients[i].ville);
                printf("%s ", rep.clients[i].code_postal);
                printf("%s ", rep.clients[i].telephone);
                printf("%s ", rep.clients[i].email);
                printf("%s ", rep.clients[i].profession);
            }
            break;
        }
}



void InterfaceTerminal(REPERTOIRE rep)
{
    int fin = 0;
    char commande[20];
    char arg[20];
    CLIENT client;

   

    do {
        printf("les differents commandes actuellement disponibles sont :\n");
        printf("    - close \n");
        printf("    - afficher \n");
        printf("    - troisieme \n\n");
        printf("*********************\n");
        printf("entrer une commande : ");
        fgets(commande, 20, stdin);

        //enlever le retour charriot
        if (commande[strlen(commande) - 1] == '\n') {
            commande[strlen(commande) - 1] = '\0';
        }

        printf("\n");



        if (!strcmp(commande,"close")) {
            printf("ca marche");
            fin = 1;
        }

        if (!strcmp(commande, "afficher")) {

            printf("arguments pour affichage : \n");
            int i;
            for (i=0;i<7;i++) {
                printf("-   %s\n", TabIntitules[i]);
            }

            printf("entrer un argument : ");
            fgets(arg, 20, stdin);
            if (arg[strlen(arg) - 1] == '\n') {
                arg[strlen(arg) - 1] = '\0';
            }

            Afficher(rep,arg);
        }
        
        if (!strcmp(commande, "troisieme")) {
            printf("ok\n");
        }

    } while (fin != 1);
}
