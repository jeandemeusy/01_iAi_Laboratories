% cloudPoint_decoder.m--
%
% Syntax:
%
% e.g.,

% Developed in Matlab 9.7.0.1190202 (R2019b) on PCWIN64.
% JDU - Jean Demeusy (jean.demeusy@heig-vd.ch), 2019-11-07 16:05
%-------------------------------------------------------------------------

%% Setup
close all;
clear;
clc;

%% Variable
pcd = load("20191108T113836/41_ProcessedXYZ.pcd", '-ascii');
img_int = imread("20191108T113836/4_intensity.png");
img_range = imread("20191108T113836/4_range.png");

tab = zeros(numel(img_range),3);

%% Code
img_int = double(img_int)/(2^16-1);
j_mapped = xmap(0:size(img_int,2)-1,0,1000);
k_mapped = xmap(0:size(img_int,1)-1,0,1000);

for k = 1:size(img_range,1)
    for j = 1:size(img_range,2)
        tab((k-1)*size(img_range,2) + j,:) = [j_mapped(j),k_mapped(k),img_int(k,j)];
    end
end
tab = tab(randperm(size(tab, 1)), :);

%% Display
ximshow(img_int,img_range);

% fid = fopen('myTextFile.txt','wt');
% if fid > 0
%     fprintf(fid,"x y value\n");
%     fprintf(fid,"%f %f %f\n",tab');
%     fclose(fid);
% end