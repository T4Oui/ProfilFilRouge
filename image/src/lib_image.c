#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include </home/pfr/pfr_code/image/include/lib_image.h>

int tab_taille_couleur(int config,int noiroublanc)
{   
    int taille=0;
        if ((config==2)&&(noiroublanc==0)) 
        {
            taille=64; // 64 valeurs et l'identificateur stocké ailleurs
        }
        else if ((config==3)&&(noiroublanc==0))
        {

            taille=512; // 512 valeurs et l'identificateur stocké ailleurs
        }
        else if ((config==2)&&(noiroublanc==1))
        {

            taille=4; // 4 valeurs et l'identificateur stocké ailleurs
        }
        else if ((config==3)&&(noiroublanc==1))
        {

            taille=8; // 8 valeurs et l'identificateur stocké ailleurs
        }
        return taille;
}


 int configurationR  (FILE* fichier)
 {
  int carac=0;
  fseek(fichier,12,SEEK_SET); //permet de placer le curseur au niveau du caractère 35 (valeur de quantification) 
  fscanf(fichier,"%d",&carac); // lis le caractère au niveau du curseur
  return carac;
  }

  
float pourcentage(float partie,int total)
{
    return (100*partie/total); //retourne un pourcentage pouvant être flottant
}

 int intersection (int* tab1, int* tab2 ,int taille)
 {
    int val1=0, val2=0 , total=0 ;
    for (int i = 0; i < taille; i++)// on parcourt toute les cases du tableau 

    {
        val1 = *(tab1+i); //pointeur sur le contenu de l'adresse (on incrémente l'adresse de i pour parcourir toutes les cases du tableau)
        val2 = *(tab2+i);
        if(val1<=val2)
        {
            total=total+val1; //on fait la somme des minimums afin d'obtenir à la fin un total représentant ce qu'il y a en commun entre les deux histogramme
        }
        else 
        {
            total=total+val2;
        }
    }
    return total;
 }

 void remplissagestructure (TAB* tableau,int bit_quantification, FILE* base_descripteur_image,int noiroublanc)
 {
    int string=0;
    tableau->nb_valeur=tab_taille_couleur(bit_quantification,noiroublanc); // on récupère le nombre de valeurs grâce à tab_taillecouleur
    fscanf(base_descripteur_image,"%d",&string);
    tableau->identifiant=string; //l'identificateur est stocké dans un champ réservé pour lui dans la structure
    for(int i =0;i<tableau->nb_valeur;i++)
    {
        fscanf(base_descripteur_image,"%d",&string);
        tableau -> T[i] = string; // le tableau contient seulement les valeurs de chaque couleur
    } 
 }

void remplissagetab (TAB* tableau1,int nbdescripteurs,int noiroublanc)

 {
    if(noiroublanc==0)
    {
        FILE* base_descripteur_image = fopen("/home/pfr/pfr/image/descripteurs_images/base_descripteur_image_couleur.txt","r");
        FILE* config = fopen("/home/pfr/pfr_code/config.txt","r");
        int nb=configurationR(config);
        for(int i=0;i<nbdescripteurs;i++)    
        {
            remplissagestructure((tableau1+i),nb,base_descripteur_image,noiroublanc); //pour chaque descripteur on remplit sa structure
        } 
        fclose(base_descripteur_image);
        fclose(config);
    }
    else
    {
        FILE* base_descripteur_image = fopen("/home/pfr/pfr/image/descripteurs_images/base_descripteur_image_NB.txt","r");
        FILE* config = fopen("/home/pfr/pfr_code/config.txt","r");
        int nb=configurationR(config);
        for(int i=0;i<nbdescripteurs;i++)    
        {

            remplissagestructure((tableau1+i),nb,base_descripteur_image,noiroublanc);
        }
        fclose(base_descripteur_image);
        fclose(config);
    }
 }

void affichagetab (TAB*tableau, int tailletableau)
{
for(int j=0;j<tailletableau;j++)
{
    for (int i = 0; i < 63; i++)
    {
        printf("%d",(tableau+j)->T[i]); //permet d'afficher toutes les valeurs des nbdescripteurs utile pour le débuggage
    }
    printf("\n\n");
}   
}
int compterlignes(FILE* fichier)
{
int c=0;;
int nblig = 1; //initialisation à 1 car il n'y a pas d'\n avant la première ligne mais on la compte quand même
while((c=fgetc(fichier)) != EOF) // on étudie tous les caractères du fichier
{
	if(c=='\n') // si c'est un caractere de fin de ligne on compte une ligne 
    {
        nblig++;
    }
}
return nblig;
}


