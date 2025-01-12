function [x ,i] = newton_radice(N, x0, tau, Nmax)

if(N<0 || x0 <= 0)
    error("metodo non possibile");
end

for i = 1:Nmax
    fx = x0^2-N;
    dfx = 2*x0;

    if dfx == 0
        error("Trovata tangente orizzontale");
    end

    x = x0 - fx/dfx;

    if abs(x - x0)/abs(x) <= tau && abs(fx) <= tau
        break;
    end

    x0 = x;
end