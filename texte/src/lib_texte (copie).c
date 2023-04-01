#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
/*
#include "/home/pfr/pfr_code/texte/include/clean.h"
#include "/home/pfr/pfr_code/texte/include/tok.h"
#include "/home/pfr/pfr_code/texte/include/descripteur_Txt.h"
#include "/home/pfr/pfr_code/texte/include/pile_dynamique.h"
#include "/home/pfr/pfr_code/texte/include/indexation_texte.h"
#include "/home/pfr/pfr_code/texte/include/piles2.h"
#include "/home/pfr/pfr_code/texte/include/table_index.h"
*/
//#include "/home/pfr/pfr_code/texte/include/lib_texte.h"
#include "../include/lib_texte.h"

#define CHEMIN_FICHIER_STOPWORD "../../data/stop_words_french.txt"
#define CHEMIN_STOCKAGE_FICH_IDX "../../../pfr/texte/fich_textes"
#define CHEMIN_TRAITEMENT_FICH_IDX "../../../pfr_code/traitement"
#define CHEMIN_LISTE_FICHIER_IDX "../../data/listeFichierTxt.txt"
#define CHEMIN_FICHIER_SOURCE "../../../pfr/texte/fich_textes/%s.xml"
#define CHEMIN_FICHIER_TOK_IDX "../../../pfr/texte/tok"

#define CHEMIN_STOCKAGE_FICH_RECH "../../../pfr/texte/recherche_texte"
#define CHEMIN_TRAITEMENT_FICH_RECH "../../../pfr_code/traitement"
#define CHEMIN_FICHIER_TOK_RECH "../../traitement"
#define CHEMIN_BASE_DESCIPTEUR_TEXTE "../../../pfr/texte/descripteurs_textes/Base_Descripteur_Texte.txt"
#define CHEMIN_LISTE_BASE_TEXTE "../../../pfr/texte/descripteurs_textes/Liste_Base_Texte.txt"
#define CHEMIN_FICHIER_OCCURENCE_COMMUN "../../data/OccurenceCommun.txt"
#define CHEMIN_LISTE_RECHERCHE_TRIEE_IDENT "../../data/liste_recherche_triee_ident.txt"
#define CHEMIN_LISTE_RECHERCHE_IDENT "../../data/liste_recherche_ident.txt"
#define CHEMIN_LISTE_RECHERCHE_TRIEE "../../data/liste_recherche_triee.txt"


void indexation_texte(void){

    char fileName[256]={0};
    char pathFileSRC[256]={0};
    //char cheminListFich[256]={0};
    //char cheminFich[256]={0};
    
    recupListeFichierTxt();

    FILE * listeFichier = fopen(CHEMIN_LISTE_FICHIER_IDX,"r");
    
    if(listeFichier != NULL){
        while(fscanf(listeFichier,"%s",fileName)==1){
            nettoyage(fileName,CHEMIN_STOCKAGE_FICH_IDX ,CHEMIN_TRAITEMENT_FICH_IDX);
            filtrage(fileName,CHEMIN_TRAITEMENT_FICH_IDX);
        }
        redirCleanTok();
    }
    
    DESCRIPT_TXT descript;
    MotTable pMotTable = initM();
    int ident = 1;
    system("echo '' > ../../../pfr/texte/descripteurs_textes/Base_Descripteur_Texte.txt");
    system("echo '' > ../../../pfr/texte/descripteurs_textes/Liste_Base_Texte.txt");
    system("echo '' > ../../../pfr/texte/descripteurs_textes/Table_Index_Texte.txt");
    
    fseek(listeFichier,0,SEEK_SET);

    while(fscanf(listeFichier,"%s",fileName)==1){
        int ret = snprintf(pathFileSRC,sizeof(pathFileSRC),CHEMIN_FICHIER_SOURCE,fileName);
        if(ret<0){
            abort();
        }
        printf("\n%s",fileName);
        descript = crea_descript_txt(fileName,ident,CHEMIN_FICHIER_TOK_IDX);
        concatBaseDescript(descript);
        ajoutListeBaseTxt(pathFileSRC,ident);
        pMotTable = table(pMotTable,ident,fileName);
        ident ++;
    }
    aff(pMotTable);
    fclose(listeFichier);
}

