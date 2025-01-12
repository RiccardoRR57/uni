% script di verifica correttezza funzione 

b1 = rand(5, 1);
U1 = rand(5);
U1 = triu(U1);

[d, xc] = solupper(U1, b1);
x = U1\b1;

err = norm(x-xc)/norm(x)