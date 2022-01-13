#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
#include "fonction.c"

/* fonction principale */
/* ************************************ */
int main()
{ 
    REPERTOIRE rep;
    char nomfichier[30];
    int test = 0;
    do {
        test = 0;
        printf("\n quel est le nom du fichier voulez vous ouvrir : ");
        fgets(nomfichier, 30, stdin);
        retourchariot(nomfichier);

        FILE* fichier = fopen(nomfichier, "r");
        if (fichier == NULL) {
            test = 1;
            printf("\n\n echec d'ouverture, fichier inexistant\n\n");
        }
    } while (test == 1);

    rep = Importer(nomfichier);
    
    int k;
    for (k = 0; k < 7; k++) {
        tripeigne(rep, k);
    }

    rep = InterfaceTerminal(rep, nomfichier);  //appel de l'interface terminal qui gere tout les appels de fonctions

    sauvegarder(rep, nomfichier);

    rep = liberte(rep); //fonction a fire pour liberer la memoire

    return 0;
}
/* ************************************ */