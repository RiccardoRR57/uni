public class TriangoloRettangolo extends Triangolo{

    public TriangoloRettangolo(double base, double altezza) {
        super(base, altezza, altezza, Math.sqrt((altezza*altezza)+(base*base)));
    }
    
}
