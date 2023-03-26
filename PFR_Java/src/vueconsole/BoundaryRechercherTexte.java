package vueconsole;

import java.util.ArrayList;
import java.util.List;

import controleur.ControlRechercherTexte;
import modele.Fichier;
import modele.TypeRechercheTexte;

public class BoundaryRechercherTexte {
	ControlRechercherTexte controlRechercher;

	public BoundaryRechercherTexte(ControlRechercherTexte controlRechercher) {
		super();
		this.controlRechercher = controlRechercher;
	}
	
	public void rechercherTexte() {
		
		List<String> resultats = new ArrayList<>();
		
		int choixTypeTexte;
		do {
			System.out.println("Quel type de recherche de texte souhaitez-vous effectuer ?");
			System.out.println("Tapez '1' pour une recherche par mot clef");
			System.out.println("Tapez '2' pour une recherche via un chemin");
			
			
			choixTypeTexte = Clavier.entrerClavierInt();
			
			if(!(choixTypeTexte == 1 || choixTypeTexte == 2)) {
				System.out.println("Veuillez entrer 1, 2 ou 3");
			}
		}while (!(choixTypeTexte == 1 || choixTypeTexte == 2));

		switch(choixTypeTexte) {
	
		case 1:
			int choixTypeMotClef;
			do {
				System.out.println("Voulez-vous faire une recherche par mot clefs simple ou complexe ?");
				System.out.println("Tapez '1' pour une recherche par mot clef simple");
				System.out.println("Tapez '2' pour une recherche par mot clef complexe");
				
				choixTypeMotClef = Clavier.entrerClavierInt();
				
				if(!(choixTypeMotClef == 1 || choixTypeMotClef == 2)) {
					System.out.println("Veuillez entrer 1 ou 2");
				}
			}while (!(choixTypeMotClef == 1 || choixTypeMotClef == 2));

			switch(choixTypeMotClef) {
		
			case 1:
				System.out.println("Entrez le mot clef");
				String motClef = Clavier.entrerClavierString();
				resultats = controlRechercher.rechercherTexteMotClef(TypeRechercheTexte.SIMPLE, motClef);
				break;
			
			case 2:
				System.out.println("Entrez les mot clefs, en les séparant par une virgules ','");
				String motsClefs = Clavier.entrerClavierString();
				resultats = controlRechercher.rechercherTexteMotClef(TypeRechercheTexte.COMPLEXE, motsClefs);
				break;
			}
			break;
			
		case 2:
			System.out.println("Entrez le chemin du fichier à comparer");
			String chemin = Clavier.entrerClavierString();
			resultats = controlRechercher.rechercherTexteChemin(chemin);
			break;
		}
		
		System.out.println("Résultats de la recherche :");
		for(int i = 0; i < resultats.size(); i++) {
			System.out.println((i+1) + ": " + resultats.get(i));
		}
		
	
		int choixFichier;
		do {
			System.out.println("Entrez le numéro du fichier que vous voulez ouvrir?");
			
			choixFichier = Clavier.entrerClavierInt();
			
			if((choixFichier < 1 || choixFichier > resultats.size())) {
				System.out.println("Mauvais numéro");
			}
		}while ((choixFichier < 1 || choixFichier > resultats.size()));
		
		Fichier.ouvrirFichierTexte(resultats.get(choixFichier-1));
		Fichier.ouvrirFichierTexte(resultats.get(choixFichier-1));
	}	
}
