package vueconsole;

import java.awt.Desktop;
import java.io.File;
import java.io.IOException;
import java.util.InputMismatchException;

import controleur.ControlRechercheSon;

public class BoundaryRechercheSon {
	// attributs

	private ControlRechercheSon controlRechercheSon;

	// Constructeur
	public BoundaryRechercheSon(ControlRechercheSon controlRechercheSon) {
		this.controlRechercheSon = controlRechercheSon;
	}

	// Méthodes
	public void rechercheSon() throws IOException {

		String chemin;
		int fois;

		System.out.println("\nEntrez le chemin de l'extrait souhaité : ");
		chemin = Clavier.entrerClavierString();

		try {
			System.out.println("\nCombien de fois voulez vous qu'il soit présent : ");
			fois = Clavier.entrerClavierInt();
		}

		catch (InputMismatchException e) {
			throw new InputMismatchException("Saisie invalide. Veuillez saisir un entier ");
		}
		

		String resultatRecherche = controlRechercheSon.rechercheSon(chemin, fois);

		if (resultatRecherche == "corpus_fi.wav") {
			System.out.println("Le fichier le plus proche est : \n" + resultatRecherche);

			File file = controlRechercheSon.getFichierResultat();

			Desktop desktop = Desktop.getDesktop();

			if (desktop.isSupported(Desktop.Action.OPEN)) {
				desktop.open(file);
			}

			else {
				System.out.println("Ouverture non supportée");
			}
		}

		if (resultatRecherche == "") {
			System.out.println("Aucun fichier ne contient corpus_fi.wav ");
		}
		
		
		
		
		
		
		
		

		/*
		 * Desktop desktop = Desktop.getDesktop();
		 * 
		 * if (desktop.isSupported(Desktop.Action.OPEN)) { desktop.open(file); }
		 * 
		 * 
		 * 
		 * else { System.out.println("Open is not supported"); }
		 * 
		 * catch (IOException exp) { exp.printStackTrace(); }
		 * 
		 * System.out.println("Le fichier le plus proche est : \n" +
		 * nomFichierResultat);
		 * 
		 * System.out.println("Aucun fichier correspondant à " + chemin + " trouvé");
		 * 
		 * System.out.println("Aucun fichier ne contient " + nomFichierRecherche);
		 * 
		 * System.out.println("Aucun fichier correspondant");
		 */

	}

}
