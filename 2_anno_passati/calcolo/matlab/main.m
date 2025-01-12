clear all
close all
clc

%% Funzione di Runge

f = @(x) 1./(1+25*x.^2);
xf = linspace(-1,1,500)'; % Griglia di punti in cui valutare la spline cubica vincolata
fx = f(xf);

%% Interpolazione della funzione mediante una spline cubica vincolata

m = 40; 
x = linspace(-1,1,m+2)'; % m+2 punti di interpolazione
y = f(x); % m+2 valori della funzione nei punti di interpolazione

zeta1 = 0; % Derivata della spline al nodo iniziale
zeta2 = zeta1; % Derivata della spline al nodo finale

C = myspline(x,y,zeta1,zeta2);
p = valspline(C,x,xf);

plot(x,y,'bx','LineWidth',3);
hold on;
plot(xf,fx,'k','LineWidth',3);
hold on;
plot(xf,p,'r','LineWidth',3); 
legend('$(x_i,f(x_i))$','$f(x)$','$s(x)$','Interpreter','Latex');