// Créé un fichier avec la liste des textes dans le répertoire et supprime l'extension .xml du nom des fichier
void recupListeFichierTxt()
{
    system("ls ../../../pfr/texte/fich_textes > ../../data/listeFichierTxt.txt");
    system("sed -i -e 's/.xml//g' ../../data/listeFichierTxt.txt");
}

//Redirection des fichier Clean et Tok dans le bon répertoire
void redirCleanTok(){
    system("cd ../../traitement/");
    system("mv ../../traitement/*.tok ../../../pfr/texte/tok;mv ../../traitement/*.clean ../../../pfr/texte/clean");
}

//Créer un descripteur texte .xml à partir du nom du fichier, de l'identifiant et du chemin vers le répertoire tok
DESCRIPT_TXT crea_descript_txt(char * fileName,int ident, char * cheminRepertoireTok){

    DESCRIPT_TXT descripteur;

    descripteur = initDescript();
    return descripteur = creerDescript(fileName,ident,cheminRepertoireTok);
}

void ajoutListeBaseTxt(char * pathFileSRC, int ident){

    char echoList[256]={0};
    if(ident<10){
        int ret = snprintf(echoList,sizeof(echoList),"echo 0%d %s >> ../../../pfr/texte/descripteurs_textes/Liste_Base_Texte.txt",ident,pathFileSRC);
        if(ret<0){
            abort();
        }
        else system(echoList);
    }
    else{
        int ret = snprintf(echoList,sizeof(echoList),"echo %d %s >> ../../../pfr/texte/descripteurs_textes/Liste_Base_Texte.txt",ident,pathFileSRC);
        if(ret<0){
            abort();
        }
        else system(echoList);
    }
}

void nettoyage(char *fileName, char * pathStockageFich, char * pathTraitement)
{
    //initialisation du chemin du fichier dans le répertoire de travail
    char pathFile[256]={0};
    int ret = snprintf(pathFile, sizeof(pathFile), "%s/%s",pathTraitement, fileName);
    if (ret < 0) {
        abort();
    }

    copieRepTravail(pathStockageFich, fileName, pathFile);
    enleverBalise(pathFile);
    changerMajMin(pathFile);
    supprNPremLig(3,pathFile);
    supprApostrophe(pathFile);
    supprChiffre(pathFile);
    supprPonctu(pathFile);
    supprTiret(pathFile);
    supprXml(pathFile);
}

// copier le fichier .xml du répertoire de stockage vers le répertoire de travail
void copieRepTravail(char * pathStockageFich, char *fileName, char * pathFile){

    char copieRepTravail[256] = {0};
    int ret = snprintf(copieRepTravail, sizeof(copieRepTravail), "cp %s/%s.xml %s.xml",pathStockageFich, fileName, pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(copieRepTravail);
    }
}

// enlever les balises dans ls fichier .xml
void enleverBalise(char * pathFile){

    char enleverBalise[256] = {0};
    int ret = snprintf(enleverBalise, sizeof(enleverBalise), "sed -i -e 's/<[^>]*>//g' %s.xml", pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(enleverBalise);
    }
}

// Changer les majuscules en minuscules
void changerMajMin(char * pathFile){
    char changeMajMin[256] = {0};
    int ret = snprintf(changeMajMin, sizeof(changeMajMin), "cat %s.xml | tr A-Z a-z > %sV2.xml", pathFile, pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(changeMajMin);
    }
}

// Supprimer les n première lignes (car lignes vides)
void supprNPremLig(int n, char * pathFile){
    char supprPremLig[256] = {0};
    int ret = snprintf(supprPremLig, sizeof(supprPremLig), "sed -i '1,%dd' %sV2.xml",n, pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(supprPremLig);
    }
}

