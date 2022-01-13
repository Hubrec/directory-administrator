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
*   sortie : return la structure REPERTOIRE
*   pr�condition : pas de precondition, il s'agit simplement d'une redirection
*   postcondition : pas de postcondition, il s'agit simplement d'une redirection
*
*/
REPERTOIRE InterfaceTerminal(REPERTOIRE rep, char nomfichier[]);

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
*   entr�e : argument de type champ de la structure ("prenom" ou "ville" par exemple)
*   sortie : num�ro du champ qui correspond � l'argument
*   pr�condition : nom doit �tre : "prenom", "nom", "ville", "codepostale", "telephone", "email" ou encore "profession"
*   postcondition : renvoie le num�ro qui correspond � l'argument , prenom = 0 et profession = 6
*
*/
int numero(char* nom);

/* specification formelle
*
*   entr�e : une chaine de caract�re
*   sortie : pas de return
*   pr�condition : la chaine de caract�re ne doit pas �tre vide
*   postcondition : renvoie la chaine de caract�re sans le caract�re de retour � la ligne ou d'espacement selon le cas
*
*/
void retourchariot(char* chaine);

/* specification formelle
*
*   entr�e : la structure REPERTOIRE
*   sortie : pas de return
*   pr�condition : pas de precondition
*   postcondition : pas de postcondition (fonction d'affichage console)
*
*/
void interfaceaff(REPERTOIRE rep);

/* specification formelle
*
*   entr�e : la structure REPERTOIRE, un tableau de 0 ou 1 qui donne les colonnes a afficher, un tableau de 0 ou 1 qui donne les colonnes sur lesquelles afficher le filtre, un char* du filtre (mot), selon quel champ afficher
*   sortie : return un entier du nombre de clients qui ont ete affich�s
*   pr�condition : champ compris entre 0 et 6
*   postcondition : a affich� tous les clients correspondant au filtre sauf si le filtre est vide a tout affich�
*
*/
int Afficher(REPERTOIRE rep, int tabcol[], int tabfiltre[], char* filtre, int champ);

/* specification formelle
*
*   entr�e : la structure REPERTOIRE, la structure CLIENT qui contient les inofrmations du nouveau client a ajouter
*   sortie : return la structure REPERTOIRE
*   pr�condition : pas de preconditions
*   postcondition : a ajout� a la structure REPEROIRE le client qui a ete donn�
*
*/
REPERTOIRE ajout(REPERTOIRE rep, CLIENT c);

/* specification formelle
*
*   entr�e : la structure REPERTOIRE, le nom du fichier dans laquel on sauvegarde (celui qu'on a ouvert)
*   sortie : pas de sortie
*   pr�condition : pas de pr�condition
*   postcondition : a ecrit tous le contenu stoqu� dans rep.clients dans le fichier donn� a l'ouverture
*
*/
void sauvegarder(REPERTOIRE rep, char nomfichier[]);

/* specification formelle
*
*   entr�e : la structure REPERTOIRE
*   sortie : la structure REPERTOIRE
*   pr�condition : doit etre appel� a la fermeture du prograppe
*   postcondition : libere toute la memoire allou�e lors du programme
*
*/
REPERTOIRE liberte(REPERTOIRE rep);

/* specification formelle
*
*   entr�e : la structure REPERTOIRE, l'indice de l'item a supprimer
*   sortie : la structure REPERTOIRE
*   pr�condition : inditem doit etre contenu entre 0 et la taille dufichier -1
*   postcondition : interverti le dernier client et celui a supprimer et r�allou avec la taille -1 (supprimer le client selectionn�)
*
*/
REPERTOIRE suppression(REPERTOIRE rep, int inditem);

/* specification formelle
*
*   entr�e : deux clients en entr�e, le champ du client
*   sortie : un entier 0 ou 1
*   pr�condition : champ compris entre 0 et 6
*   postcondition : return 1 si les deux clients sont identiques sur le champ en entr�e et 0 sinon
*
*/
int compare(CLIENT c1, CLIENT c2, int champ);

/* specification formelle
*
*   entr�e : la structure REPERTOIRE, l'indice du client a modifier, un tableau contenant les elements 
*   sortie : la structure REPERTOIRE
*   pr�condition : inditem doit etre compris entre 0 et le nombre de clients -1
*   postcondition : met les informations du client cl a l'indice inditem dans le REPERTOIRE
*
*/
REPERTOIRE modifier(REPERTOIRE rep, int inditem, int tabelement[], CLIENT cl);

/* specification formelle
*
*   entr�e : la structure REPERTOIRE, un client compose de nom et prenom, un pointeur dernier pour avoir "deux return"
*   sortie : un entier du premier indice auquel on a le client recherche ou -1 si il n'y est pas
*   pr�condition : cl doit contenir un nom et prenom
*   postcondition : renvoi l'indice du premier et dernier indice ou on a les clients qui correspondent a la recherche
*
*/
int recherche(REPERTOIRE rep, CLIENT c, int* dernier);

/* specification formelle
*
*   entr�e : la structure CLIENT donc un client, le numero du champ
*   sortie : un pointeur sur une chaine de charactere
*   pr�condition : numerochamp entre 0 et 6
*   postcondition : renvoi le contenu des informations du client entr� au champ entr�
*
*/
char* RecupereChamp(CLIENT client, int numerochamp);

/* specification formelle
*
*   entr�e : la structure REPERTOIRE, l'entier item qui est l'element a modifier
*   sortie : pas de return
*   pr�condition : item entre 0 et la taille -1 du tableau de stockage des clients
*   postcondition : a demand� a l'utilisateur ce qu'il fallait modifier et par quoi puis appelle la fonction modifier
*
*/
void interfacemodiff(REPERTOIRE rep, int item); 