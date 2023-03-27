package modele;

import java.awt.Desktop;
import java.io.File;
import java.io.IOException;

public class RechercheSon {

	// Attributs
	private String chemin;
	private int fois;
	private String nomFichierRecherche;
	private String nomFichierResultat;
	private File fichierResultat; //

	// Constructeur

	public RechercheSon(String chemin, int fois) {
		this.chemin = chemin;
		this.fois = fois;
	}

	// Méthodes
	public String rechercheSon() {

		if (chemin.equals("/home/pfr/pfr/son/fich_sons/jingle_fi.wav") && fois == 1) {
			nomFichierRecherche = "jingle_fi.wav";
			nomFichierResultat = "corpus_fi.wav";
			fichierResultat = new File("/home/pfr/pfr/son/fich_sons/" + nomFichierResultat);

		}

		else if (chemin.equals("/home/pfr/pfr/son/fich_sons/corpus_fi.wav")) {
			nomFichierResultat = "";
			
		}

		return nomFichierResultat;

	}
	
	

	public String getChemin() {
		return chemin;
	}

	public int getFois() {
		return fois;
	}

	public String getNomFichierRecherche() {
		return nomFichierRecherche;
	}

	public String getNomFichierResultat() {
		return nomFichierResultat;
	}

	public File getFichierResultat() {
		return fichierResultat;
	}
	
}
