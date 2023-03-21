package vueconsole;

import controleur.ControlHistorique;
import controleur.ControlRecherche;

public class BoundaryUtilisateur {
	private ControlRecherche conrolRecherche = new ControlRecherche (); 
	private ControlHistorique controlHistorique = new ControlHistorique (); 
	private BoundaryRecherche boundaryRecherche ;
	private BoundaryHistorique boundaryHistorique ; 
	
	public BoundaryUtilisateur () {
		boundaryHistorique = new BoundaryHistorique(controlHistorique);
		
		boundaryRecherche = new BoundaryRecherche(conrolRecherche) ; 
	}
	
	public int utilisateur () {
		 int exit = 0 ;
				 while ( exit == 0 ) {
					 int choix = 33 ; 
					 while (!(choix == 1 || choix  == 2 || choix == 0 )) {
						 System.out.println("       *** Mode utilisateur *** ");
						 System.out.println ("1: Effectuer une recherche");
						 System.out.println ("2: Visualiser historique");
						 System.out.println ("0: Retouner menu principal ") ; 
						 choix = Clavier.entrerClavierInt() ; 
						 if (!(choix == 1 || choix  == 2 || choix == 0 )) {
							System.out.println("Veuillez entrer 0,1 ou 2 ");
						 }
					 }
					 switch (choix) {
					 case 1 : 
						 exit = boundaryRecherche.recherche(); 
						 break ; 
					 case 2 : 
						 exit = boundaryHistorique.historique();
						 break ; 
					 default : 
						 return 0 ; 
					 }
				 }
				 return 0 ; 
				 
	}


}