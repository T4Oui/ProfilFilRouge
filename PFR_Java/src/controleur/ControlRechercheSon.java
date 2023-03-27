package controleur;

import java.io.File;
import java.io.FileNotFoundException;

import modele.RechercheSon;

public class ControlRechercheSon {

	// Attributs
	private RechercheSon uneRechercheSon;

	// Constructeur
	public ControlRechercheSon(RechercheSon uneRechercheSon) {
		this.uneRechercheSon = uneRechercheSon;
	}

	// Méthodes
	public String rechercheSon(String chemin, int fois) throws FileNotFoundException {
		File fichierRecherche = new File(chemin);
		if (fichierRecherche.exists() && !fichierRecherche.isDirectory()) {
			uneRechercheSon = new RechercheSon(chemin, fois);
			return uneRechercheSon.rechercheSon();
		}

		else {
			throw new FileNotFoundException("Le fichier recherché n'existe pas");
		}
		
	}
	
	public RechercheSon getUneRechercheSon() {
		return uneRechercheSon;
	}
	
	public File getFichierResultat() {
		return uneRechercheSon.getFichierResultat();
	}

}
