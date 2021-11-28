#pragma once

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
void InterfaceTerminal(REPERTOIRE rep);
