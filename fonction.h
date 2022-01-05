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
*   entr�e : prends en entr�e le nom du fichier
*   sortie : return la structure REPERTOIRE
*   pr�condition : donner le nom d'un fichier qui existe et qui est dans le meme repertoire que le programme
*   postcondition : rempli avec les informations contenues dans le repertoire par champ le tableau de structure CLIENT clients
* 
*/
REPERTOIRE Importer(char nom_fichier[30]);

/* specification formelle
*
*   entr�e : la structure REPERTOIRE
*   sortie : la structure REPERTOIRE
*   pr�condition : pas de precondition, il s'agit simplement d'une redirection
*   postcondition : pas de postcondition, il s'agit simplement d'une redirection
*
*/
REPERTOIRE InterfaceTerminal(REPERTOIRE rep);

/* specification formelle
*
*   entr�e : la structure REPERTOIRE, l'entier champ
*   sortie : pas de return
*   pr�condition : champ doit etre une valeur contenue entre 0 et 6
*   postcondition : renvoi le tableau tabind dans REPERTOIRE dans l'odre tri� de l'annuaire pour le champ entr�
*
*/
void triiinsertion(REPERTOIRE rep, int champ);

/* specification formelle
*
*   entr�e : la structure REPERTOIRE, l'entier champ
*   sortie : pas de return
*   pr�condition : champ doit etre une valeur contenue entre 0 et 6
*   postcondition : renvoi le tableau tabind dans REPERTOIRE dans l'odre tri� de l'annuaire pour le champ entr�
*
*/
void tripeigne(REPERTOIRE rep, int champ);

/* specification formelle
*
*   entr�e : 
*   sortie :
*   pr�condition :
*   postcondition :
*
*/
int numero(char* nom);

/* specification formelle
*
*   entr�e : 
*   sortie :
*   pr�condition :
*   postcondition :
*
*/
void retourchariot(char* chaine);

/* specification formelle
*
*   entr�e : 
*   sortie :
*   pr�condition :
*   postcondition :
*
*/
void interfaceaff(REPERTOIRE rep);

/* specification formelle
*
*   entr�e : 
*   sortie :
*   pr�condition :
*   postcondition :
*
*/
int Afficher(REPERTOIRE rep, int tabcol[], int tabfiltre[], char* filtre, int champ);

/* specification formelle
*
*   entr�e : 
*   sortie :
*   pr�condition :
*   postcondition :
*
*/
REPERTOIRE ajout(REPERTOIRE rep, CLIENT c);

/* specification formelle
*
*   entr�e : 
*   sortie :
*   pr�condition :
*   postcondition :
*
*/
void sauvegarder(REPERTOIRE rep);

/* specification formelle
*
*   entr�e : 
*   sortie :
*   pr�condition :
*   postcondition :
*
*/
REPERTOIRE liberte(REPERTOIRE rep);

/* specification formelle
*
*   entr�e : 
*   sortie :
*   pr�condition :
*   postcondition :
*
*/
REPERTOIRE suppression(REPERTOIRE rep, int inditem);
int recherche(REPERTOIRE rep, int champ);

/* specification formelle
*
*   entr�e : 
*   sortie :
*   pr�condition :
*   postcondition :
*
*/
int compare(CLIENT c1, CLIENT c2, int champ);

/* specification formelle
*
*   entr�e : 
*   sortie :
*   pr�condition :
*   postcondition :
*
*/
REPERTOIRE modifier(REPERTOIRE rep, int inditem, int tabelement[], CLIENT cl);

/* specification formelle
*
*   entr�e :
*   sortie :
*   pr�condition :
*   postcondition :
*
*/
int recherche(REPERTOIRE rep, CLIENT c, int* dernier);

/* specification formelle
*
*   entr�e :
*   sortie :
*   pr�condition :
*   postcondition :
*
*/
char* RecupereChamp(CLIENT client, int numerochamp);

/* specification formelle
*
*   entr�e : 
*   sortie : 
*   pr�condition : 
*   postcondition : 
*
*/
void interfacemodiff(REPERTOIRE rep, int item);