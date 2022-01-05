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

    rep = Importer("annuaire5000.csv");
    
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