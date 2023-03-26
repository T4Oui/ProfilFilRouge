package modele;

public class ThreadIndexation extends Thread {
	private boolean condition = true;
	//LibraryTexteMoteur libraryTexteMoteur = LibraryTexteMoteur.INSTANCE;
	
	public ThreadIndexation() {}
	
	public void arret() {
		condition = false;
		System.out.println("Thread fermé");
	}
	
	public void run() {
		System.out.println("Thread ouvert");
		do {
			try {
				Thread.sleep(5000);
			} catch(InterruptedException e) {
				e.printStackTrace();
			}
			
			//libraryTexteMoteur.indexation_texte();	
			
		}while(condition);
	}
}
