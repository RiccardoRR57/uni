package ex2;


public class ContoCorrente {
	private int numCC;
	private int saldo;
	private int movimenti[];
	private int numMovimenti;
	
	public ContoCorrente(int numCC, int saldo) {
		setNumCC(numCC);
		setSaldo(saldo);
		this.movimenti = new int[10];
		this.numMovimenti = 0;
	}
	
	void prelievo(int importo) {
		this.movimento(-importo);
	}
	
	void versamento(int importo) {
		this.movimento(importo);
	}
	
	/**
	 * Aggiunge un elemento ai movimenti, aggiorna il saldo, 
	 * se l'array non ha più spazio viene esapanso per contenere altri 10 elementi
	 * @param importo 
	 */
	private void movimento(int importo) {
		this.setSaldo(this.getSaldo() + importo);
		if(numMovimenti >= movimenti.length) {
			int tmp[] = new int[movimenti.length*2];
			System.arraycopy(movimenti, 0, tmp, 0, movimenti.length);
			//tmp = Arrays.copyOf(movimenti, movimenti.length);
			movimenti = tmp;
		}
		movimenti[numMovimenti++] = importo; 
	}

	private void setNumCC(int numCC) {
		this.numCC = numCC;
	}

	public int getSaldo() {
		return saldo;
	}

	private void setSaldo(int saldo) {
		this.saldo = saldo;
	}
	
	public void print() {
		System.out.println("Numero Conto: " + this.numCC);
		System.out.println("Saldo Attuale: " + this.saldo);
		for(int i = 0; i<numMovimenti; i++) {
			if(movimenti[i] > 0) {
				System.out.print("Versamento: ");
			}
			else {
				System.out.print("Prelievo: ");
			}
			System.out.println(Math.abs(movimenti[i]));
		}
	}
}
