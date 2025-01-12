function [n] = norma2(x)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
x= x.^2;
n = sum(x);
n=sqrt(n);
end