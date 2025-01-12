function a = interpolazione(x,y)

V = vandermonde(x);

a = V\y;

end