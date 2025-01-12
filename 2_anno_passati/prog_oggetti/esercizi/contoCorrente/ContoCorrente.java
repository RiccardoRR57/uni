public class ContoCorrente {

    private int numero;

    private int saldo;

    private int[] movimenti;

    private int numMovimenti;

    public ContoCorrente(int numero, int saldo) {
        
        this.numero = numero;
        this.saldo = saldo;
        movimenti = new int[20];
        numMovimenti = 0;
    }

    public void prelievo(int importo) {
        saldo = saldo - importo;
        movimenti[numMovimenti] = -importo;
        numMovimenti++;
    }

    public void versamento(int importo) {
        saldo = saldo + importo;
        movimenti[numMovimenti] = importo;
        numMovimenti++;
    }

    public int getSaldo() {
        return saldo;
    }

    public int getNumero() {
        return numero;
    }

    public void stampa() {
        for (int i = 0; i < numMovimenti; i++) {
            System.out.println(movimenti[i]);
        }
    }
}