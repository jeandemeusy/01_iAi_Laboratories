% convex_hull_example.m--
%
% Syntax: 
%
% e.g.,   

% Developed in Matlab 9.7.0.1190202 (R2019b) on PCWIN64.
% JDU - Jean Demeusy (jean.demeusy@heig-vd.ch), 2019-11-12 17:50
%-------------------------------------------------------------------------

%% Setup
%close all;
clear;
clc;

%% Variable
%P = [5 10; 10 5; 25 5; 20 10; 10 10; 16 45; 20 35; 53 50; 36 32; 25 15; 39 10; 30 55 ];
% P = round(rand(90,2)*60) + 10;
[a,b] = ndgrid(100:50:700, 100:50:700);
P = [a(:) b(:)];

tic
[L_hull,L_ens] = convex_hull(P);
toc

%% Code
subplot(1,3,1);
plot(P(:,1),P(:,2),'.k'); axis equal; hold on;
xlim([0 800]);
ylim([0 800]);
for k = 1:size(L_ens,1)
    %text(L_ens(k,1)-3,L_ens(k,2)+3,"p"+num2str(k-1));
end 
hold off;

%% Display
subplot(1,3,3);
plot(P(:,1),P(:,2),'.k'); hold on; axis equal;
plot(L_hull(:,1),L_hull(:,2),"-g","LineWidth",1.5);
xlim([0 800]);
ylim([0 800]); hold off;

subplot(1,3,2);
plot(P(:,1),P(:,2),'.k'); hold on; axis equal;
plot([P(1,1),P(2,1)],[P(1,2), P(2,2)],"-k","LineWidth",1.5);
plot([P(2,1),P(4,1)],[P(2,2), P(4,2)],"-k","LineWidth",1.5);
plot([P(4,1),P(5,1)],[P(4,2), P(5,2)],"-k","LineWidth",1.5);
plot([P(5,1),P(7,1)],[P(5,2), P(7,2)],"-k","LineWidth",1.5);
plot([P(7,1),P(1,1)],[P(7,2), P(1,2)],"-k","LineWidth",1.5);
xlim([0 800]);
ylim([0 800]); hold off;
