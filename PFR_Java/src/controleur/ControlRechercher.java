package controleur;

import libraryJNA.LibraryTexteMoteur;
import modele.TypeRechercheTexte;

public class ControlRechercher {
	LibraryTexteMoteur libraryTexteMoteur = LibraryTexteMoteur.INSTANCE;
	
	public String rechercheTexteMotClef(TypeRechercheTexte typeRechercheTexte, String motClef) {
		String fichier = null;
		switch(typeRechercheTexte) {				
			case SIMPLE:
				
				//LibraryTexteMoteur libraryTexteMoteur = LibraryTexteMoteur.INSTANCE;
				//libraryTexteMoteur.indexation_texte();
								
				
				libraryTexteMoteur.rech_MC(motClef);
				
				 // A faire
				//fichier = libraryTexteMoteur.rech_MC(motClef); // recupérer le retour de la recherche
				
				
				break;
			
			case COMPLEXE:
				
				
				fichier = ""; // recupérer le retour de la recherche
				break;
		}
		
		return fichier;
		
	}

	public String rechercheTexteChemin(String chemin) {
		
		libraryTexteMoteur.recherche_comparaison_texte(chemin, 35);
		
		return null;
	}

	

}