// suppression ' et "
void supprApostrophe(char * pathFile){
    char supprApostrophe[256] = {0}; 
    system("chmod +x ../../texte/src/remove_apostrophe.sh");
    int ret = snprintf(supprApostrophe, sizeof(supprApostrophe), "../../texte/src/remove_apostrophe.sh %sV2.xml", pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(supprApostrophe);
    }
}

// Supprimer les chiffres
void supprChiffre(char * pathFile){
    char supprChiffre[256] = {0};
    int ret = snprintf(supprChiffre, sizeof(supprChiffre), "sed -i -e 's/[0-9]//g' %sV2.xml", pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(supprChiffre);
    }
}

// Remplace de la ponctuation et des symboles (hors -) par des " "
void supprPonctu(char * pathFile){
    char supprPonctu[256] = {0};
    int ret = snprintf(supprPonctu, sizeof(supprPonctu), "sed -i -e 's/[.,;:?!()%%_<>/$€]/ /g' %sV2.xml", pathFile);
    if (ret < 0)
    {
        abort();
    }
    else
        system(supprPonctu);
}

// Suppression des "-" et création du fichier .clean
void supprTiret(char * pathFile){
    char supprTiret[256] = {0};
    int ret = snprintf(supprTiret, sizeof(supprTiret), "sed 's/-/ /g' %sV2.xml > %s.clean", pathFile, pathFile);
    if (ret < 0)
    {
        abort();
    }
    else
        system(supprTiret);
}

// Suppression des fichiers .xml
void supprXml(char * pathFile){
    char supprXmlV2[256] = {0};
    int ret = snprintf(supprXmlV2, sizeof(supprXmlV2), "rm %sV2.xml;rm %s.xml ", pathFile, pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(supprXmlV2);
    }
}

void filtrage(char *fileName, char * pathTraitement)
{
    char mot[256] = {0};
    char pathChaine[256] = {0};
    char pathFile[256] = {0};
    int ret;
    int test;

    ret = snprintf(pathFile, sizeof(pathFile), "%s/%s",pathTraitement, fileName);
    if (ret < 0) {
        abort();
    }

    ret = snprintf(pathChaine, sizeof(pathChaine), "%s.clean", pathFile);
    if (ret < 0) {
        abort();
    }

    creerFichTok(pathFile);

    FILE *fichier_clean = fopen(pathChaine, "r");

    if (fichier_clean != NULL)
    {
        while (fscanf(fichier_clean, "%s", mot) == 1)
        {
            enleverStopWord(mot,pathFile);
        }
    }
    fclose(fichier_clean);
}

void enleverStopWord(char * mot, char * pathFile){

    char stopWord[256] = {0};
    char ajoutMotTok[256] = {0};
    FILE *fichierStopWord = fopen(CHEMIN_FICHIER_STOPWORD, "r");
    int is_stopword = 0;

    //lecture du stopword dans le fichier stop_words_french.txt
    while (fscanf(fichierStopWord,"%s", stopWord) == 1)
    {
        if ((strcmp(mot, stopWord) == 0) || (strlen(mot) <=2))
        {
            is_stopword = 1;
            break;
        }
    }

    //ajout du mot dans le .tok si ce n'est pas un stopword
    if (is_stopword == 0)
    {
        int ret = snprintf(ajoutMotTok, sizeof(ajoutMotTok), "echo %s >> %s.tok", mot, pathFile);
        if (ret < 0)
        {
            abort();
        }
        else system(ajoutMotTok);
    }
    fclose(fichierStopWord);    
}

// On vide ou créé le fichier .tok à partir du nom du fichier
void creerFichTok(char * pathFile){

    char creerFichTok[256]={0};
    int ret = snprintf(creerFichTok, sizeof(creerFichTok), "echo '' > %s.tok", pathFile);
    if (ret < 0) {
        abort();
    }
    else system(creerFichTok);
}

/*Pile1*/

Table initT() { return NULL; }

Table addT(Table p, int fich, int nb)
{
    Table paux = (Table)malloc(sizeof(Cel1));
    paux->fich = fich;
    paux->nb = nb;
    paux->suiv = p;
    return paux;
}

