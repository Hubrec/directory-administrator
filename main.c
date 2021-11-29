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

    // Afficher(rep);

    InterfaceTerminal(rep);

    return 0;
}
/* ************************************ */