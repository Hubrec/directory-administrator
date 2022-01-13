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
*   sortie : return la structure REPERTOIRE
*   précondition : pas de precondition, il s'agit simplement d'une redirection
*   postcondition : pas de postcondition, il s'agit simplement d'une redirection
*
*/
REPERTOIRE InterfaceTerminal(REPERTOIRE rep, char nomfichier[]);

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
*   entrée : argument de type champ de la structure ("prenom" ou "ville" par exemple)
*   sortie : numéro du champ qui correspond à l'argument
*   précondition : nom doit être : "prenom", "nom", "ville", "codepostale", "telephone", "email" ou encore "profession"
*   postcondition : renvoie le numéro qui correspond à l'argument , prenom = 0 et profession = 6
*
*/
int numero(char* nom);

/* specification formelle
*
*   entrée : une chaine de caractère
*   sortie : pas de return
*   précondition : la chaine de caractère ne doit pas être vide
*   postcondition : renvoie la chaine de caractère sans le caractère de retour à la ligne ou d'espacement selon le cas
*
*/
void retourchariot(char* chaine);

/* specification formelle
*
*   entrée : la structure REPERTOIRE
*   sortie : pas de return
*   précondition : pas de precondition
*   postcondition : pas de postcondition (fonction d'affichage console)
*
*/
void interfaceaff(REPERTOIRE rep);

/* specification formelle
*
*   entrée : la structure REPERTOIRE, un tableau de 0 ou 1 qui donne les colonnes a afficher, un tableau de 0 ou 1 qui donne les colonnes sur lesquelles afficher le filtre, un char* du filtre (mot), selon quel champ afficher
*   sortie : return un entier du nombre de clients qui ont ete affichés
*   précondition : champ compris entre 0 et 6
*   postcondition : a affiché tous les clients correspondant au filtre sauf si le filtre est vide a tout affiché
*
*/
int Afficher(REPERTOIRE rep, int tabcol[], int tabfiltre[], char* filtre, int champ);

/* specification formelle
*
*   entrée : la structure REPERTOIRE, la structure CLIENT qui contient les inofrmations du nouveau client a ajouter
*   sortie : return la structure REPERTOIRE
*   précondition : pas de preconditions
*   postcondition : a ajouté a la structure REPEROIRE le client qui a ete donné
*
*/
REPERTOIRE ajout(REPERTOIRE rep, CLIENT c);

/* specification formelle
*
*   entrée : la structure REPERTOIRE, le nom du fichier dans laquel on sauvegarde (celui qu'on a ouvert)
*   sortie : pas de sortie
*   précondition : pas de précondition
*   postcondition : a ecrit tous le contenu stoqué dans rep.clients dans le fichier donné a l'ouverture
*
*/
void sauvegarder(REPERTOIRE rep, char nomfichier[]);

/* specification formelle
*
*   entrée : la structure REPERTOIRE
*   sortie : la structure REPERTOIRE
*   précondition : doit etre appelé a la fermeture du prograppe
*   postcondition : libere toute la memoire allouée lors du programme
*
*/
REPERTOIRE liberte(REPERTOIRE rep);

/* specification formelle
*
*   entrée : la structure REPERTOIRE, l'indice de l'item a supprimer
*   sortie : la structure REPERTOIRE
*   précondition : inditem doit etre contenu entre 0 et la taille dufichier -1
*   postcondition : interverti le dernier client et celui a supprimer et réallou avec la taille -1 (supprimer le client selectionné)
*
*/
REPERTOIRE suppression(REPERTOIRE rep, int inditem);

/* specification formelle
*
*   entrée : deux clients en entrée, le champ du client
*   sortie : un entier 0 ou 1
*   précondition : champ compris entre 0 et 6
*   postcondition : return 1 si les deux clients sont identiques sur le champ en entrée et 0 sinon
*
*/
int compare(CLIENT c1, CLIENT c2, int champ);

/* specification formelle
*
*   entrée : la structure REPERTOIRE, l'indice du client a modifier, un tableau contenant les elements 
*   sortie : la structure REPERTOIRE
*   précondition : inditem doit etre compris entre 0 et le nombre de clients -1
*   postcondition : met les informations du client cl a l'indice inditem dans le REPERTOIRE
*
*/
REPERTOIRE modifier(REPERTOIRE rep, int inditem, int tabelement[], CLIENT cl);

/* specification formelle
*
*   entrée : la structure REPERTOIRE, un client compose de nom et prenom, un pointeur dernier pour avoir "deux return"
*   sortie : un entier du premier indice auquel on a le client recherche ou -1 si il n'y est pas
*   précondition : cl doit contenir un nom et prenom
*   postcondition : renvoi l'indice du premier et dernier indice ou on a les clients qui correspondent a la recherche
*
*/
int recherche(REPERTOIRE rep, CLIENT c, int* dernier);

/* specification formelle
*
*   entrée : la structure CLIENT donc un client, le numero du champ
*   sortie : un pointeur sur une chaine de charactere
*   précondition : numerochamp entre 0 et 6
*   postcondition : renvoi le contenu des informations du client entré au champ entré
*
*/
char* RecupereChamp(CLIENT client, int numerochamp);

/* specification formelle
*
*   entrée : la structure REPERTOIRE, l'entier item qui est l'element a modifier
*   sortie : pas de return
*   précondition : item entre 0 et la taille -1 du tableau de stockage des clients
*   postcondition : a demandé a l'utilisateur ce qu'il fallait modifier et par quoi puis appelle la fonction modifier
*
*/
void interfacemodiff(REPERTOIRE rep, int item); 