void comparaison_couleur(TAB* descripteur, int identifiant, int nbdescripteurs)
{
    int somme=0;
    float tab[nbdescripteurs];
    for(int i=0;i<nbdescripteurs;i++)
    {
        if(((descripteur+i)->identifiant)==identifiant)
        {
            for(int j=0;j<nbdescripteurs;j++)
            {
                if (j==i)
                {

                }

                else
                {
                    somme=intersection((descripteur+i)->T,(descripteur+j)->T,((descripteur+j)->nb_valeur));
                    (descripteur+j)->pourcentage=pourcentage(somme,((descripteur)+i)->total);
                }


            }
        }
    }


}


 void malloc_structure(TAB* tab,int nbdescripteurs)
 {
    for(int i=0;i<nbdescripteurs;i++)
    {
        (tab+i)->T=(int*)malloc(sizeof(int)*(tab->nb_valeur));
        for(int j=0;j<tab->nb_valeur;j++)
        {
               (tab+i)->T[j]=0;          // cela permet d'allouer la mémoir popur le tableau de chaque descripteur
        }
    }
 }
 void free_structure(TAB* tab,int nbdescripteurs)
 {
        for(int j=0;j<nbdescripteurs;j++)
        {
            free(((tab+j)->T)); // permet de free la première case de chaque tableau
        }
}


 void total(TAB* descripteur,int tabtaillemax)
 {
    for(int j=0;j<tabtaillemax;j++)
    {
        int somme=0;
        for (int i = 0; i < (descripteur+j)->nb_valeur; i++)
        {
            somme=somme+((descripteur+j)->T[i]);      // calcul simplement le total
        }
        (descripteur+j)->total=somme;

    }
 }


void afficher_pourcentage(STRUCTPOURC* tableau2, int nbdescripteurs, float pourcentagemini)
    {
        char resultat[256]={0};
        system("echo '' > /home/pfr/pfr_code/data/resultat_recherche.txt");
        for(int t=nbdescripteurs-1;t>=1;t--) 
        {            if(tableau2[t].pourcentage>=pourcentagemini)
            {
                //printf("%s\t%f\n",tableau2[t].fichier,(tableau2[t]).pourcentage);
                snprintf(resultat, sizeof(resultat),"echo '%f %s' >> /home/pfr/pfr_code/data/resultat_recherche.txt",(tableau2[t]).pourcentage,tableau2[t].fichier);
                system(resultat);
            }
        }
    }
void tri (STRUCTPOURC* tableau2, int nbdescripteurs)
{
int i=0, j=0, d=0;
float c=0;
for(i=0;i<nbdescripteurs-1;i++)
{


    for(j=i+1;j<nbdescripteurs;j++)
    {

    
        if ( tableau2[i].pourcentage > tableau2[j].pourcentage )  // tri structures en fonction de la valeur de leur pourcentage
        {
            c = tableau2[i].pourcentage;
            d=tableau2[i].identifiant;
            tableau2[i].pourcentage = tableau2[j].pourcentage;
            tableau2[i].identifiant = tableau2[j].identifiant;
            tableau2[j].pourcentage = c;
            tableau2[j].identifiant=d;
        }
    }

}
}
void remplissagetabpourcent(STRUCTPOURC* tableau2, TAB* tableau1, int nbdescripteurs)
{
    for(int z=0;z<nbdescripteurs;z++)
    {
        (tableau2[z]).pourcentage=(tableau1[z]).pourcentage;
        (tableau2[z]).identifiant=(tableau1[z]).identifiant;

    }
}

