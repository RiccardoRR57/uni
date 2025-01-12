A = [1e-15 1 -2; 1 4 1; 2 5 6];

b = A * ones(3, 1);

[L, U, p] = gauss2(A);

d = L\b(p);
xc = U\d;

x = A\b;

norm(x-xc)/norm(x)