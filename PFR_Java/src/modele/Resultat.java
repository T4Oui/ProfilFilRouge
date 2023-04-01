package modele;

import java.util.List;

public class Resultat {
	private List<String> listeResultat;
	private TypeRecherche typeResultat;
	private TypeRechercheCouleur typeResultatCouleur;
	private Recherche recherche;
	
	public Resultat(TypeRecherche typeResultat, List<String> listeResultat, Recherche recherche)	{
		this.typeResultat = typeResultat;
		this.listeResultat=listeResultat;
		this.recherche=recherche;
	}
	
	public Resultat(TypeRechercheCouleur type, List<String> listeResultat, Recherche recherche)	{
		this.typeResultatCouleur = type;
		this.listeResultat=listeResultat;
		this.recherche=recherche;
	}
	
	public TypeRecherche getTypeResultat() {
		return this.typeResultat;
	}
	
	public TypeRechercheCouleur getTypeResultatCouleur() {
		return this. typeResultatCouleur;
	}
	
	public List<String> getListeResultat() {
		return this.listeResultat;
	}
	
	public Recherche getRecherche()
	{
		return this.recherche;
	}
	
	public String toString ()
	{
		return this.recherche.toString()+" ==> Resultat : "+this.listeResultat.toString().substring(1, this.listeResultat.toString().length()-1);
	}
}
