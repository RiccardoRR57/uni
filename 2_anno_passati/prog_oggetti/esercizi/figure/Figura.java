/**
 * Figura
 */
public abstract class Figura {

    public abstract double calcolaArea();
    public abstract double calcolaPerimetro();

    /**
	 * Metodo per la stampa dei dati (area e perimetro)
	 */
	public void dati()
	{
		System.out.println("La figura ha area di " + calcolaArea() + " e perimetro di " + calcolaPerimetro());
	}
}