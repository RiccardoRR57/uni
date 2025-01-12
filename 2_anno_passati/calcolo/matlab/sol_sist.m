function [xc, ncond, normr, d] = sol_sist(A,b)

% soluzione calcolata con \
xc = A\b;

% numero condizionamento di A
ncond = cond(A, 2);

% calcolo norma del residuo
r = b - A*xc;
normr = norm(r);

% stima dell'errore
d = ncond*normr/norm(b);
end