package controleur;

public class ControlSIdentifier {
	
	private final String motDePasse = "feur" ; 
    public ControlSIdentifier() {
		
	}
	public  boolean verifierMotDePasse (String mdp ) {
		return (mdp.equals(motDePasse));
	}

}