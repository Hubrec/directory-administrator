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
enum CHAMP { PRENOM, NOM, VILLE, CP, TEL, MAIL, PROF };

const char* TabIntitules[7];

typedef struct repertoire {
    CLIENT* clients;
    int taille;
    int** tabind;
} REPERTOIRE;

REPERTOIRE Importer(char* nom_fichier);
void Afficher(REPERTOIRE rep, char* valeur, int tabind[]);
void InterfaceTerminal(REPERTOIRE rep);
void triindirecte(REPERTOIRE rep, int champ);
int numero(char* nom);
void retourchariot(char* chaine);
