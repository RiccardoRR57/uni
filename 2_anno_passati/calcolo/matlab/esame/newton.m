function [x] = newton(N, x0, tau, Nmax)

%funzione è     x^2 - N = 0

for k = 1:Nmax
    x = x0 - (x0*x0 -N)/(2*x0);
    if (abs(x*x - N) < tau) && abs(x-x0) < tau
        break;
    end
    x0=x;
end

end