int comptageNbLigne(char * pathFile){

    int ctpMot=0;
    char comptageMot[256]={0};
    //comptage du nombre de mot du fichier passer en paramètre
    snprintf(comptageMot,sizeof(comptageMot),"wc -l %s > /home/pfr/pfr_code/data/comptage.txt",pathFile);
    system(comptageMot);
    
    //récupération du nombre de mot dans le fichier comptage.txt
    FILE * comptage = fopen("/home/pfr/pfr_code/data/comptage.txt","r");
    fscanf(comptage,"%d",&ctpMot);
    fclose(comptage);
    return ctpMot;
}

 int nbdenbdescripteurs(int noiroublanc)
 {
    int nbdescripteurs=0;
        if(noiroublanc==0)
    {
        nbdescripteurs = comptageNbLigne("/home/pfr/pfr/image/descripteurs_images/base_descripteur_image_couleur.txt");
    }
    else
    {
        nbdescripteurs = comptageNbLigne("/home/pfr/pfr/image/descripteurs_images/base_descripteur_image_NB.txt");
    }
    return nbdescripteurs;

 }

 void afficher_resultat_couleur(STRUCTPOURC* tableau2, int nbdescripteurs)
    {
    int id_courant=0;
    FILE *fich = fopen("/home/pfr/pfr/image/descripteurs_images/base_image_couleur.txt", "r");
    char chemin[256] ={0};
    char chaine[256] ={0};
    while (fscanf(fich,"%d",&id_courant) == 1)
        {
            fscanf(fich,"%s",chemin);
            if(id_courant==tableau2[nbdescripteurs-1].identifiant)//nbdescripteurs-1 car la structure du fichier recherché est toujours dans le tableau et on ne  veut pas afficher le pourcentage de ressemblance d'un fichier avec lui-même
            {
                printf("%s\n",chemin);
            }
        }
    fclose(fich);
    }

 void afficher_resultat_noiroublanc(STRUCTPOURC* tableau2, int nbdescripteurs)
    {
    int id_courant=0;
    FILE *fich = fopen("/home/pfr/pfr/image/descripteurs_images/base_image_noirblanc.txt", "r");
    char chemin[256] ={0};
    char chaine[256] ={0};
    while (fscanf(fich,"%d",&id_courant) == 1)
        {
            fscanf(fich,"%s",chemin);
            if(id_courant==tableau2[nbdescripteurs-1].identifiant)//nbdescripteurs-1 car la structure du fichier recherché est toujours dans le tableau et on ne  veut pas afficher le pourcentage de ressemblance d'un fichier avec lui-même
            {
                printf("%s\n",chemin);
            }
        }
    fclose(fich);
    }

void recherchenoiretblanc(int fichierrecherche, float pourcentagemini,char* fichier)
{
    FILE* config = fopen("/home/pfr/pfr_code/config.txt","r");
    int noiroublanc=1;
    int nbdescripteurs=0;
    int bit_config=0;
    nbdescripteurs=nbdenbdescripteurs(noiroublanc);
    
    TAB* tableau1=(TAB*)malloc(sizeof(struct TAB)*(nbdescripteurs)); //crée un tableau de la taille nombre de 
    bit_config=configurationR(config);
    tableau1->nb_valeur=tab_taille_couleur(bit_config,noiroublanc);
    malloc_structure(tableau1,nbdescripteurs);
    remplissagetab(tableau1,nbdescripteurs, noiroublanc);
    total(tableau1,nbdescripteurs);
    comparaison_couleur( tableau1,fichierrecherche,nbdescripteurs);
    STRUCTPOURC tableau2[nbdescripteurs]; //crée un tableau de la taille nombre de descripteur
    remplissagetabpourcent(tableau2,tableau1,nbdescripteurs);
    for(int i=0;i<nbdescripteurs;i++)
    {
        if(tableau2[i].identifiant==fichierrecherche)
        {
            tableau2[i].pourcentage=0;
        }
    }
    tri(tableau2,nbdescripteurs);
    recupfichier_noiroublanc(tableau2,nbdescripteurs);
    afficher_pourcentage(tableau2,nbdescripteurs,pourcentagemini);
    fclose(config);
    strcpy(fichier,tableau2[nbdescripteurs-1].fichier);
    free_structure(tableau1,nbdescripteurs);
    free(tableau1);//désallouement de l'espace mémoire
}
void recherchecouleur(int fichierrecherche, float pourcentagemini, char* fichier)
{
    FILE* config = fopen("/home/pfr/pfr_code/config.txt","r");
    int noiroublanc=0;
    int nbdescripteurs=0;
    int bit_config=0;
    nbdescripteurs=nbdenbdescripteurs(noiroublanc);
    TAB* tableau1=(TAB*)malloc(sizeof(struct TAB)*(nbdescripteurs)); //crée un tableau de la taille nombre de 
    bit_config=configurationR(config);
    tableau1->nb_valeur=tab_taille_couleur(bit_config,noiroublanc);
    malloc_structure(tableau1,nbdescripteurs);
    remplissagetab(tableau1,nbdescripteurs, noiroublanc);
    total(tableau1,nbdescripteurs);
    comparaison_couleur( tableau1,fichierrecherche,nbdescripteurs);
    STRUCTPOURC tableau2[nbdescripteurs]; //crée un tableau de la taille nombre de descripteur
    remplissagetabpourcent(tableau2,tableau1,nbdescripteurs);
    for(int i=0;i<nbdescripteurs;i++)
    {
        if(tableau2[i].identifiant==fichierrecherche)
        {
            tableau2[i].pourcentage=0;
        }
    }
    tri(tableau2,nbdescripteurs);
    recupfichier_couleur(tableau2, nbdescripteurs);
    afficher_pourcentage(tableau2,nbdescripteurs,pourcentagemini);
    fclose(config);
    strcpy(fichier,tableau2[nbdescripteurs-1].fichier);
    free_structure(tableau1,nbdescripteurs);
    free(tableau1);//désallouement de l'espace mémoire
}
void recupfichier_couleur (STRUCTPOURC* tab,int nbdescripteurs)
{
    FILE *fich = fopen("/home/pfr/pfr/image/descripteurs_images/base_image_couleur.txt", "r");
    int id_courant=0;
            for(int i=0;i<nbdescripteurs;i++)
            {
                fscanf(fich,"%d",&id_courant);
                for (int j = 0; j < nbdescripteurs; j++)
                {
                    if(id_courant==(tab+j)->identifiant)
                    {
                        fscanf(fich,"%s",((tab+j)->fichier));
                    }
                }
            }   
    fclose(fich);

}

