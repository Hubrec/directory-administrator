#pragma once

typedef struct client {
    char* prenom;
    char* nom;
    char* ville;
    char* code_postal;
    char* telephone;
    char* email;
    char* profession;
} CLIENT;

//juste pour que ce soit plus lisible
enum CHAMP { PRENOM, NOM, VILLE, CP, TEL, MAIL, PROF, TOUT };

const int espacement[7];

const char* TabIntitules[8];

typedef struct repertoire {
    CLIENT* clients; // tableau de clients
    int taille;      // taille du tableau de clients = # de clients
    int ** tabind;   // tableau de tableaux d'indices
} REPERTOIRE;

REPERTOIRE Importer(char* nom_fichier);
void Afficher2(REPERTOIRE rep, char* valeur, int tabind[]);
void InterfaceTerminal(REPERTOIRE rep);
void triindirecte(REPERTOIRE rep, int champ);
void tripeigne(REPERTOIRE rep, int champ);
int numero(char* nom);
void retourchariot(char* chaine);
void interfaceaff(REPERTOIRE rep);
void Afficher(REPERTOIRE rep, int tabcol[], char* filtre, int champ);

