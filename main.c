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

    //appel de l'interface terminal qui gere tout les appels de fonctions

    InterfaceTerminal(rep);

    return 0;
}
/* ************************************ */