function [x] = jacobi(A, b, Nmax, x0)
    x = x0;
    d = diag(A);
    
    for k = 1 : Nmax
        x = x + b./d - (A*x)./d;
    end
end