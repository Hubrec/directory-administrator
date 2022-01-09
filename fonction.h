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

/* specification formelle
* 
*   entrée : prends en entrée le nom du fichier
*   sortie : return la structure REPERTOIRE
*   précondition : donner le nom d'un fichier qui existe et qui est dans le meme repertoire que le programme
*   postcondition : rempli avec les informations contenues dans le repertoire par champ le tableau de structure CLIENT clients
* 
*/
REPERTOIRE Importer(char nom_fichier[30]);

/* specification formelle
*
*   entrée : la structure REPERTOIRE
*   sortie : la structure REPERTOIRE
*   précondition : pas de precondition, il s'agit simplement d'une redirection
*   postcondition : pas de postcondition, il s'agit simplement d'une redirection
*
*/
REPERTOIRE InterfaceTerminal(REPERTOIRE rep);

/* specification formelle
*
*   entrée : la structure REPERTOIRE, l'entier champ
*   sortie : pas de return
*   précondition : champ doit etre une valeur contenue entre 0 et 6
*   postcondition : renvoi le tableau tabind dans REPERTOIRE dans l'odre trié de l'annuaire pour le champ entré
*
*/
void triiinsertion(REPERTOIRE rep, int champ);

/* specification formelle
*
*   entrée : la structure REPERTOIRE, l'entier champ
*   sortie : pas de return
*   précondition : champ doit etre une valeur contenue entre 0 et 6
*   postcondition : renvoi le tableau tabind dans REPERTOIRE dans l'odre trié de l'annuaire pour le champ entré
*
*/
void tripeigne(REPERTOIRE rep, int champ);

/* specification formelle
*
*   entrée : 
*   sortie :
*   précondition :
*   postcondition :
*
*/
int numero(char* nom);

/* specification formelle
*
*   entrée : 
*   sortie :
*   précondition :
*   postcondition :
*
*/
void retourchariot(char* chaine);

/* specification formelle
*
*   entrée : 
*   sortie :
*   précondition :
*   postcondition :
*
*/
void interfaceaff(REPERTOIRE rep);

/* specification formelle
*
*   entrée : 
*   sortie :
*   précondition :
*   postcondition :
*
*/
int Afficher(REPERTOIRE rep, int tabcol[], int tabfiltre[], char* filtre, int champ);

/* specification formelle
*
*   entrée : 
*   sortie :
*   précondition :
*   postcondition :
*
*/
REPERTOIRE ajout(REPERTOIRE rep, CLIENT c);

/* specification formelle
*
*   entrée : 
*   sortie :
*   précondition :
*   postcondition :
*
*/
void sauvegarder(REPERTOIRE rep);

/* specification formelle
*
*   entrée : 
*   sortie :
*   précondition :
*   postcondition :
*
*/
REPERTOIRE liberte(REPERTOIRE rep);

/* specification formelle
*
*   entrée : 
*   sortie :
*   précondition :
*   postcondition :
*
*/
REPERTOIRE suppression(REPERTOIRE rep, int inditem);
int recherche(REPERTOIRE rep, int champ, char* col_recherche);

/* specification formelle
*
*   entrée : 
*   sortie :
*   précondition :
*   postcondition :
*
*/
int compare(CLIENT c1, CLIENT c2, int champ);

/* specification formelle
*
*   entrée : 
*   sortie :
*   précondition :
*   postcondition :
*
*/
REPERTOIRE modifier(REPERTOIRE rep, int inditem, int tabelement[], CLIENT cl);

/* specification formelle
*
*   entrée :
*   sortie :
*   précondition :
*   postcondition :
*
*/
int recherche(REPERTOIRE rep, CLIENT c, int* dernier);

/* specification formelle
*
*   entrée :
*   sortie :
*   précondition :
*   postcondition :
*
*/
char* RecupereChamp(CLIENT client, int numerochamp);

/* specification formelle
*
*   entrée : 
*   sortie : 
*   précondition : 
*   postcondition : 
*
*/
void interfacemodiff(REPERTOIRE rep, int item);