package controleur;

import java.awt.desktop.OpenFilesHandler;

import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import modele.BDHistorique;
import modele.Fichier;
import modele.FileHandler;
import modele.IdentiteFichier;
import modele.JPGFileReader;
import modele.Recherche;
import modele.Resultat;
import modele.TypeRecherche;
import modele.TypeRechercheCouleur;
import libraryJNA.*;
public class ControlRechercherImage {
	private String nom="test";
	private Resultat resultat;
	public ControlRechercherImage() {
		// TODO Auto-generated constructor stub
	}
	
	public Resultat rechercheImageNB(float pourcentageMini, String nom)
	{
		//nom=rechercheImageNB(pourcentage,nom) du C
		Recherche recherche = new Recherche(nom, pourcentageMini);
		IdentiteFichier identite=IdentiteFichier.getInstance();
		identite.ajouterIdentifiant();
		String identifiant=identite.getKeyByValue(nom);
		LibraryImageMoteur jna=LibraryImageMoteur.INSTANCE;
		int iden=Integer.parseInt(identifiant);
		jna.recherchenoiretblanc(iden,pourcentageMini,"?");
		 
		 List<String> res = FileHandler.readFileToList("/home/pfr/pfr_code/data/resultat_recherche.txt");
		 this.resultat= new Resultat(TypeRechercheCouleur.NOIRETBLANC, res, recherche);
		 
		BDHistorique bdHistorique = BDHistorique.getInstance();
		bdHistorique.ajouterHistorique(recherche,resultat);
		//System.out.println(bdHistorique.visualiserHistorique());
		 
		 return resultat;
	}
	
	public Resultat rechercheImageCouleur(float pourcentageMini, String nom)
	{
		this.nom="Couleur"+String.valueOf(pourcentageMini)+nom;
		Recherche recherche = new Recherche(nom, pourcentageMini);
		IdentiteFichier identite=IdentiteFichier.getInstance();
		identite.ajouterIdentifiant();
		String identifiant=identite.getKeyByValue(nom);
		LibraryImageMoteur jna=LibraryImageMoteur.INSTANCE;
		int iden=Integer.parseInt(identifiant);
	    jna.recherchecouleur(iden,pourcentageMini,"?");
		List<String> res = FileHandler.readFileToList("/home/pfr/pfr_code/data/resultat_recherche.txt");
		this.resultat= new Resultat(TypeRechercheCouleur.COULEUR, res, recherche);
		
		BDHistorique bdHistorique = BDHistorique.getInstance();
		bdHistorique.ajouterHistorique(recherche,resultat);
		//System.out.println(bdHistorique.visualiserHistorique());
		
		return resultat;
	}
	
	public Resultat rechercheParCouleur(int couleur)
	{
		nom=couleur+"TEST COULEUR";
		switch (couleur)
		{
			case 1 :
			     Recherche recherche= new Recherche("BLEU", 0);
				 List<String> res = new ArrayList<>();
				 res.add("34.jpg 9,000%");
				 res.add("35.jpg 3,000%");
				 res.add("28.jpg 1,000%");
			        try {
			            BufferedImage image = JPGFileReader.readJPGFile("/Users/valentin/Documents/Capture d’écran 2023-03-18 à 09.18.28.png");
			            // process the image here
			        } catch (IOException e) {
			            System.out.println("Error reading image file: " + e.getMessage());
			        }
			       return (new Resultat(TypeRechercheCouleur.RGB, res, recherche));
			case 2:
				
			       
			default :
				return null;
			
				
				 		
		}
		
			
		
	}

}
