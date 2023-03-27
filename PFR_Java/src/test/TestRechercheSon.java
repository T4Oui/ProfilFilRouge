package test;

import java.io.IOException;

import controleur.ControlRechercheSon;
import modele.RechercheSon;
import vueconsole.BoundaryRechercheSon;

public class TestRechercheSon {

	public static void main(String[] args) throws IOException {

		ControlRechercheSon controlRechercheSon = new ControlRechercheSon(null);

		BoundaryRechercheSon boundaryRechercheSon = new BoundaryRechercheSon(controlRechercheSon);
		boundaryRechercheSon.rechercheSon();

	}

}
