A = [1 2 3; 4 34 6; 7 5 9];

b = A * ones(3, 1);

[L, U] = gauss1(A);

d = L\b;
xc = U\d;

x = A\b;

norm(x-xc)/norm(x);