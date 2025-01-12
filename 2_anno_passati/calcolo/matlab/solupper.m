function [det, x]= solupper(U,b)

n = size(U);

if(not(isequal(n(2), n(1)))) 
    error("Matrice non quadrata")
end

n = n(1);

det = 1;

for i = 1:n
    det = det*U(i, i);
end

if(det==0)
    error("Matrice non invertibile")
end

x = zeros(n, 1);

for i = n:-1:1
    x(i)=(b(i) - U(i,:)*x)/U(i,i);

end