void recupfichier_noiroublanc (STRUCTPOURC* tab,int nbdescripteurs)
{
    FILE *fich = fopen("/home/pfr/pfr/image/descripteurs_images/base_image_NB.txt", "r");
    int id_courant=0;
            for(int i=0;i<nbdescripteurs;i++)
            {
                fscanf(fich,"%d",&id_courant);
                for (int j = 0; j < nbdescripteurs; j++)
                {
                    if(id_courant==(tab+j)->identifiant)
                    {
                        fscanf(fich,"%s",((tab+j)->fichier));

                    }
                }
            } 
    fclose(fich);

}


void open_image_coul(char * fichier){
    char chaine[256] = {0};
    char nomfich[150];
    char changerNom[256]={0};
    int ret = snprintf(changerNom,sizeof(changerNom),"echo '%s' > /home/pfr/pfr_code/data/nfich_rech.txt ",fichier);
    if(ret<0){
        abort();
    } else system(changerNom);
    system("sed -i -e 's/txt/jpg/g' /home/pfr/pfr_code/data/nfich_rech.txt");
    FILE * fich =fopen("/home/pfr/pfr_code/data/nfich_rech.txt","r");
    fscanf(fich,"%s",nomfich);
    ret = snprintf(chaine,sizeof(chaine),"display /home/pfr/pfr/image/fich_images/%s",nomfich);
    if(ret<0){
        abort();
    } else system(chaine);
    fclose(fich);
}

void open_image_nb(char * fichier){
    char chaine[256] = {0};
    char nomfich[150];
    char changerNom[256]={0};
    int ret = snprintf(changerNom,sizeof(changerNom),"echo '%s' > /home/pfr/pfr_code/data/nfich_rech.txt ; sed -i -e 's/txt/bmp/g' /home/pfr/pfr_code/data/nfich_rech.txt",fichier);
    if(ret<0){
        abort();
    } else system(changerNom);
    FILE * fich =fopen("/home/pfr/pfr_code/data/nfich_rech.txt","r");
    fscanf(fich,"%s",nomfich);
    ret = snprintf(chaine,sizeof(chaine),"viewnior /home/pfr/pfr/image/fich_images/%s",nomfich);
    if(ret<0){
        abort();
    } else system(chaine);
    fclose(fich);
}

// Ouvrir le fichier avec le mode qui le prend en paramètre
FILE* openFile( const char * nomFichier , const char * m ) 
{
  FILE* file = fopen ( nomFichier , m) ; 
  if (file == NULL ) //Vérification si le fichier est bien ouvert ou non
  { 
    printf ( "error opening file ") ; 
  }
  return file ; 
}


