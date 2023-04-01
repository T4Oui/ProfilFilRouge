package modele;

public class Recherche {
	private String nom;
	private float pourcentage;
	public Recherche(String nom, float pourcentage)
	{
		// TODO Auto-generated constructor stub
		this.nom=nom;
		this.pourcentage=pourcentage;
	}
	public void setNom(String nom)
	{
		this.nom=nom;
	}
	
	public String getNom(Recherche recherche)
	{
		return this.nom;
	}
	
	public String toString()
	{
		if(this.pourcentage != 0)
		{
			return "Recherche : "+this .nom + String.valueOf(this.pourcentage);
		}
		else
			return "Recherche : "+this.nom;
	}
	


}
