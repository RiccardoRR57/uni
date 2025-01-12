public class Triangolo extends Figura {
    
    private double base;
    private double altezza;

    private double lato1;
    private double lato2;


    public Triangolo(double base, double altezza, double lato1, double lato2) {
        this.base = base;
        this.altezza = altezza;
        this.lato1 = lato1;
        this.lato2 = lato2;
    }    

    @Override
    public double calcolaArea() {
        return (base*altezza)/2;
    }
    @Override
    public double calcolaPerimetro() {
        return base+lato1+lato2;
    }
}
