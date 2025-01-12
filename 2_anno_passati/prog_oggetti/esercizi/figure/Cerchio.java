public class Cerchio extends Figura {

    private double raggio;
    static final double PI = 3.14;

    public Cerchio(double raggio) {
        this.raggio = raggio;
    }
    
    public double getRaggio() {
        return raggio;
    }

    @Override
    public double calcolaArea() {
        return raggio*raggio*PI;
    }

    @Override
    public double calcolaPerimetro() {
        return 2*raggio*PI;
    }
}