void affT(Table p)
{
    char chaine[256] = {0};
    while (p != NULL)
    {
        // printf("    %s %d\n", p->fich,p->nb);
        snprintf(chaine, 256, "echo '%d %d'>> ../../../pfr/texte/descripteurs_textes/Table_Index_Texte.txt", p->fich, p->nb);
        system(chaine);
        p = p->suiv;
    }
}

/*Pile2*/

MotTable initM() { return NULL; }

MotTable addM(MotTable p, char *mot)
{
    MotTable paux = (MotTable)malloc(sizeof(Cel2));
    snprintf(paux->mot, sizeof(paux->mot), "%s", mot);
    paux->nbMot=0;
    paux->table = NULL;
    paux->motTableSuiv = p;
    return paux;
}

MotTable add(MotTable p, int nb, char *mot, int fich)
{
    int nb_min;
    FILE *config = fopen("../../config.txt", "r");
    fscanf(config, "%d", &nb_min);
    fclose(config);

    MotTable paux = p;
    MotTable posC2 = NULL;
    if (nb >= nb_min)
    {
        while (paux != NULL)
        {
            if (strcmp(paux->mot, mot) == 0)
                posC2 = paux;
            paux = paux->motTableSuiv;
        }
        if (posC2 == NULL)
        {
            p = addM(p, mot);
            p->table = addT(p->table, fich, nb);
            p->nbMot++;
        }
        else
        {
            if (posC2->table->fich != fich)
            {
                posC2->table = addT(posC2->table, fich, nb);
                posC2->nbMot++;
            }
        }
    }
    return p;
}

void aff(MotTable p)
{
    char chaine[256] = {0};
    while (p != NULL)
    {
        // printf("%s\n",p->mot);
        snprintf(chaine, 256, "echo '%s' >> ../../../pfr/texte/descripteurs_textes/Table_Index_Texte.txt", p->mot);
        system(chaine);
        snprintf(chaine, 256, "echo '%d' >> ../../../pfr/texte/descripteurs_textes/Table_Index_Texte.txt", p->nbMot);
        system(chaine);
        if (p->table != NULL)
        {
            affT(p->table);
        }
        p = p->motTableSuiv;
    }
}

//initialise un mot
MOT initMot(){
    MOT mot;
    mot.ident = 0;
    mot.nb_occur = 0;
    mot.mot_suiv = NULL;
    return mot;
}

//ajoute les caractéristique d'un mot d'un fichier.tok
MOT addMot(char * motTxt, int ident,char * fileName){
    MOT mot;
    mot.ident = ident;
    snprintf(mot.mot,sizeof(mot.mot),"%s",motTxt);
    mot.nb_occur = chercheNbOccur(motTxt,fileName);
    mot.mot_suiv = NULL;
    return mot;
}

//Créé une pile de mot relatif à un fichier et met à jour le paramètre nbMotDiff du fichier.tok
void creerPileMot(PILE * pileMot , char * fileName, int * nbMotDiff, int ident, char * cheminRepertoireTok){
    char recupTokUniq[256]={0};   
    char motRecup[256]={0};
    char pathFile[256]={0};
    *pileMot = init_PILE();
    MOT mot = initMot();
    *nbMotDiff = 0;
    int nb_occ_min = 0;

    //Création  du fichier CloneTok avec une seule occurence pas mot du fichier .tok
    snprintf(recupTokUniq,sizeof(recupTokUniq),"sort %s/%s.tok | uniq > ../../traitement/CloneTok/%sClone.tok",cheminRepertoireTok,fileName,fileName);
    system(recupTokUniq);

    //ouverture du fichier Clone.tok
    snprintf(pathFile,sizeof(pathFile),"../../traitement/CloneTok/%sClone.tok",fileName);
    FILE * fichier_CloneTok = fopen(pathFile,"r");

    //récupération du nombre d'occurrence minimum pour qu'un mot soit ajouter au descripteur
    FILE * fichier_config = fopen("../../config.txt","r");
    fscanf(fichier_config,"%d",&nb_occ_min);
    fclose(fichier_config);
    
    //ajout des mots au descripteur (création de la pile de mot) 
    while(fscanf(fichier_CloneTok,"%s",motRecup)==1){
        mot = addMot(motRecup,ident,fileName);
        if((mot.nb_occur >= nb_occ_min)&&(strlen(mot.mot)>2)){
            *pileMot = emPILE(*pileMot,mot);
        }
    }
    //comptage du nombre de mot unique
    *nbMotDiff = comptageNbMot(pathFile);

    fclose(fichier_CloneTok);
}

