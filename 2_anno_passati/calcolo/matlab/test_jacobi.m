A = diag(-3*ones(1,20)) + diag(1*ones(1,20-1),1) + diag(1*ones(1,20-1),-1);

b = diag(ones(20));

xes = A\b;

for k = 1:10
    x = jacobi(A, b, k, zeros(20,1));
    y = gauss_seidl(A, b, k, zeros(20,1));

    
    errx(k) = (norm(xes - x))/norm(xes);
    erry(k) = (norm(xes - y))/norm(xes);
end

errx'
erry'