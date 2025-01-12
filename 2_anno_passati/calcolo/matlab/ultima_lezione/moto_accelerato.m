% esercizio 2

t = [0 1 1.5 2 2.5 3 3.5 4]';
s = [0 1.2 3.0 3.7 7.9 11.6 15.5 19.8]';

m = length(t);
A = [ones(m, 1) t t.^2];
alpha = min_quadrati(A, s);

V = vander(t);
V = V(:, m:-1:1);
a= V\s;
a = a(m:-1:1);

plot(t,s,'ro');
hold on;
z = linspace(t(1), t(m));
new = [1.3 2.4 3.7];

pz = alpha(1) + alpha(2)*z + alpha(3)*z.^2;
pz_stima = alpha(1) + alpha(2)*new + alpha(3)*new.^2;
plot(z, pz, 'g');

hold on;
pz2 = polyval(a,z);
pz2_stima = polyval(a,new);
plot(z, pz2, 'b');


pz_stima
pz2_stima
