function [L, U, p] = gauss2(A)

n = size(A);
n = n(1);
p = (1:n)';     

for k=1:n-1
    
    [pivot, index] = max(abs(A(k:n, k)));
    index = index + k-1;
    
    if index ~= k
        % scambio le righe
        app = A(k, :);
        A(k,:) = A(index,:);
        A(index,:) = app;
        
        % aggiorno il vettore p
        app = p(k);
        p(k) = p(index);
        p(index) = app;
    end
    
    if abs(A(k,k)) < eps
        error("Matrice non fattorizzabile")
    end

    % eliminazione di gauss
    A(k+1:n,k) = A(k+1:n,k)/A(k, k); % moltiplicatori di Gauss
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