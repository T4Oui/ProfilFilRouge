package test;

import controleur.ControlModifierParametre;
import controleur.ControlSIdentifier;
import vueconsole.BoundaryModifierParametre;
import vueconsole.BoundaryMoteurDeRecherche;
import vueconsole.BoundarySIdentifier;

public class testInterface {

	public static void main(String[] args) {
		BoundaryMoteurDeRecherche boundaryMoteurDeRecherche = new BoundaryMoteurDeRecherche() ; 
		System.out.println("Debut ");
		boundaryMoteurDeRecherche.moteurDeRecherche();
		//boundarySIdentifier.sIdentifier();
		//boundaryModifierParametre.modifierParametre();	
		System.out.println("Fin ") ; 
		 
		

	}
}