//initialise le descripteur avec des valeurs par défaut
DESCRIPT_TXT initDescript(){
    DESCRIPT_TXT descript;
    descript.ident = 0;
    descript.pile_mot = init_PILE();
    descript.nb_mot_diff = 0;
    descript.taille_txt = 0;
    return descript;
}

//créé le descripteur d'un fichier.tok à partir du chemin du fichier source .xml (identifiant) et du fichier tok accessible dans l'arborescence de répertoires
DESCRIPT_TXT creerDescript(char * fileName, int ident,char * cheminRepertoireTok){

    DESCRIPT_TXT descript = initDescript();
    char pathFile[256]={0};
    //char motRecup[256]={0};

    descript.ident = ident;
    creerPileMot(&descript.pile_mot,fileName,&(descript.nb_mot_diff),ident,cheminRepertoireTok);
    snprintf(pathFile,sizeof(pathFile),"%s/%s.tok",cheminRepertoireTok,fileName);
    //Détermination de la taille du texte en nombre de mot
    descript.taille_txt= comptageNbMot(pathFile);
    return descript;
}

int chercheNbOccur(char * mot, char * fileName){

    char cptnbMot[256]={0};
    int nb_occurrence = 0;

    //comptage du nombre d'occurrence d'un mot dans le fichier passé en paramètre
    snprintf(cptnbMot, sizeof(cptnbMot), "grep -ow '%s' ../../pfr/texte/tok/%s.tok | wc -l > ../../data/nbOccur.txt",mot,fileName);
    system(cptnbMot);

    //récupération du nombre d'occurrence du mot dans le fichier nbOccur.txt
    FILE * nbOccur = fopen("../../data/nbOccur.txt","r");
    fscanf(nbOccur,"%d",&nb_occurrence);
    fclose(nbOccur);
    return nb_occurrence;
}

//ajout du descripteur au fichier bas descripteur texte
void concatBaseDescript(DESCRIPT_TXT descript){

    //ajout de l'identifiant
    char ajoutIdentDescript[256]={0};
    snprintf(ajoutIdentDescript,sizeof(ajoutIdentDescript),"echo %d >> ../../../pfr/texte/descripteurs_textes/Base_Descripteur_Texte.txt",descript.ident);
    system(ajoutIdentDescript);

    //ajout des mots
    char ajoutMotDescript[256]={0};
    MOT mot = initMot();
    while(!PILE_estVide(descript.pile_mot)){
        descript.pile_mot=dePILE(descript.pile_mot, &mot);
        snprintf(ajoutMotDescript,sizeof(ajoutMotDescript),"echo %d %s %d >> ../../../pfr/texte/descripteurs_textes/Base_Descripteur_Texte.txt",mot.ident,mot.mot,mot.nb_occur);
        system(ajoutMotDescript);
    }
    //ajout du nombre de mot différents
    char ajoutNbMotDiffDescript[256]={0};
    snprintf(ajoutNbMotDiffDescript,sizeof(ajoutNbMotDiffDescript),"echo %d >> ../../../pfr/texte/descripteurs_textes/Base_Descripteur_Texte.txt",descript.nb_mot_diff);
    system(ajoutNbMotDiffDescript);

    //ajout de la taille du texte en nombre de mot
    char ajoutNbMotDescript[256]={0};
    snprintf(ajoutNbMotDescript,sizeof(ajoutNbMotDescript),"echo %d >> ../../../pfr/texte/descripteurs_textes/Base_Descripteur_Texte.txt",descript.taille_txt);
    system(ajoutNbMotDescript);
} 

