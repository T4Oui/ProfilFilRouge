package modele;
import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.Scanner;
import java.io.PrintWriter;

public class Parametre {
	 private int nbOccurence ;
	 private int nbBit ;
	 private int nbrEchantillon   ; 
	 private int tailleIntervalle  ; 
	 private int  modeRecherche ; 
	 
	 
	 private  Parametre () {
		 
		 String filename = "/home/pfr/pfr_code/config.txt"; // nom du fichier de configuration 
	        
	        try {
	            // Ouvre le fichier de configuration en lecture
	            File configFile = new File(filename);
	            Scanner scanner = new Scanner(configFile); 
	            // Lit le fichier ligne par ligne
	                String line = scanner.nextLine();
	                String[] tab = line.split("\\s+") ;
	                nbOccurence  = Integer.parseInt(tab[0]) ;  
	                line = scanner.nextLine();
	                tab = line.split("\\s+") ;
	                nbBit = Integer.parseInt(tab[0]) ;
	                line = scanner.nextLine();
	                tab = line.split("\\s+") ;
	                nbrEchantillon = Integer.parseInt(tab[0]) ;
	                line = scanner.nextLine();
	                tab = line.split("\\s+") ;
	                tailleIntervalle = Integer.parseInt(tab[0]) ;
	                line = scanner.nextLine();
	                tab = line.split("\\s+") ;
	                modeRecherche = Integer.parseInt(tab[0])  ;
	                scanner.close();
	                
	        } catch (IOException e) {
	            e.printStackTrace();
	        }       
	                 
	 }
	 
	 private static class ParametreHolder {
		 private static final Parametre intance = new Parametre ();
	 }
	 public static Parametre getIntance () {
		 return (ParametreHolder.intance ) ; 
	 }
	@Override
	public String toString() {
		return "Parametre \n nbOccurence = " + nbOccurence + "\n nbBit = " + nbBit + "\n nbrEchantillon = " + nbrEchantillon
				+ "\n tailleIntervalle = " + tailleIntervalle + "\n modeRecherche = " + getMode().toString() ;
	} 
	
	
    public void modifier  ( int nou , int nbrLig){
	     
	        String line ;
	        String filename = "/home/pfr/pfr_code/config.txt"; // nom du fichier de configuration 
	        
	        try {
	            // Ouvre le fichier de configuration en lecture
	            File configFile = new File(filename);
	            Scanner scanner = new Scanner(configFile);
	            StringBuilder buffer = new StringBuilder();
	            int i = 1 ; 
	            // Lit le fichier ligne par ligne
	            while (scanner.hasNextLine() ) {
	                line = scanner.nextLine();
	                if (i == nbrLig) {
	                	String[] restLigne = line.split("\\s+") ;
	                	int debut = 1;
	                	restLigne = Arrays.copyOfRange(restLigne, debut, restLigne.length);
	                	String  ligne = String.join( " " , restLigne) ; 
		                    // Modifie la ligne contenant le nombre
	                    line = nou  + " " +  ligne  ;
	                }
	                buffer.append(line).append(System.lineSeparator());
	                i++ ;  
	            }
	            scanner.close();
	            
	            // Écrit les modifications dans le fichier
	            PrintWriter writer = new PrintWriter(configFile);
	            writer.write(buffer.toString());
	            writer.close();
	        } catch (IOException e) {
	            e.printStackTrace();
	        }
	    }
	public void setNbrOcc ( int nbrOcc) {
    modifier  (  nbrOcc , 1) ; 
		this.nbOccurence = nbrOcc ;
		
	}
	public void setNbrBit (int nbrBit) {
		modifier ( nbrBit , 2 );
		this.nbBit = nbrBit ; 
	}
	public void setNbrEch ( int nbrEch) {
		modifier(nbrEch , 3);
		this.nbrEchantillon = nbrEch ; 
	}
	public  void setIntervalle ( int intervalle) {
		modifier( intervalle , 4);
		this.tailleIntervalle = intervalle ; 
	}
	public void setModeRecherche ( int mode ) {
		modifier( mode , 5);
		this.modeRecherche = mode ; 
			
		}
	
	public ModeRecherche getMode() {
		switch ( modeRecherche ){
		case  1 : 
			return ( ModeRecherche.OUVERT ); 
			
		case 2 : 
			return ( ModeRecherche.FERME ); 
			
		default :  
			return ( ModeRecherche.MULTI_MOTEUR ); 
	     }

     }
}