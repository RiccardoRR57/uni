% esercizio 2

t = [0 10 20 30 40 80 90 100]';
s = [68.0 67.1 66.4 65.6 64.6 61.8 61.0 60.0]';

m = length(t);
A = [ones(m, 1) t];
alpha = min_quadrati(A, s);

V = vander(t);
V = V(:, m:-1:1);
a= V\s;
a = a(m:-1:1);

plot(t,s,'ro');
hold on;
z = linspace(t(1), t(m));
new = [50 60 70];

pz = alpha(1) + alpha(2)*z;
pz_stima = alpha(1) + alpha(2)*new;
plot(z, pz, 'g');

hold on;
pz2 = polyval(a,z);
pz2_stima = polyval(a,new);
plot(z, pz2, 'b');


pz_stima
pz2_stima
