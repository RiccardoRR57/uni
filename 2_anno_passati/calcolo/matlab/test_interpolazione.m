clear
close all
x=(1:4)';
y=[3;5;6;4];

a = interpolazione(x,y);

z=3.5;
val = valutazione(z, a);

xplot = linspace(1,4,100)';
yplot = valutazione(xplot, a);
yplotlag = interp_lagrange(x,y,xplot);

plot(z, val, 'go', 'LineWidth', 3);
hold on;
plot(xplot, yplot);
hold on;
plot(xplot, yplotlag);
hold on;
plot(x, y, 'rx', 'LineWidth', 3);