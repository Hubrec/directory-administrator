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

//juste pour que ce soit plus lisible
enum CHAMP {PRENOM, NOM, VILLE, CP, TEL, MAIL,PROF};

const char * TabIntitules[7];

typedef struct repertoire {
    CLIENT * clients;
    int taille;
} REPERTOIRE;

REPERTOIRE Importer(char * nom_fichier);
void Afficher(REPERTOIRE rep);
void InterfaceTerminal(REPERTOIRE rep);
