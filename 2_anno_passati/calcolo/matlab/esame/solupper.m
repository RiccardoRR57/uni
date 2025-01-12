function [det, x] = solupper(U, b)

n = size(U);
n=n(1);
det = 1;

for k = 1:n
    det = det * U(k,k);
end

if(det == 0)
    error("Matrice non invertibile")
end

x = zeros(n, 1);
for i = n:-1:1
    x(i) = (b(i) - x'*U(i,:)') / U(i,i);
end

end