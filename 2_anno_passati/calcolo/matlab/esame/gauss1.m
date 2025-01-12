function [L,U] = gauss1(A)

n = size(A);
n=n(1);

for k=1:n-1
    if A(k,k) < eps
        error("Matrtice non fattorizzabile con Gauss")
    end
    for i=k+1:n
        A(i,k) = A(i,k)/A(k,k);
        for j=k+1 : n
            A(i,j) = A(i,j) - A(i,k)*A(k,j);
        end
    end
end

U = triu(A);
L = A - U + eye(n);

end