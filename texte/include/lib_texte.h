#ifndef INDEXATION_TEXTE_H_INCLUS
#define INDEXATION_TEXTE_H_INCLUS

#include "descripteur_Txt.h"

/*Pile1*/

typedef struct s_cel1{
    int fich;
    int nb;
    struct s_cel1 * suiv;
} Cel1;

typedef Cel1 * Table;

/*Pile2*/

typedef struct s_cel2{
    char mot [50];
    int nbMot;
    Table table;
    struct s_cel2 * motTableSuiv;
} Cel2;

typedef Cel2 * MotTable;

void indexation_texte(void);

void recupListeFichierTxt();
void redirCleanTok();
DESCRIPT_TXT crea_descript_txt(char * fileName,int ident,char * cheminRepertoireTok);
void ajoutListeBaseTxt(char * fileName, int ident);

PILE init_PILE();
void affiche_PILE(PILE p);
int PILE_estVide(PILE p);
PILE emPILE(PILE p, MOT mot);
PILE dePILE(PILE p, MOT * mot);

void filtrage (char * fileName, char * pathTraitement);
void enleverStopWord(char * mot, char * pathFile);
void creerFichTok(char * pathFile);
void nettoyage (char * fileName, char * pathStockageFich, char * pathTraitement);
void copieRepTravail(char * pathStockageFich, char *fileName, char * pathFile);
void enleverBalise(char * pathFile);
void changerMajMin(char * pathFile);
void supprNPremLig(int n, char * pathFile);
void supprApostrophe(char * pathFile);
void supprChiffre(char * pathFile);
void supprPonctu(char * pathFile);
void supprTiret(char * pathFile);
void supprXml(char * pathFile);

MOT initMot();
MOT addMot(char * motTxt, int ident,char * fileName);
int chercheNbOccur(char * mot, char * fileName);
void creerPileMot(PILE * pileMot , char * fileName, int * nbMotDiff, int ident, char * cheminRepertoireTok);
DESCRIPT_TXT initDescript();
DESCRIPT_TXT creerDescript(char * fileName, int ident,char * cheminRepertoireTok);
void concatBaseDescript(DESCRIPT_TXT descript);
int comptageNbMot(char * fileName);

Table initT();
Table addT(Table p, int fich, int nb);
void affT(Table p);
MotTable initM();
MotTable addM(MotTable p, char * MotTable);
MotTable add(MotTable p, int nb, char * MotTable, int fich);
void aff(MotTable p);
MotTable table(MotTable p, int ident, char *fichier);

void recherche_comparaison_texte(char * pathFileRecherchee, int nbFichierTxt);
void nbOccurCommun(int * tabOccurCommun, DESCRIPT_TXT descriptMotRech, int nbFichierTxt);
int compareNbOccurComm(int * tabOccurCommun,int nbFichierTxt);

void rech_MC(char * mot);
void open_fich();

#endif
