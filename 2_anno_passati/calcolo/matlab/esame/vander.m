function [V] = vander(x)
% Calcolo la dimensione del vettore x
n = length(x);
% Creo una matrice nxn di zeri
V=ones(n);

for k=1:n
    V(k,:) = x(k).^(0:n-1);
end

end