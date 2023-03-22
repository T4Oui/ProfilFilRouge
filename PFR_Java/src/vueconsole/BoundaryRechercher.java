package vueconsole;

public class BoundaryRechercher {
	BoundaryRechercherTexte boundaryRechercherTexte;
	BoundaryRechercherImage boundaryRechercherImage;
	BoundaryRechercherSon boundaryRechercherSon;
	
	public BoundaryRechercher(BoundaryRechercherTexte boundaryRechercherTexte,
			BoundaryRechercherImage boundaryRechercherImage, BoundaryRechercherSon boundaryRechercherSon) {
		super();
		this.boundaryRechercherTexte = boundaryRechercherTexte;
		this.boundaryRechercherImage = boundaryRechercherImage;
		this.boundaryRechercherSon = boundaryRechercherSon;
	}
	
	public void rechercher() {
		
		String fichier = "";		
		int choix;
		do {
			System.out.println("Quel recherche souhaitez-vous effectuer ?");
			System.out.println("Tapez '1' pour rechercher un texte");
			System.out.println("Tapez '2' pour rechercher une image");
			System.out.println("Tapez '3' pour rechercher un son");
			
			choix = Clavier.entrerClavierInt();
			
			if(!(choix == 1 || choix == 2 || choix == 3)) {
				System.out.println("Veuillez entrer 1, 2 ou 3");
			}
		}while (!(choix == 1 || choix == 2 || choix == 3));

		switch(choix) {
		case 1:
			boundaryRechercherTexte.rechercherTexte();
			break;
		case 2:
			boundaryRechercherImage.rechercherImage();
			break;
		case 3:
			boundaryRechercherSon.rechercherSon();
			break;
		}
		
	}
	
	
	
	
	
	
	
}
