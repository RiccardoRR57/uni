function lv = interp_lagrange(x, y, v)


if length(x) ~= length(y)
    error("dimensioni x e y")
end

n = length(y);
lv = zeros(size(v));

for j = 1: n

    ljv = ones(size(v));
    for i = 1 : n

        if i ~= j
            ljv = ljv .*(v-x(i))/((x(j)-x(i)));
        end
    end

    lv = lv +y(j)*ljv;

end