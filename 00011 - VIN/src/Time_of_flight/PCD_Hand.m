% PCD_Hand.m--
%
% Syntax: 
%
% e.g.,   

% Developed in Matlab 9.7.0.1190202 (R2019b) on PCWIN64.
% JDU - Jean Demeusy (jean.demeusy@heig-vd.ch), 2019-11-11 14:29
%-------------------------------------------------------------------------

%% Setup
close all;
clear;
clc;

%% Variable
pcd = pcread("20191108T113836\41_ProcessedXYZ.pcd");
%pcd = pcread("20191107T191549\1_ProcessedXYZ.pcd");
hexMap = {'454545','38523A','29602F','1B6F23','0C7E17','008A0E'};

%% Code
range = pcd.Location(:,:,3);
range = range(10:end-8,10:end-8);
range = xmap(range,0,255);

num_el = 3;
myColorMap = zeros(num_el, 3);

myColorMap(:,1) = xmap(1:num_el,0, 0);
myColorMap(:,2) = xmap(1:num_el,0, 1);
myColorMap(:,3) = xmap(1:num_el,1,.5);

%% Display
ximshow(pcd.Intensity, range);

subplot(1,2,2);
colormap(gca, myColorMap); % Ignore pink map and use jet instead.