int comptageNbMot(char * pathFile){

    int ctpMot=0;
    char comptageMot[256]={0};
    //comptage du nombre de mot du fichier passer en paramètre
    snprintf(comptageMot,sizeof(comptageMot),"wc -w %s > ../../data/comptage.txt",pathFile);
    system(comptageMot);
    
    //récupération du nombre de mot dans le fichier comptage.txt
    FILE * comptage = fopen("../../data/comptage.txt","r");
    fscanf(comptage,"%d",&ctpMot);
    fclose(comptage);
    return ctpMot;
}

PILE init_PILE(){
	PILE p = NULL;
	return p;
}

void affiche_PILE(PILE p){
	
	while(p != NULL){
		printf("\n ident = %d,",p->ident);
    	printf("mot = %s,",p->mot);
		printf(" nb_occur = %d",p->nb_occur);
		p=p->mot_suiv;
	}
}

int PILE_estVide(PILE p){

	return (p == NULL);
}
//Empile un mot dans la pile de mot
PILE emPILE(PILE p, MOT mot){
	
	PILE paux =(PILE)malloc(sizeof(struct MOT));
	if(!PILE_estVide(paux)){
		paux->ident = mot.ident;
		snprintf(paux->mot,sizeof(paux->mot),"%s",mot.mot);
		paux->nb_occur = mot.nb_occur;
		paux->mot_suiv = p;
	}
	return paux;
}

PILE dePILE(PILE p, MOT * mot){

	PILE paux=p;
	if(!PILE_estVide(p)) {
		mot->ident = paux->ident;
		snprintf(mot->mot,sizeof(mot->mot),"%s",paux->mot);
		mot->nb_occur = paux->nb_occur;
		p = p->mot_suiv;
		free(paux);
	}
	return p;
}

MotTable table(MotTable p, int ident, char *fichier)
{
    char chaine1[256] = {0};
    char mot[256];
    int ret = snprintf(chaine1, 256, "../../../pfr/texte/tok/%s.tok", fichier);
    if (ret < 0)
    {
        abort();
    }
    FILE *fich = fopen(chaine1, "r");
    while (fscanf(fich, "%s", mot) == 1)
    {
        p = add(p, chercheNbOccur(mot, fichier), mot, ident);
    }
    fclose(fich);
    return p;
}

void nbOccurCommun(int * tabOccurCommun, DESCRIPT_TXT descriptRech, int nbFichierTxt){

    //initialisation du nombez d'occurrence de chaque fichier à 0
    for(int i=0; i<nbFichierTxt;i++){
        *(tabOccurCommun+i)=0;
    }
    MOT mot;
    char recupFichMotCommun[256]={0};
    system("echo '' > "CHEMIN_FICHIER_OCCURENCE_COMMUN);
    FILE * OccurenceCommun = fopen(CHEMIN_FICHIER_OCCURENCE_COMMUN,"r");
    int identFich;
    char motRecup[50]={0};
    int occur;

    //recherche parmis le mots de la pile de mot
    while(descriptRech.pile_mot != NULL){
        fseek(OccurenceCommun,0,SEEK_SET);
        descriptRech.pile_mot = dePILE(descriptRech.pile_mot, &mot);

        //Récupération de la liste des ideantifiants et du nombre d'occurrence pour le mot.mot
        int ret = snprintf(recupFichMotCommun,sizeof(recupFichMotCommun),"grep '%s ' %s > %s",mot.mot,CHEMIN_BASE_DESCIPTEUR_TEXTE,CHEMIN_FICHIER_OCCURENCE_COMMUN);
        if(ret<0){
            abort();
        }
        else system(recupFichMotCommun);

        //Récupération des données
        while(fscanf(OccurenceCommun,"%d",&identFich)==1){
            fscanf(OccurenceCommun,"%s",motRecup);
            fscanf(OccurenceCommun,"%d",&occur);
            if(strlen(motRecup)==strlen(mot.mot)){
                //ajout des occurrences au tableau
                if(occur <= mot.nb_occur){
                    *(tabOccurCommun+identFich-1)+= occur;
                }
                else *(tabOccurCommun+identFich-1)+= mot.nb_occur;
            }
        }
    }
    fclose(OccurenceCommun);
}

