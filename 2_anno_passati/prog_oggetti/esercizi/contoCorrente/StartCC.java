public class StartCC{
	public static void main(String[] args) {
		
		// creazione di un vettore di conti correnti
		ContoCorrente[] ccVett = new ContoCorrente[3];

		// ATTENZIONE: creare un vettore di tipo non equivale ad inizializzare ogni
		// singola cella => occorre inizializzare ogni cella del vettore

		// inizializzazione delle celle
		ccVett[0] = new ContoCorrente(10, 1000);
		ccVett[1] = new ContoCorrente(11, 0);
		ccVett[2] = new ContoCorrente(13, 3000);

		// operazioni sui conti correnti
		System.out.println(ccVett[0].getSaldo());
		System.out.println(ccVett[1].getSaldo());
		System.out.println(ccVett[2].getSaldo());

		ccVett[0].prelievo(500);
		ccVett[0].prelievo(200);
		ccVett[1].versamento(1000);
		ccVett[2].versamento(10000);

		System.out.println(ccVett[0].getSaldo());
		System.out.println(ccVett[1].getSaldo());
		System.out.println(ccVett[2].getSaldo());

		ccVett[0].stampa();
		ccVett[1].stampa();
		ccVett[2].stampa();

		// ATTENZIONE: cosa produce questo codice?
		for (int i = 0; i < 20; i++) {
			ccVett[0].versamento(10);
		}

		// RISPOSTA:
		// a) aggiunge al saldo 10*20=200 unitö
		// b) produce un errore

	}
}
