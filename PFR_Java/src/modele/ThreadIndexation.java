package modele;

import java.io.File;
import java.io.IOException;
import java.util.Map;

public class ThreadIndexation extends Thread {
	private boolean condition = true;
	private int nbFichier=0;
	private IdentiteFichier liste =IdentiteFichier.getInstance();
	//LibraryTexteMoteur libraryTexteMoteur = LibraryTexteMoteur.INSTANCE;
	
	public ThreadIndexation() {}
	
	public void arret() {
		condition = false;
		System.out.println("Thread fermé");
	}
	
	public void run() {
		System.out.println("Thread ouvert");
		try {
			nbFichier=CountFiles.nbFichier(getName());
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		do {
			try {
				Thread.sleep(5000);
			} catch(InterruptedException e) {
				e.printStackTrace();
			}
			
			try {
				int test=CountFiles.nbFichier(getName());
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			if (test!=nbFichier)
			{
				//recup la liste des nouveaux fichiers
				File directory = new File("chemin vers le dossier qui contient tout les fichiers");
				File[] liste = directory.listFiles();
				
				for(int i=nbFichier;i<test+1;i++) {
					//recup un des fichiers
					String fichierActuel =liste[i].getName();
					String extesion = FilenameUtils.getExtension(fichierActuel);
					//if (extension du fichier= bmp, jpg,txt){
					File source = new File("chemin vers le dossier qui contient tout les fichiers"+//nomfichier a deplacer);
					File dest = new File ("/home/pfr/pfr/image/fich_images");
					try {
						//déplace d'un repertoire à un autre
						boolean ok = source.renameTo(new File(dest, source.getName()));
						if(!ok) {
							//gestion erreurs
						}
						ControlRechercherImage.indexerUnFichier("nom du fichier");
					} catch(IOException e) {
						e.printStackTrace();
					}
					
					
					
					//if (extension du fichier= xml){
					File source = new File("chemin vers le dossier qui contient tout les fichiers"+//nomfichier a deplacer);
					File dest = new File ("/home/pfr/pfr/texte/fich_textes");
					try {
						//déplace d'un repertoire à un autre
						boolean ok = source.renameTo(new File(dest, source.getName()));
						if(!ok) {
							//gestion erreurs
						}
						ControlRechercherTexte.indexerUnFichier("nom du fichier");
					} catch(IOException e) {
						e.printStackTrace();
					}
				}
			}
			
		
		//recup liste fichier ls et conatains avec la map
			
			
			//libraryTexteMoteur.indexation_texte();	
			
		}while(condition);
		//libraryTexteMoteur.indexation_texte();	

		
	}
}
