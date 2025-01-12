package motori;

/**
 * Motore
 */
public class Motore {

    /**
     * Cilindrata misurata in CC
     */
    private int cilindrata;

    private int cilindri;

    /**
     * Potenza misurata in cavalli
     */
    private int potenza;

    private Boolean diesel;

    public Motore(int cilindrata, int cilindri, int potenza) {
        this.cilindrata = cilindrata;
        this.cilindri = cilindri;
        this.potenza = potenza;
    }
    
    public int getCilindrata() {
        return cilindrata;
    }

    public int getCilindri() {
        return cilindri;
    }

    public int getPotenza() {
        return potenza;
    }

    public Boolean isDiesel() {
        return diesel;
    }
}