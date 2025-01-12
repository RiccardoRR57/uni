import java.awt.*;
import javax.swing.*;

public class NuovoPannello extends JPanel{

	public void paintComponent(Graphics g) // o anche solo paint
	{
		super.paintComponent(g);
		setBackground(Color.blue);
		g.setColor(Color.magenta);
		//g.drawRect(40, 40, 40, 70);
		g.fillOval(100, 100, 50, 50);
		g.drawRect(120, 150, 10, 150);
		g.drawLine(120, 150, 100, 220);
		g.drawLine(130, 150, 150, 220);
		g.drawLine(120, 300, 100, 350);
		g.drawLine(130, 300, 150, 350);
	}
}
