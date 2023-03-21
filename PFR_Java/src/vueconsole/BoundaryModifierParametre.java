package vueconsole;

import controleur.ControlModifierParametre;

public class BoundaryModifierParametre {
   
	private ControlModifierParametre controlModifierParametre ;
	
	public BoundaryModifierParametre ( ControlModifierParametre controlModifierParametre) {
		this.controlModifierParametre = controlModifierParametre ; 
	}
	public void visualiserParametre() {
		String s = controlModifierParametre.visualiserParametre();
		System.out.println(s);
	}
	
	public int  modifierParametre () {
		int exit = 1;
		while ( exit ==1 ) {

			visualiserParametre();
			System.out.println (" Que voulez vous modifier ? "); 
			int choix = 33; 
			while ( !(choix ==1 || choix == 2 || choix == 3 || choix == 4 || choix == 5 || choix == 0)) {
				System.out.println ( "1: Modifier  nombre d'occurence d'un mot dans un fichier texte");
    			System.out.println ( "2: Modifier nombre de bit de quantification des fichiers image ");
    			System.out.println ( "3: Modifier nombre d'echantillon des fichiers son ");
    			System.out.println ( "4: Modifier taille de l'intervalle d'un fichier son");
    			System.out.println ( "5: Modifier mode recherche");
    			System.out.println ( "0: Retourner au menu precedent");
    			choix = Clavier.entrerClavierInt() ;
    			if ( !(choix ==1 || choix == 2 || choix == 3 || choix == 4 || choix == 5 || choix == 0)) {
    				System.out.println("Veuillez entre 1,2,3,4 ou 5 "); 
    			}
			}
			switch ( choix ) {
			case 1 :
				System.out.println("Veuillez rentrer la valeur à mettre en place ");
				int nbrAcc = Clavier.entrerClavierInt();
				controlModifierParametre.modifierNbrOcc(nbrAcc);
				break ;
			case 2 : 
				System.out.println("Veuillez rentrer la valeur à mettre en place ");
				int nbrBit = Clavier.entrerClavierInt();
				controlModifierParametre.modifierNbrBit(nbrBit);
				break ;
			case 3 : 
				System.out.println("Veuillez rentrer la valeur à mettre en place ") ;
				int nbrEch = Clavier.entrerClavierInt();
				controlModifierParametre.modifierNbrEch(nbrEch);
				break ;
			case 4 :
				System.out.println("Veuillez rentrer la valeur à mettre en place ") ;
				int intervalle  = Clavier.entrerClavierInt();
				controlModifierParametre.modifierIntervalle(intervalle);
				break ;
			case 5 : 
				int modeRecherche =0 ; 
				while ( !(modeRecherche ==1 || modeRecherche == 2|| modeRecherche == 3 )) {
				  System.out.println ("1 Recherche ouvert");
				  System.out.println ("2 Recherche ferme ") ; 
				  System.out.println ("3 Recherche multi_moteur") ; 
				  modeRecherche  =  Clavier.entrerClavierInt();
				  if (!(modeRecherche ==1 || modeRecherche == 2 || modeRecherche == 3 )) {
					System.out.println("Veuillez entre 1,2 ou 3 "); 
			    	}
				}
				controlModifierParametre.modifierModeRecherche (modeRecherche) ;
				break ; 
			default : 
				exit = 0;	
			}
		}
		
		return exit ; 
	}
}