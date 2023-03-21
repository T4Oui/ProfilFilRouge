package vueconsole;

import controleur.ControlSIdentifier;

public class BoundarySIdentifier {
      ControlSIdentifier  controlSIdentifier  ;
      
      public BoundarySIdentifier( ControlSIdentifier  controlSIdentifier ) {
    	  this.controlSIdentifier = controlSIdentifier ;
      }
      
      public int  sIdentifier () {
    	  boolean b = false ;
    	  while (!b) {
    		  System.out.println ("Mot de passe?"); 
    		  String motDePasse = Clavier.entrerClavierString();
    		  b= controlSIdentifier.verifierMotDePasse ( motDePasse); 
    		  if ( ! b) {
        		  System.out.println ("Mot de passe erroné ");  
        		  System.out.println (" (Taper 0: revenir au menu principal) ");
    		  }
    		  if ( b == false && motDePasse.equals("0")) {
    			  return (0); 
    		  }
    	  }
    	  return 1 ; 
      }
}