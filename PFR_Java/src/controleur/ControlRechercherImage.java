package controleur;

import java.util.List;

import modele.FileHandler;
import modele.Resultat;
import modele.TypeRecherche;

public class ControlRechercherImage {
	private String nom="test";
	private Resultat resultat;
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
	
	public String rechercheParCouleur(int couleur)
	{
		nom=couleur+"TEST COULEUR";
		
		return this.nom;
	}

}
