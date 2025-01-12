function [c, i] = bisezione_radice(m, n, N, Nmax)
if N<0
    error("radice negativa non esiste");
end
if m*m > N || n*n < N
    error("N non è nell'intervallo sscelto");
end

for i = 1 : Nmax
    c = m + (n-m)/2;
    fc = c^2-N;
    if fc == 0
        break
    end
    if fc < 0
        m = c;
    else
        n = c;
    end
end