package testconsole;

import controleur.ControlRechercherTexte;
import vueconsole.BoundaryRechercher;
import vueconsole.BoundaryRechercherImage;
import vueconsole.BoundaryRechercherSon;
import vueconsole.BoundaryRechercherTexte;

public class TestCasRechercher {
	
	public static void main(String[] args) {
		ControlRechercherTexte controlRechercherTexte = new ControlRechercherTexte();
		
		BoundaryRechercherTexte boundaryRechercherTexte = new BoundaryRechercherTexte(controlRechercherTexte);
		BoundaryRechercherImage boundaryRechercherImage = null;
		BoundaryRechercherSon boundaryRechercherSon= null;
		
		BoundaryRechercher boundaryRechercher = new BoundaryRechercher(boundaryRechercherTexte, boundaryRechercherImage, boundaryRechercherSon);
		
		boundaryRechercher.rechercher();	
	
	}

}
