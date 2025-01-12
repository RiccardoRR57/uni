% Script per l'ingrandimento di un'immagine tramite il comando interp2

% Pulisco il workspace e chiudo tutte le finestre grafiche
clear
close all

% Carico "lena.mat" contenente un'immagine 100x100 dal file lena
load lena.mat 

% Mostro a video l'immagine di partenza e l'immagine 200x200 da riempire
obj_zoom = zeros(200);
obj_zoom(1:2:200,1:2:200) = obj;
subplot(1,2,1); imshow(obj,[]);
set(gca,'Units','pixels'); 
set(gca,'Position',[1 1 100 100]);
subplot(1,2,2); imshow(obj_zoom,[]);
set(gca,'Units','pixels'); 
set(gca,'Position',[110 1 200 200]);
pause

% Punti di interpolazione e griglia di ingrandimento
X = 1:2:200; % vettore delle coordinate x_i di interpolazione
Y = X'; % vettore delle coordinate y_i di interpolazione
Z = obj; % vettore dei valori f(x_i,y_i) 
Xq = 1:200; % vettore delle ascisse xq_i 
            % dei punti Q_i in cui valutare
            % l'interpolante
Yq = Xq';  % vettore delle ordinate yq_i 
            % dei punti Q_i in cui valutare
            % l'interpolante
% Ingrandimento immagine mediante interpolazione bilineare            
x_zoom_lin = interp2(X,Y,Z,Xq,Yq,'linear'); 
            
% Ingrandimento immagine mediante interpolazione bicubica
x_zoom_cub = interp2(X,Y,Z,Xq,Yq,'cubic'); 

% Metto l'immagine originale e le immagini ingrandite a confronto
figure;

subplot(1,3,1); imshow(obj,[]);
set(gca,'Units','pixels'); 
set(gca,'Position',[1 1 100 100]);

subplot(1,3,2); imshow(x_zoom_lin,[]);
set(gca,'Units','pixels'); 
set(gca,'Position',[110 1 200 200]);

subplot(1,3,3); imshow(x_zoom_cub,[]);
set(gca,'Units','pixels'); 
set(gca,'Position',[320 1 200 200]);

pause

% Confronto tra interpolazione bilineare e bicubica
figure;
subplot(1,2,1); imshow(x_zoom_lin(100:180,100:180),[]); title('bilineare')
subplot(1,2,2); imshow(x_zoom_cub(100:180,100:180),[]); title('bicubica')