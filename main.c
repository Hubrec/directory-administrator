#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
#include "interface.c"
#include "fonctionalites.c"
#include "entree-sortie.c"
#include "ansi.c"
#include "ansi.h"


/* fonction principale */
/* ************************************ */
int main()
{
    REPERTOIRE rep;
    char nomfichier[30];
    printf("Quel est le nom du fichier voulez vous ouvrir ?\n");
    scanf("%s", nomfichier);
    rep = Importer(nomfichier);
    
    int k;
    for (k = 0; k < 7; k++) {
        tripeigne(rep, k);
    }

    rep = InterfaceTerminal(rep);  //appel de l'interface terminal qui gere tout les appels de fonctions

    sauvegarder(rep);

    rep = liberte(rep); //fonction a fire pour liberer la memoire

    return 0;
}
/* ************************************ */