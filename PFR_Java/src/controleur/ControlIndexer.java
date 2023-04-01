package controleur;

import libraryJNA.LibraryImageMoteur;
import libraryJNA.LibrarySonMoteur;
import libraryJNA.LibraryTexteMoteur;
import modele.IdentiteFichier;

public class ControlIndexer {

	public void indexationTout(String chemin) {
		indexationTexte(chemin);
		indexationImage(chemin);
		indexationSon(chemin);
	}

	public void indexationTexte(String chemin) {
		// appel indexationTexte(chemin) de C
		LibraryTexteMoteur libraryTexteMoteur = LibraryTexteMoteur.INSTANCE;
		libraryTexteMoteur.indexation_texte();
	}

	public void indexationImage(String chemin) {
		// appel indexationImage(chemin) de C
		LibraryImageMoteur libraryImageMoteur = LibraryImageMoteur.INSTANCE;
		libraryImageMoteur.indexation_image();
		IdentiteFichier ident = IdentiteFichier.getInstance();
		ident.ajouterIdentifiant();
	}

	public void indexationSon(String chemin) {
		// appel indexationSon(chemin) de C
		LibrarySonMoteur librarySonMoteur = LibrarySonMoteur.INSTANCE;
		librarySonMoteur.indexation_son();
	}

}