// Fonction quantification qui prend en paramètre un tableau {R, V, B} si l'image est en couleur sinon {pixel, 0,0} et renvoie la nouvelle valeur de pixel
int quantification (int tab[] , int b , int n ) 
{ 

  int t[8] ;  
  int nouPix = 0 ; 
  int Nbr = (n *b)-1 ; //le nombre de bits nécessaire
  int i = 0;  //compteur
  while (( i<3) && (Nbr >=0 ))
   { 
    int a = tab[i] ; 
    for (int j = 0 ; j<8 ; j ++) //codage décimal binaire d'un pixel 
    {
       t[j] = a % 2 ;
       a = a / 2;
    } 
    if (n ==2)
    { 
       nouPix = nouPix + (t[7] * pow(2 , Nbr) )+ (t[6] * pow(2 , Nbr-1)) ;
       Nbr = Nbr - 2 ;
    } 
    else if (n ==3)
    { 
      nouPix = nouPix + (t[7] * pow(2 , Nbr) )+ (t[6] * pow(2 , Nbr-1)) + (t[5] * pow(2 , Nbr-2)) ;
      Nbr = Nbr - 3 ;
    } 
    i++ ; 
    }
  return ( nouPix) ; 
} 

//Parcourir le fichier image .txt, appeler la fonction quantification pour chaque pixel et retourne une matrice contenant tous les nouveaux pixels
 int ** pretraitement_image ( const char* fichier , int * ptrNBLIG , int * ptrNBCOL, int * ptrB  , int n)  
{ 
  char chaine[256] = {0} ; 
  int ret = snprintf ( chaine , 256 ,"/home/pfr/pfr/image/fich_images/txt/%s" , fichier ) ;
  if ( ret < 0 )
       abort(); 
    FILE* f = openFile( chaine , "r" ); //ouvrir le fichier avec le mode lire
   
    fscanf(f,"%d" , ptrNBLIG);  // nombre de ligne 
    
    fscanf(f,"%d" , ptrNBCOL ); // nombre de colonne

    fscanf(f,"%d", ptrB);   // nombre de composantes
    int ** APQ = malloc( (*ptrNBLIG)*sizeof(int*) );

    if ( APQ == NULL )
    { 
     printf ("erreur ") ; 
     exit(1); 
    }
    int tab[3];
    if ( (*ptrB) !=3 ) // image N/B
    { 
      for ( int a =0 ; a<*ptrNBLIG ; a++ )
     {  
        APQ[a] = malloc( (*ptrNBCOL)*sizeof(int) );
        for (int b=0; b< (*ptrNBCOL); b++ ) 
            {  fscanf(f,"%d", &tab[0]); 
              tab[1] = 0 ;
              tab[2] = 0 ;
               APQ[a][b]= quantification ( tab , *ptrB , n) ; // tab = {pixel , 0 ,0}
               }
               } }
    else  // image en couleur 
      { int taille = (*ptrNBLIG) *(*ptrNBCOL) ;
        int rouge[taille] ; 
        int vert [taille] ; 
        int bleu [taille] ; 
        int r =0 ;
        int v =0 ;
        int bl=0 ;
        for ( int i = 0 ;i<3 ;i++)
        {
          for ( int a =0 ; a<(*ptrNBLIG) ; a++ )
          {  
           APQ[a] = malloc( (*ptrNBCOL)*sizeof(int) );
           for (int b=0; b< (*ptrNBCOL); b++ ) 
           { 
              if (i==0) 
              { 
                  fscanf(f,"%d", &rouge[r]); //tableau qui contient tous les composants rouges
                   r++ ; 
              }
              else if (i==1)
              { 
                  fscanf(f,"%d", &vert[v]); //tableau qui contient tous les composants verts
                   v++ ;
              }
              else 
              { 
                  fscanf(f,"%d", &bleu[bl]); //tableau qui contient tous les composants bleus
                   bl++ ; 
              }
           }
          }
        }
        int t =0 ; 

        for ( int a =0 ; a<(*ptrNBLIG) ; a++ )
            for (int b=0; b< (*ptrNBCOL); b++ ) 
                {
                    tab [0] = rouge[t] ; 
                    tab[1] = vert [t];
                    tab[2] = bleu[t]; 
                    APQ[a][b]= quantification ( tab , *ptrB , n) ; // tab = { composant_rouge, composant_vert, composant_bleu}
                    t++;
                    }
        }
        
        fclose(f) ;
    return ( APQ ) ;  
      }
