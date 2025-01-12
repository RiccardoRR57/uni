clear
close all
for n=999999999
    x = linspace(-1, 1, n)';
    y = 1./(1+25*x.^2);
    figure
    plot(x, y, 'rx', 'LineWidth',2)
    hold on
    fplot(@(x) 1./(1+25*x.^2), [-1,1])

    V = vander(x);
    V = V(:, n:-1:1);
    a = V \ y;

    xplot = linspace(-1,1,100);
    yplot = valutazione(xplot, a);
    hold on
    plot(xplot, yplot, 'b.-', 'LineWidth',3);
end