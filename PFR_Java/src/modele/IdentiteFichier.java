package modele;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;


public class IdentiteFichier {
private Map<String,String> identifiantsColor = new HashMap<>();
private Map<String,String> identifiantsNB = new HashMap<>();

	
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
		List<String> res = FileHandler.readFileToList("/home/pfr/pfr/image/descripteurs_images/base_image_couleur.txt");
		System.out.println(res.toString()); 
		for (String string : res) {
			String[] parts = string.split(" "); // Splitting the string at the space character
			this.identifiantsColor.put(parts[0],parts[2]);
		}
		res=FileHandler.readFileToList("/home/pfr/pfr/image/descripteurs_images/base_image_NB.txt");
		for (String string : res) {
			String[] parts = string.split(" "); // Splitting the string at the space character
			this.identifiantsNB.put(parts[0],parts[2]);
		}
	}
		
	public String visualiserIdentifiantColor() {
		return this.identifiantsColor.toString();
	}
	
	public String visualiserIdentifiantNB() {
		return this.identifiantsNB.toString();
	}
	
	public  String getKeyByValueColor(String value) {
	    for (Entry<String, String> entry : this.identifiantsColor.entrySet()) {
	        if (entry.getValue().equals(value)) {
	            return entry.getKey();
	        }
	    }
	    return null;
	}
	
	public  String getKeyByValueNB(String value) {
	    for (Entry<String, String> entry : this.identifiantsNB.entrySet()) {
	        if (entry.getValue().equals(value)) {
	            return entry.getKey();
	        }
	    }
	    return null;
	}

	
	public Map<String,String> getListeFichierNB()
	{
		return this.identifiantsNB;
	}
	
	public Map<String,String> getListeFichierColor()
	{
		return this.identifiantsColor;
	}
	

}
