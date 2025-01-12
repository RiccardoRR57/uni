function p = valspline(C,x,xf)
%
% Valutazione di una spline (relativa ai nodi x) nella griglia di punti xf
% i coefficienti dei polinomi che formano la spline sono i C
%

% Numero dei sottointervalli + numero dei coefficienti della spline su
% ciascun sottointervallo
n = size(C,1);

% Inizializzo il vettore contenente le valutazioni della spline
p = zeros(length(xf),1);

% Valutazione della spline di interpolazione sulla griglia di punti xf
for i = 1 : length(xf)
    
    % Individuo il sottointervallo a cui appartiene xf(i)
    ij = find(x>xf(i));
    if isempty(ij) && x(end)~=xf(i)
        error('un elemento di xf cade fuori');
    elseif xf(i) == x(end)
        k = n;
    else
        k = ij(1)-1;
    end
    
    % Algoritmo di Horner
    p(i) = C(k,1)*(xf(i)-x(k))+C(k,2);
    p(i) = p(i)*(xf(i)-x(k))+C(k,3);
    p(i) = p(i)*(xf(i)-x(k))+C(k,4);
    
end