import java.awt.Container;
import javax.swing.JFrame;

public class Omino {
	
	public static void main(String args[])
	{
		JFrame jf = new JFrame("Omino");
		//al posto di JFrame si potrebbe utilizzare BigFrame per avere una finestra grande
		jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		//Per settare una grandezza predefinita della finestra (poi per� se i cponenti interni sno pi� grandi la finestra si adatta)
		//jf.setPreferredSize(new Dimension(600,400));
		//jf.pack();
		//oppure
		jf.setLocation(500,200);
		jf.setSize(600,400);
		//o ancora
		//jf.setBounds(600,400,500,200);
		
		Container cjf = jf.getContentPane();
		NuovoPannello np = new NuovoPannello();
		cjf.add(np);
		jf.setVisible(true);
		
		//jf.show(); // per visualizzare la finestra (deprecato)
		
	}
}
