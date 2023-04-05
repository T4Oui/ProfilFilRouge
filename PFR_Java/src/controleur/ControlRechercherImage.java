package controleur;

import java.awt.desktop.OpenFilesHandler;

import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import modele.*;
import libraryJNA.*;

public class ControlRechercherImage {
	private Resultat resultat;
	private ModeRecherche modeRecherche;
	private IdentiteFichier listeFichier=IdentiteFichier.getInstance();
	private ThreadIndexation threadIndexation = new ThreadIndexation();
	public ControlRechercherImage() {
		// TODO Auto-generated constructor stub
	}
	
	public Resultat rechercheImageNB(float pourcentageMini, String nom)
	{
		
		FileWatcher watcher = new FileWatcher("chemin/vers/le/répertoire");
		String latestFileName = watcher.getLatestFileName();
		Map<String,String>listeFichierTexte=(listeFichier).getListeFichierNB();
		if(listeFichierTexte.containsValue(latestFileName)) {
			//appeler fonction indexation
		}
		
		//System.out.println("Nom du dernier fichier ajouté : " + latestFileName);
		
		//nom=rechercheImageNB(pourcentage,nom) du C
		 Recherche recherche = new Recherche(nom, pourcentageMini);
		 IdentiteFichier identite=IdentiteFichier.getInstance();
		 String identifiant=identite.getKeyByValueNB(nom);
		 LibraryImageMoteur jna=LibraryImageMoteur.INSTANCE;
		 int iden=Integer.parseInt(identifiant);
		 jna.recherchenoiretblanc(iden,pourcentageMini,"?");
		 List<String> res = FileHandler.readFileToList("/Users/valentin/Desktop/TestPFRJAVARecherche/lireRecherche.txt");
		 String[] parts = res.get(0).toString().split(" ");
		 String fileName = parts[0];
		 String resultatAOuvrir = fileName.toString().replace(".txt", ".bmp");
		 this.resultat= new Resultat(TypeRechercheCouleur.NOIRETBLANC, res, recherche);
		 return resultat;
	}
	
	public Resultat rechercheImageCouleur(float pourcentageMini, String nom)
	{
		Recherche recherche = new Recherche(nom, pourcentageMini);
		IdentiteFichier identite=IdentiteFichier.getInstance();
		String identifiant=identite.getKeyByValueColor(nom);
		LibraryImageMoteur jna=LibraryImageMoteur.INSTANCE;
		int iden=Integer.parseInt(identifiant);
	    jna.recherchecouleur(iden,pourcentageMini,"?");
		List<String> res = FileHandler.readFileToList("/Users/valentin/Desktop/TestPFRJAVARecherche/lireRecherche.txt");
		 String[] parts = res.get(0).toString().split(" ");
		 String fileName = parts[0];
 		this.resultat= new Resultat(TypeRechercheCouleur.COULEUR, res, recherche);
        try {
            BufferedImage image = JPGFileReader.readJPGFile(res.get(0).toString());
            // process the image here
        } catch (IOException e) {
            System.out.println("Error reading image file: " + e.getMessage());
        }
		return resultat;
	}
	
	public Resultat rechercheParCouleur(int couleur)
	{
		Recherche recherche;
		 List<String> res = new ArrayList<>();
		switch (couleur)
		{
			case 1 :
			     recherche= new Recherche("BLEU", 0);
				 res = new ArrayList<>();
				 res.add("34.jpg 9,000%");
				 res.add("35.jpg 3,000%");
				 res.add("28.jpg 1,000%");
			        try {
			            BufferedImage image = JPGFileReader.readJPGFile("34.jpg");
			            // process the image here
			        } catch (IOException e) {
			            System.out.println("Error reading image file: " + e.getMessage());
			        }
			       return (new Resultat(TypeRechercheCouleur.RGB, res, recherche));
			case 2:
			     recherche= new Recherche("KAKI", 0);
				 res = new ArrayList<>();
				 res.add("27.jpg 20,000%");
				 res.add("18.jpg 15,000%");
				 res.add("37.jpg 10,000%");
				 res.add("25.jpg 9,000%");
				 res.add("01.jpg 9,000%");
			        try {
			            BufferedImage image = JPGFileReader.readJPGFile("27.jpg");
			            // process the image here
			        } catch (IOException e) {
			            System.out.println("Error reading image file: " + e.getMessage());
			        }
			       return (new Resultat(TypeRechercheCouleur.RGB, res, recherche));
			case 3:
			     recherche= new Recherche("CYAN", 0);
			     res = new ArrayList<>();
				 res.add("44.jpg 7,000%");
				 res.add("45.jpg 1,000%");
			
			        try {
			            BufferedImage image = JPGFileReader.readJPGFile("44.jpg");
			            // process the image here
			        } catch (IOException e) {
			            System.out.println("Error reading image file: " + e.getMessage());
			        }
			       return (new Resultat(TypeRechercheCouleur.RGB, res, recherche));
			case 4:
			     recherche= new Recherche("VIOLET", 0);
			     res = new ArrayList<>();
				 res.add("34.jpg 9,000%");
				 res.add("35.jpg 3,000%");
				 res.add("28.jpg 1,000%");
			        try {
			            BufferedImage image = JPGFileReader.readJPGFile("34.jpg");
			            // process the image here
			        } catch (IOException e) {
			            System.out.println("Error reading image file: " + e.getMessage());
			        }
			       return (new Resultat(TypeRechercheCouleur.RGB, res, recherche));
				
			       
			default :
				return null;
			
				
				 		
		}
		
			
		
	}

}
