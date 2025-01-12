package ex1;

public class Libro {
	private String autore;
	private String titolo;
	private int n_copie;
	private int n_pagine;
	private String genere;
	
	public Libro(String titolo, String autore, int n_copie, int n_pagine, String genere) {
		this.autore=autore;
		this.titolo=titolo;
		this.n_copie=n_copie;
		this.n_pagine=n_pagine;
		this.genere=genere;
	}
	
	public boolean prestito() {
		if(this.n_copie > 0) {
			this.n_copie--;
			return true;
		}
		return false;
	}
	
	public void restituzione() {
		this.n_copie++;
	}
}
