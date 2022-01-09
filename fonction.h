
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

REPERTOIRE Importer(char nom_fichier[30]);
void Afficher2(REPERTOIRE rep, char* valeur, int tabind[]);
REPERTOIRE InterfaceTerminal(REPERTOIRE rep);
void triindirecte(REPERTOIRE rep, int champ);
void tripeigne(REPERTOIRE rep, int champ);
int numero(char* nom);
void retourchariot(char* chaine);
void interfaceaff(REPERTOIRE rep, int* tabind);
int Afficher(REPERTOIRE rep, int tabcol[], int tabfiltre[], char* filtre, int champ);
REPERTOIRE ajout(REPERTOIRE rep);
void sauvegarder(REPERTOIRE rep);
REPERTOIRE liberte(REPERTOIRE rep);
REPERTOIRE suppression(REPERTOIRE rep, int inditem);
int compare(CLIENT c1, CLIENT c2, int champ);
REPERTOIRE modifier(REPERTOIRE rep, int inditem, int tabelement[]);

