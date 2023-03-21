package vueconsole;
import controleur.ControlIndexer;

public class BoundaryIndexer {
	
	private ControlIndexer controlIndexer;
	
	public BoundaryIndexer(ControlIndexer controlIndexer) {
		this.controlIndexer=controlIndexer;
	}
	
	public void indexer() {
		int choix=0;
		System.out.println("Indexation: Veuillez effectuer un choix");
		while ((choix!=1) || (choix!=2) || (choix!=3) || (choix!=4)) {
			System.out.println("1. Indexer tous les fichiers");
			System.out.println("2. Indexer que les textes");
			System.out.println("3. Indexer que les images");
			System.out.println("4. Indexer que les audios");
			choix=Clavier.entrerClavierInt();
			if ((choix!=1) || (choix!=2) || (choix!=3) || (choix!=4)) {
				System.out.println("Votre choix doit être compris entre 1 et 4, faites un choix");
			}
		}
		
		System.out.println("Saisir le chemin du dossier que vous voulez indexer");
		String chemin=Clavier.entrerClavierString();
		switch(choix) {
			case 1:
				controlIndexer.indexationTout(chemin);
				break;
			case 2:
				controlIndexer.indexationTexte(chemin);
				break;
			case 3:
				controlIndexer.indexationImage(chemin);
				break;
			default:
				controlIndexer.indexationSon(chemin);
		}
		System.out.println("Indexation Réussie");
	}
	
}
