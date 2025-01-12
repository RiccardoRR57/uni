/**
 * Classe di esempio per l'utilizzo della classe astratta FIGURE
 * @author mariachiarapuviani
 *
 */
public class Prova 
{
	public static void main(String[] args) 
	{
		// Definisco delle generiche figure
		Figura f [] = new Figura[5];
	
		// Specifico le figure
		f[0] = new Quadrato(12);
		f[1] = new Rettangolo(6,5);
		f[2] = new Triangolo(4,3,5,4);
		f[3] = new TriangoloRettangolo(4,5);
		f[4] = new Cerchio(3);
		
		// Stampo i dati delle figure
		for(int i=0; i<5; i++)
		{
			f[i].dati();
		}
	}
	
}


