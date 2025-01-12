public class Rettangolo extends Figura{
    
    private double base;
    private double altezza;

    public Rettangolo(double base, double altezza) {
        this.base = base;
        this.altezza = altezza;
    }

    @Override
    public double calcolaArea() {
        return base*altezza;
    }
    @Override
    public double calcolaPerimetro() {
        return 2*(base+altezza);
    }

    public double getAltezza() {
        return altezza;
    }

    public double getBase() {
        return base;
    }
}
