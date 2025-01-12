function [L, U] = gauss1(A)

n = size(A);
n = n(1);

for k=1:n-1
    if abs(A(k,k)) < eps
        error("Matrice non fattorizzabile")
    end
    A(k+1:n,k) = A(k+1:n,k)/A(k,k); % moltiplicatori di Gauss
    A(k+1:n, k+1:n) = A(k+1:n, k+1:n) - A(k+1:n,k)*A(k,k+1:n); % trasformazioni di Gauss
    
    %for i=k+1:n
    %    A(i,k)=A(i,k)/A(k,k);
    %    for j=k+1:n
    %        A(i,j)=A(i,j)-A(i,k)*A(k,j);
    %    end
    %end
end

U=triu(A);
L=(A-U) + eye(n);

end