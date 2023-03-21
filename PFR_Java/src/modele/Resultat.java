package modele;

import java.util.List;

public class Resultat {
	private List<String> listeResultat;
	private TypeRecherche typeResultat;
	
	public Resultat(TypeRecherche type, List<String> listeResultat) {
		this.typeResultat = type;
		this.listeResultat=listeResultat;
	}
	
	public TypeRecherche getTypeResultat() {
		return this.typeResultat;
	}
	
	public List<String> getListeResultat() {
		return this.listeResultat;
	}
}