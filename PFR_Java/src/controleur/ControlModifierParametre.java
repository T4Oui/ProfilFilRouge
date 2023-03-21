package controleur;

import modele.Parametre;

public class ControlModifierParametre {
         Parametre parametre  ; 
         ControlIndexer controlIndexer ; 
         
         public ControlModifierParametre ( ) {
        	 parametre = Parametre.getIntance ();
        	 
         }
         /*
         public ControlModifierParametre (ControlIndexer controlIndexer ) {
        	 parametre = Parametre.getIntance ();
        	 this.controlIndexer = controlIndexer ; 
         }*/
         
         
	public String visualiserParametre() {
		String s = parametre.toString();
		return s ; 
	}
	
	public void modifierNbrOcc(int nbrAcc) {
		parametre.setNbrOcc ( nbrAcc);
		//controlIndexer.indexerFichierText (); 
	}
	public void modifierNbrBit(int nbrBit) {
		parametre.setNbrBit(nbrBit);
		//controlIndexer.indexerFichierImage ();
	}
	public void modifierNbrEch ( int nbrEch) {
		parametre.setNbrEch ( nbrEch) ; 
		//controlIndexer.indexerFichierSon (); 
	}
	public void modifierIntervalle (int intervalle) {
		parametre.setIntervalle ( intervalle) ; 
		//controlIndexer.indexerFichierSon (); 
	}
	public void modifierModeRecherche (int mode) {
		parametre.setModeRecherche (mode); 
	}
}