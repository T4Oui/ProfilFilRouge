package modele;

import java.util.List;

public class Resultat {
	private List<String> listeResultat;
	private TypeRecherche typeResultat;
	private TypeRechercheCouleur typeResultatCouleur;
	
	public Resultat(TypeRecherche type, List<String> listeResultat)	{
		this.typeResultat = type;
		this.listeResultat=listeResultat;
	}
	
	public Resultat(TypeRechercheCouleur type, List<String> listeResultat)	{
		this.typeResultatCouleur = type;
		this.listeResultat=listeResultat;
	}
	
	public TypeRecherche getTypeResultat() {
		return this.typeResultat;
	}
	
	public TypeRecherche getTypeResultatCouleur() {
		return this. typeResultatCouleur;
	}
	
	public List<String> getListeResultat() {
		return this.listeResultat;
	}
}
