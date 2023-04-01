package modele;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;


public class IdentiteFichier {
private Map<String,String> identifiants = new HashMap<>();
	
	private IdentiteFichier() {
		// TODO Auto-generated constructor stub
	}
	
	private static class IdentiteFichierHolder{
		private static final IdentiteFichier INSTANCE = new IdentiteFichier();
	}
	
	public static IdentiteFichier getInstance() {
		return IdentiteFichierHolder.INSTANCE;
	}
	
	public void ajouterIdentifiant() {
		List<String> res = FileHandler.readFileToList("/Users/valentin/Downloads/base_image/ base_image_couleur.txt");
		for (String string : res) {
			String[] parts = string.split(" "); // Splitting the string at the space character
			this.identifiants.put(parts[0],parts[2]);
		}
		res=FileHandler.readFileToList("/Users/valentin/Downloads/base_image/ base_image_NB.txt");
		for (String string : res) {
			String[] parts = string.split(" "); // Splitting the string at the space character
			this.identifiants.put(parts[0],parts[2]);
		}
	}
		
	public String visualiserIdentifiant() {
		return this.identifiants.toString();
	}
	
	public  String getKeyByValue(String value) {
	    for (Entry<String, String> entry : this.identifiants.entrySet()) {
	        if (entry.getValue().equals(value)) {
	            return entry.getKey();
	        }
	    }
	    return null;
	}
	

}
