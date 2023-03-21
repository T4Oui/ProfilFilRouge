package vueconsole;

public class BoundaryMoteurDeRecherche {

	private BoundaryAdmin boundaryAdmin = new BoundaryAdmin();
	private BoundaryUtilisateur boundaryUtilisateur = new BoundaryUtilisateur();

	public void BoundarymoteurDeRecherche() {
		
	}

	public void moteurDeRecherche() {
	
		int exit  = 0;
		while ( exit  == 0) {
			int choix = 33;
			System.out.println("       ** Menu Principal ** ");
			while (!(choix == 1 || choix == 2 || choix == 0 )) {
				System.out.println("1: mode Utilisateur ");
				System.out.println("2: mode Administrateur ");
				System.out.println("0: exit");
				choix = Clavier.entrerClavierInt();
				if (!(choix == 1 || choix == 2|| choix == 0 )) {
					System.out.println(" Veuillez entre 1 ou 2");
				}
			}
			if (choix == 2) {
				exit  = boundaryAdmin.admin();
			} else if (choix == 1){
				exit  = boundaryUtilisateur.utilisateur();
			}
			else {
				break ; 
			}
		}
	}

}