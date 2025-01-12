function [norma] = normap(x,p)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
if(p==inf) 
    max = x(0);
    for i = 1:
    norma=max(x);
else 
    norma = sum(x.^p)^(1/p);
end