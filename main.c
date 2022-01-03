#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"

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

    InterfaceTerminal(rep);  //appel de l'interface terminal qui gere tout les appels de fonctions

    liberte(rep); //fonction a fire pour liberer la memoire

    return 0;
}
/* ************************************ */