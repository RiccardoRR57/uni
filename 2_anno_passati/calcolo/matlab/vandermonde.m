function [V] = vandermonde(x)

n = size(x);

for i = 1:n
    V(1:n,i) = x.^(i-1);
end