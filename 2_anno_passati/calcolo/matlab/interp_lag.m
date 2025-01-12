function lv = interp_lag(x,y,v)


if length(x) ~= length(y)
    error('Dimensioni di x e y incompatibili')
end

n = length(y);
lv = zeros(size(v));

for j = 1: n 

    ljv = ones(size(v));
    for i = 1 : n
    
        if i ~= j
            ljv = ljv .*(v-x(i))/(x(j)-x(i));
        end


    end

    lv = lv + y(j)*ljv; %elemendo j-esimo della base di lagrange valutato in v.

end