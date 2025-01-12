function [a] = bisez(N, n, m, Nmax)

for k = 1:Nmax

    a = n + (m-n)/2;
    if(a*a < N)
        n = a;
    else
        m=a;
    end
end


end