// Fonction à utiliser dans la fonction indexation_recherche qui effectue le même traitement que la fonction pretraitement_image mais avec un autre chemin de fichier
int ** pretraitement_recherche ( const char* fichier , int * ptrNBLIG , int * ptrNBCOL, int * ptrB  , int n) 
{ 
  char chaine[256] = {0} ; 
  int ret = snprintf ( chaine , 256 ,"/home/pfr/pfr/image/recherche_image/%s" , fichier ) ;
  if ( ret < 0 )
       abort(); 
    FILE* f = openFile( chaine , "r" );  
   
    fscanf(f,"%d" , ptrNBLIG);
    
    fscanf(f,"%d" , ptrNBCOL );

    fscanf(f,"%d", ptrB);  
    int ** APQ = malloc( (*ptrNBLIG)*sizeof(int*) );

    if ( APQ == NULL )
    { 
      printf ("erreur ") ; 
     exit(1); }

    int tab[3];
    if ( (*ptrB) !=3 )
    { 
      for ( int a =0 ; a<*ptrNBLIG ; a++ )
     {  
        APQ[a] = malloc( (*ptrNBCOL)*sizeof(int) );
        for (int b=0; b< (*ptrNBCOL); b++ ) 
            {  fscanf(f,"%d", &tab[0]); 
              tab[1] = 0 ;
              tab[2] = 0 ;
               APQ[a][b]= quantification ( tab , *ptrB , n) ;
               }
               } }
    else 
      {  int taille = (*ptrNBLIG) *(*ptrNBCOL) ;
         int rouge[taille] ;
        int vert [taille] ; 
        int bleu [taille] ; 
        int r =0 ;
        int v =0 ;
        int bl=0 ;
        for ( int i = 0 ;i<3 ;i++)
          {
            for ( int a =0 ; a<(*ptrNBLIG) ; a++ )
         {  
           APQ[a] = malloc( (*ptrNBCOL)*sizeof(int) );
           for (int b=0; b< (*ptrNBCOL); b++ ) 
           { 
              if (i==0){ 
                  fscanf(f,"%d", &rouge[r]); 
                   r++ ; }
              else if (i==1){ 
                  fscanf(f,"%d", &vert[v]); 
                   v++ ; }
              else { 
                  fscanf(f,"%d", &bleu[bl]); 
                   bl++ ; }
           }
         }
        }
        int t =0 ; 
        for ( int a =0 ; a<(*ptrNBLIG) ; a++ )
            for (int b=0; b< (*ptrNBCOL); b++ ) 
                {
                    tab [0] = rouge[t] ; 
                    tab[1] = vert [t];
                    tab[2] = bleu[t]; 
                    APQ[a][b]= quantification ( tab , *ptrB , n) ;
                    t++;
                    }
        }
        
        fclose(f) ;
    return ( APQ ) ;  
      }


// Calculer nombre d'occurrence d'un pixel dans la matrice
int histogramme ( int ** matrice , int pixel , int * ptrNBLIG , int * ptrNBCOL)  
{
     
 int acc = 0  ;
 for (int i = 0 ;i < *ptrNBLIG ; i++ )
       for ( int j =0 ; j < *ptrNBCOL ; j++)
            if (matrice[i][j] ==  pixel)
                 acc++ ;

 return acc ; 
}

//Le mise à jour des fichiers base_descripteur_image.txt et base_image.txt pour chaque nouveau descripteur
void mise_a_jour_base_image (  FILE* LBI , FILE* BDI, const char* f ,int*  descripteur , int n , int* d ) 
         {  int c = pow ( 2 , ((*d)*n) ) + 1 ; 
             fprintf (LBI, "%d  %s \n" , descripteur[0] ,f) ;  
             for  ( int i=0  ; i < c ; i++ )
                fprintf ( BDI , "%d  " , descripteur[i]) ;
             fprintf(BDI , "\n") ; 
         }