int compareNbOccurComm(int * tabOccurCommun,int nbFichierTxt){
    int occurMax = 0;
    int identFichier = 0;
    char addListeFichTriee[256]={0};
    char addListeFich[256]={0};

    system("echo '' > "CHEMIN_LISTE_RECHERCHE_TRIEE);

    for(int i=nbFichierTxt-1; i>=0; i--){

        //if(*(tabOccurCommun+i)> occurMax){
        //    occurMax = *(tabOccurCommun+i);
            identFichier = i+1;
            if(identFichier<10){
                int ret = snprintf(addListeFich,sizeof(addListeFich),"echo 0%d %d  >> "CHEMIN_LISTE_RECHERCHE_IDENT,identFichier,*(tabOccurCommun+i));
                if(ret<0){
                    abort();
                }
                system(addListeFich);
            }
            else {
                int ret = snprintf(addListeFich,sizeof(addListeFich),"echo %d %d  >> "CHEMIN_LISTE_RECHERCHE_IDENT,identFichier,*(tabOccurCommun+i));
                if(ret<0){
                    abort();
                }
                system(addListeFich);
            }
        //}
    }
    int ret = snprintf(addListeFichTriee,sizeof(addListeFichTriee),"sort -k2nr "CHEMIN_LISTE_RECHERCHE_IDENT" > "CHEMIN_LISTE_RECHERCHE_TRIEE_IDENT);
        if(ret<0){
            abort();
        }
        system(addListeFichTriee);
    return identFichier;
}

void recherche_comparaison_texte(char * pathFileRecherchee, int nbFichierTxt){

    char fileName[256]={0};
    char recupNom[256]={0};
    int recherTxt = 0;
    int * tabOccurCommun = (int *) malloc(sizeof(int)*nbFichierTxt);
    int identRessemble=0;

    system("echo '' > ../..//data/liste_recherche_triee_ident.txt");
    system("echo '' > ../..//data/liste_recherche_ident.txt");
    system("echo '' > ../..//data/liste_recherche_triee.txt");
    system("echo '' >../..//data/resultat_recherche.txt");
    char ecrireResult[256] ={0};

    int ret = snprintf(recupNom,sizeof(recupNom),"basename %s > ../../data/recupNomRech.txt",pathFileRecherchee);
    if(ret<0){
        abort();
    }
    else system(recupNom);

    FILE * recupNomRech = fopen("../../data/recupNomRech.txt","r");
    if(fscanf(recupNomRech,"%s",fileName)==1){
        system("rm -f ../../traitement/*.tok;rm -f ../../traitement/*.clean;");
        nettoyage(fileName,CHEMIN_STOCKAGE_FICH_RECH,CHEMIN_TRAITEMENT_FICH_RECH);
        filtrage(fileName,CHEMIN_TRAITEMENT_FICH_RECH);
    }
    fclose(recupNomRech);
    DESCRIPT_TXT descriptRech = initDescript();
    descriptRech = crea_descript_txt(fileName,0,CHEMIN_FICHIER_TOK_RECH);

    nbOccurCommun(tabOccurCommun, descriptRech, nbFichierTxt);
    identRessemble = compareNbOccurComm(tabOccurCommun,nbFichierTxt);

    free(tabOccurCommun);

    FILE * listeTrieeIdent = fopen(CHEMIN_LISTE_RECHERCHE_TRIEE_IDENT,"r");
    char ident[10] ={0};
    int occurrence;
    char grepIdent[256]={0};
    while(fscanf(listeTrieeIdent,"%s",ident)==1){
        fscanf(listeTrieeIdent,"%d",&occurrence);
        int ret = snprintf(grepIdent,sizeof(grepIdent),"grep '%s ' "CHEMIN_LISTE_BASE_TEXTE" >> "CHEMIN_LISTE_RECHERCHE_TRIEE" ; sed -i -e 's/%s //g' "CHEMIN_LISTE_RECHERCHE_TRIEE,ident,ident);
        if(ret<0){
            abort();
        }
        else system(grepIdent);
    }

    FILE * listeRechTriee = fopen(CHEMIN_LISTE_RECHERCHE_TRIEE,"r");
    char chemin[256]={0};
    char garderNomFich[256]={0};
    while(fscanf(listeRechTriee,"%s",chemin)==1){
        /*
        int ret = snprintf(garderNomFich,sizeof(garderNomFich),"basename %s",chemin);
        if(ret<0){
            abort();
        }
        else system(garderNomFich);
        */
        int ret = snprintf(ecrireResult,sizeof(ecrireResult),"echo '%s' >> ../../data/resultat_recherche.txt",chemin);
        if(ret<0){
            abort();
        } system(ecrireResult);
    } 

    fseek(listeRechTriee,0,SEEK_SET);
    char cheminRechAfficher[256]={0};
    char ouvrirTexte[256]={0};
    fscanf(listeRechTriee,"%s",cheminRechAfficher);
    ret = snprintf(ouvrirTexte,sizeof(ouvrirTexte),"xdg-open %s",cheminRechAfficher);
    if(ret<0){
        abort();
    } system(ouvrirTexte);

    fclose(listeTrieeIdent);
    fclose(listeRechTriee);

}

