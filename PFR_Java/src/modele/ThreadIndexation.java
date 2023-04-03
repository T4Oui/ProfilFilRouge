package modele;

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
			if (test==nbFichier)
			{
				
			}
			
		
		//recup liste fichier ls et conatains avec la map
			
			
			//libraryTexteMoteur.indexation_texte();	
			
		}while(condition);
		//libraryTexteMoteur.indexation_texte();	

		
	}
}
