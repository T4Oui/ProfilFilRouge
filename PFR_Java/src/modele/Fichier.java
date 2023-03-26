package modele;

import java.awt.Desktop;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;


public class Fichier {
	
	public static List<String> lire(String chemin) {
		List<String> resultat = new ArrayList<>();		
			
		try {
			
			File f = new File(chemin);
			
			FileReader fileReader = new FileReader(f);

			BufferedReader reader = new BufferedReader (fileReader);
			
		    String line = reader.readLine();
		    while(line != null) 
		    {	 	
		         resultat.add(line);
	         
		         line = reader.readLine();
		    }
		    reader.close();
		    
		} catch (IOException ex) {
			ex.printStackTrace();
		}
		
		return resultat;
	
	}
	
	
	public static void supprimer (String chemin) {
		
		  // Créer un objet File pour le fichier à supprimer
        File f = new File(chemin);

        // Vérifier si le fichier existe
        if (f.exists()) {
            // Supprimer le fichier
            f.delete();
        }
	}
	
	public static void ouvrirFichierTexte(String chemin)  {
        File fichier = new File(chemin);

        if (!fichier.exists()) {
            System.out.println("Le fichier n'existe pas.");
            return;
        }

        Desktop desktop = Desktop.getDesktop();
        try {
            desktop.open(fichier);
        } catch (IOException e) {
            e.printStackTrace();
        }
	}
	
}
