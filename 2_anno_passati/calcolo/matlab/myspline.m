function C = myspline(x,y,zeta1,zeta2)
%
% Costruzione dei coefficienti di una spline cubica interpolante vincolata
% relativa ai nodi x, ai valori della funzione y, e con valori della
% derivata prima nei nodi iniziale e finale zeta1 e zeta2.
% C e' una matrice con tante righe quanti sono i sottointervalli e
% 4 colonne contenenti i coefficienti dei polinomi
% di grado 3 da quello della potenza 3 a quello della potenza 0
%
% s_i(x)=C(i,1)*(x-x_i)^3+C(i,2)*(x-x_i)^2+C(i,3)*(x-x_i)+C(i,4)
%

% Numero dei nodi di interpolazione - 2
m = length(x)-2;

% Ampiezze degli intervalli 
h = x(2:m+2)-x(1:m+1); % vettore di lunghezza m+1 contenenti le ampiezze degli m+1 intervalli

% Costruzione della matrice T
t0 = 2*(h(1:m) + h(2:m+1)); % diagonale principale di T
t1 =  h(1:m-1); % sovradiagonale di T % [0;h(1:n-3)];
t_1 = h(3:m+1); % sottodiagonale di T % [h(3:n-1);0];
T = diag(t_1,-1) + diag(t0) + diag(t1,1);
%T = spdiags([t_1,t0,t1],[-1,0,1],n-2,n-2); % crea una matrice sparsa

% Costruzione del vettore dei termini noti
b = (y(2:m+1)-y(1:m))./h(1:m).*h(2:m+1) + h(1:m).*(y(3:m+2)-y(2:m+1))./h(2:m+1);
b = 3*b;
b(1) = b(1)-zeta1*h(2);
b(m) = b(m)-zeta2*h(m);

% Risoluzione del sistema tridiagonale
z = T\b; % Trovo tutti i coefficienti relativi alle potenze di grado 1 (x-x_i)
z = [zeta1;z;zeta2]; % Aggiungo i coefficienti già noti in partenza

% Memorizzazione dei coefficienti locali
C = zeros(m+1,4);
C(:,1) = ( z(1:m+1)+z(2:m+2) - 2*(y(2:m+2)-y(1:m+1))./h(1:m+1) ) ./ h(1:m+1).^2;
C(:,2) = ( (y(2:m+2)-y(1:m+1))./h(1:m+1)-z(1:m+1) )./h(1:m+1)-C(:,1).*h(1:m+1);
C(:,3) = z(1:m+1); % coeff di x-x_i
C(:,4) = y(1:m+1); % coeff del termine omogeneo