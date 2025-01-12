function p = valutazione(x, a)

n = size(a);

p = 0;

for i = 1:n
    p = p + a(i)*x.^(i-1);
end

end