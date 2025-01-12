function [alpha] = min_quadrati(A, y)

y = y(:);

[m, n] = size(A);

if n > m
    error('La matrice A ha più colonne che righe');
end

if rank(A) < n
    error('Il rango di A è minore di n');
end

[Q, R] = qr(A);

R = R(1:n, :);

y_tilde = Q'*y;

y1 = y_tilde(1:n);

alpha = R\y1;

end