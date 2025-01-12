function [x] = gauss_seidl(A, b, Nmax, x)

[n, m] = size(A);

for k = 1:Nmax
    for i = 1:n
        x(i) = x(i) + b(i)/A(i,i) - (A(i,:)*x)/A(i, i);
    end
end