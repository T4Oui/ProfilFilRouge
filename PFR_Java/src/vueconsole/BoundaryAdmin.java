package vueconsole;

import controleur.ControlIndexer;
import controleur.ControlModifierParametre;
import controleur.ControlSIdentifier;
import controleur.ControlVisualiserDescripteur;

public class BoundaryAdmin {
	private BoundaryIndexer boundaryIndexer;
	private BoundaryModifierParametre boundaryModifierParametre;
	private BoundarySIdentifier boundarySIdentifier;
	private BoundaryVisualiserDescripteur boundaryVisualiserDescripteur;
	private BoundaryUtilisateur boundaryUtilisateur;
	private ControlIndexer controlIndexer = new ControlIndexer();
	private ControlModifierParametre controlModifierParametre = new ControlModifierParametre();
	private ControlSIdentifier controlSIDentifier = new ControlSIdentifier();
	private ControlVisualiserDescripteur controlVisualiserDescripteur = new ControlVisualiserDescripteur();

	public BoundaryAdmin() {

		boundaryIndexer = new BoundaryIndexer(controlIndexer);
		boundaryModifierParametre = new BoundaryModifierParametre(controlModifierParametre);
		boundarySIdentifier = new BoundarySIdentifier(controlSIDentifier);
		boundaryVisualiserDescripteur = new BoundaryVisualiserDescripteur(controlVisualiserDescripteur);
		boundaryUtilisateur = new BoundaryUtilisateur();

	}

	public int admin() {
		int mdpOK = boundarySIdentifier.sIdentifier();
		if (mdpOK == 0) {
			return 0;
		} else {
			int exit = 0; 
			while ( exit == 0 ) {
				int choix = 5;
			     while (!(choix == 1 || choix == 2 || choix == 3 || choix == 4 || choix == 0)) {
			    System.out.println("      ** Mode Administrateur **");
				System.out.println("1: modifier les configurations");
				System.out.println("2: visualiser le contenu des descripteurs");
				System.out.println("3: effectuer une recherche");
				System.out.println("4: faire l'indexation");
				System.out.println("0: revenir au menu principal");
				choix = Clavier.entrerClavierInt();
				if (!(choix == 1 || choix == 2 || choix == 3 || choix == 4 || choix == 0)) {
					System.out.println("Veuillez entre 1 ,2 ,3 ,4 ou 0");
				}
				
			}
			switch (choix) {
			case 1 : 
				exit = boundaryModifierParametre.modifierParametre();
				break ; 
			case 2 : 
				exit = boundaryVisualiserDescripteur.visualiserDescripteur();
				break ; 
			case 3 : 
				exit = boundaryUtilisateur.utilisateur() ; 
				break ; 
			case 4 : 
				exit = boundaryIndexer.indexer();
				break ; 
			default : 
				return ( 0 ) ;
			}

		}
	}
	return (0) ; 	
	}
		}