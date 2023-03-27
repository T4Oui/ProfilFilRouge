package controleur;

import java.awt.desktop.OpenFilesHandler;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import modele.Fichier;
import modele.FileHandler;
import modele.JPGFileReader;
import modele.Recherche;
import modele.Resultat;
import modele.TypeRecherche;
import modele.TypeRechercheCouleur;

public class ControlRechercherImage {
	private String nom="test";
	private Resultat resultat;
	private Recherche recherche;
	public ControlRechercherImage() {
		// TODO Auto-generated constructor stub
	}
	
	public Resultat rechercheImageNB(float pourcentageMini, String nom)
	{
		//nom=rechercheImageNB(pourcentage,nom) du C
		 List<String> res = FileHandler.readFileToList("/Users/valentin/Desktop/TestPFRJAVARecherche/lireRecherche.txt");
		 this.resultat= new Resultat(TypeRecherche.IMAGE,res );
		 return resultat;
	}
	
	public Resultat rechercheImageCouleur(float pourcentageMini, String nom)
	{
		//nom=rechercheImageCouleur(pourcentage,nom) du C
		this.nom="Couleur"+String.valueOf(pourcentageMini)+nom;

		return null;
	}
	
	public Resultat rechercheParCouleur(int couleur)
	{
		nom=couleur+"TEST COULEUR";
		switch (couleur)
		{
			case 1 :
				 this.recherche.setNom("Bleu");
				 List<String> res = new ArrayList<>();
				 res.add("34.jpg 9,000%");
				 res.add("35.jpg 3,000%");
				 res.add("28.jpg 1,000%");
				 System.out.println("dfdf");
			        try {
			            BufferedImage image = JPGFileReader.readJPGFile("/Users/valentin/Documents/Capture d’écran 2023-03-18 à 09.18.28.png");
			            // process the image here
			        } catch (IOException e) {
			            System.out.println("Error reading image file: " + e.getMessage());
			        }
			       return (new Resultat(TypeRechercheCouleur.RGB, res));
				 
				 



		
		}
		return resultat;
			
		
	}

}
