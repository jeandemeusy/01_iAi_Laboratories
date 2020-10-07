% data_load_pcd.m--
%
% Syntax: 
%
% e.g.,   

% Developed in Matlab 9.7.0.1190202 (R2019b) on PCWIN64.
% JDU - Jean Demeusy (jean.demeusy@heig-vd.ch), 2019-11-11 15:29
%-------------------------------------------------------------------------

%% Setup
close all;
clear;
clc;

%% Variable
data = importdata("20191108T113836\dataText.txt");
real_img = imread("20191108T113836\41_Range.png");

zdata = data(:,3);

%% Code
img = reshape(zdata,[640,480])';

real_img = xmap(real_img,0,255);
img = xmap(img,0,255);

%% Display
ximshow(img, real_img, double(real_img)-double(img));