void rech_MC(char * mot){
    system("echo '' > ../../data/rech_mot_clef.txt");
    system("echo '' > ../../data/resultat_recherche.txt");
    char ecrireResult[256] ={0};
    char carac[200];
    char chaine[210];
    int nbMot;
    int id_courant;
    int id_fich;
    char chemin[200];
    FILE * table =fopen("../../../pfr/texte/descripteurs_textes/Table_Index_Texte.txt","r"); 
    while(fscanf(table,"%s",carac)){
        if(strcmp(carac,mot)==0){
            fscanf(table,"%d",&nbMot);
            int fich;
            int nb;
            for(int i=0;i<nbMot;i++){
                fscanf(table,"%d",&fich);
                fscanf(table,"%d",&nb);
                snprintf(chaine, 150,"echo '%d %d'>> ../../data/rech_mot_clef.txt",fich,nb);
                system(chaine);
            }
            snprintf(chaine,270,"sort -k 2 -nr ../../data/rech_mot_clef.txt > ../../data/rech_mot_clef_tri.txt");
            system(chaine);
            FILE *rech = fopen("../../data/rech_mot_clef_tri.txt","r");
            while (fscanf(rech,"%d",&id_fich)==1){
                fscanf(rech,"%d",&nb);
                FILE *base = fopen("../../../pfr/texte/descripteurs_textes/Liste_Base_Texte.txt", "r");
                while (fscanf(base,"%d",&id_courant) == 1){
                    fscanf(base,"%s",chemin);
                    if(id_courant==id_fich){
                        //printf("%s %d\n",chemin,nb);
                        int ret = snprintf(ecrireResult,sizeof(ecrireResult),"echo '%s %d' >> ../../data/resultat_recherche.txt",chemin,nb);
                        if(ret<0){
                            abort();
                        } system(ecrireResult);
                    }
                }
                fclose(base);
            }
            fclose(rech);
            break;
        }
    }
    fclose(table);
}


void open_fich(){
    int ident;
    int id_courant;
    char chemin[150] ={0};
    char chaine[150] = {0};
    FILE * rech = fopen("/home/pfr/pfr_code/data/rech_mot_clef_tri.txt","r");
    fscanf(rech,"%d",&ident);
    fclose(rech);
    FILE *fich = fopen("/home/pfr/pfr/texte/descripteurs_textes/Liste_Base_Texte.txt", "r");
    while (fscanf(fich,"%d",&id_courant) == 1){
        fscanf(fich,"%s",chemin);
        if(id_courant==ident){
            snprintf(chaine,220,"xdg-open %s",chemin);
            system(chaine);
            break;
        }
    }
    fclose(fich);
}

