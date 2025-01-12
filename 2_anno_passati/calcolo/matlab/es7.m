clear
close all

n=10;
x = (1900 : 10 : 1990)';
y = [76 92 105.7 122.8 131.7 150.7 179 205 226.5 248.7]';

plot(x, y, 'x', 'LineWidth', 3);

hold on;

V = vander(x);
V=V(:,n:-1:1);
a = V\y;
z = linspace(1900, 1990, 100);
pz = polyval(a(n:-1:1), z);
plot(z,pz, 'b', 'LineWidth', 3);

pzz=interp_lagrange(x, y, z);
plot(z, pzz, 'g', 'LineWidth', 3);

