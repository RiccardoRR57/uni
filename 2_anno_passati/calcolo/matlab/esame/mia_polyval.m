function [px] = mia_polyval(a, x)

n = length(a);
px = zeros(size(x));

for k=1:n
    px = px + a(k)*(x.^(n-k));
end
end