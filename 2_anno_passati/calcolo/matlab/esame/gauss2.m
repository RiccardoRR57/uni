function [L,U,p] = gauss2(A)

n = size(A);
n=n(1);
p=1:n;

for k = 1:n-1
    [m, i] = max(A(k:n, k));
    i = i + k-1;

    app = A(k, :);
    A(k,:) = A(i,:);
    A(i,:) = app;
    p(i) = k;
    p(k) = i;

    

end

end