//Fonction pour recupere le nombre de bits utilisés pour la quantification
int configuration (FILE* fichier) 
{
  int carac=0;
  fseek(fichier,12,SEEK_SET); //permet de placer le curseur au niveau du caractère 35 (valeur de quantification) 
  fscanf(fichier,"%d",&carac); // lis le caractère au niveau du curseu
  return carac;
}

//Crée un descripteur image .txt a partire d'une matrice 
int* descripteur_image ( int ** matrice , int n , int * ptrNBCOL , int * ptrNBLIG , int * b) 
{
 int c = pow ( 2 , ((*b)*n) )  ; //  c+1 : taille d'un descripteur 
 int* D =  (int*) malloc ((c+1) *sizeof( int));  
 D[0]=0 ;  //Initialiser l'identifiant avec 0
 for (int i = 0 ; i < c ; i++ ){ 
    D[i+1] = histogramme( matrice , i  , ptrNBLIG , ptrNBCOL) ; 
    }
  return D ;

} 



void indexation_image () { 
 int id =0 ; 
 char nomFichier[200] ;
 system("ls /home/pfr/pfr/image/fich_images/txt > /home/pfr/pfr_code/data/listeFichierImage.txt " );  //Créé un fichier avec la liste des textes dans le répertoire 
 FILE * listeFichier = openFile("/home/pfr/pfr_code/data/listeFichierImage.txt","r") ; 
 system("rm /home/pfr/pfr/image/descripteurs_images/*.txt");

 while ( fscanf ( listeFichier ,"%s",nomFichier )==1) // Faire l'indexation de tous les fichiers
 { 

 printf ( "/home/pfr/pfr/image/fich_images/txt/%s\n",nomFichier);
 id++ ;
 FILE* config = openFile("/home/pfr/pfr_code/config.txt" , "r" ); 
 int n = configuration(config); 
 fclose(config);
 int NBLIG ; //nombre des lignes
 int NBCOL ; //nombre des colonnes
 int d ;  //nombre des composantes
 int ** matrice = pretraitement_image( nomFichier , &NBLIG ,&NBCOL , &d , n ) ; 
 int * Descripteur = descripteur_image ( matrice , n , &NBCOL, &NBLIG , &d ) ; 
 FILE* BDI = NULL ;
 FILE * LBI = NULL ;
 if (d==3){ //image en couleur 
 Descripteur[0]= 3000 + id;
 //Ouvrir les fichiers en mode écrire 
 BDI = openFile("/home/pfr/pfr/image/descripteurs_images/base_descripteur_image_couleur.txt" ,"a" ) ; 
 LBI = openFile("/home/pfr/pfr/image/descripteurs_images/base_image_couleur.txt","a" ) ;
 }
 
 else {  //image en N/B
 Descripteur[0]= 4000 +id; 
 BDI = openFile("/home/pfr/pfr/image/descripteurs_images/base_descripteur_image_NB.txt" ,"a" ) ;
 LBI = openFile("/home/pfr/pfr/image/descripteurs_images/base_image_NB.txt","a" ) ;
 }
 mise_a_jour_base_image ( LBI , BDI, nomFichier, Descripteur , n , &d) ;
 for (int i = 0 ; i< NBLIG ;i++ )
    free (matrice[i]) ; 
 free(matrice) ; 
 free (Descripteur ) ; 
 
 fclose( BDI );
 fclose( LBI ) ; 
 }
 fclose(listeFichier) ; 
}


//Fonction à utiliser dans la fonction recherche_image qui effectue le même traitement que la fonction indexation_image 
//mais avec un seul fichier, sans faire le mise à jour des fichiers base_descripteur_image.txt et base_image.txt et retourne un descripteur 
int* indexation_recherche (const char * image )  
{      FILE* config = openFile("/home/pfr/pfr_code/config.txt" , "r" ); 
         int  n = configuration(config); 
         int NBLIG ;
         int NBCOL ;
         int id =  100 ; 
         int d ; 
         int ** matrice = pretraitement_recherche(image , &NBLIG ,&NBCOL , &d  , n ) ; 
         int * Descripteur = descripteur_image  ( matrice , n , &NBCOL, &NBLIG , &d  ) ; 
         if (d==3){ 
         Descripteur[0]= 3000 + id;
          }
         else { 
          Descripteur[0]= 4000 +id; 
          }
         for (int i = 0 ; i< NBLIG ;i++ )
               free (matrice[i]) ; 
         free(matrice) ;  
         return (Descripteur) ;
}



