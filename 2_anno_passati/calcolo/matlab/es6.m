for n = 4: 2: 10
    
    A = hilbert(n);
    x_es = ones(n,1);
    b = A*x_es;
    [xc, ncond, normr, d] = sol_sist(A,b);
    fprintf('Caso n: %d \n', n);
    fprintf('Ncond = %e \n', ncond);
    fprintf('Norma residuo: %e \n', normr);
    fprintf('Stima errore: %e \n', d);
    fprintf('Errore effettivo = %e \n\n', norm(xc-x_es)/norm(x))

end