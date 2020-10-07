% PCD_decoder.m--
%
% Syntax:
%
% e.g.,

% Developed in Matlab 9.7.0.1190202 (R2019b) on PCWIN64.
% JDU - Jean Demeusy (jean.demeusy@heig-vd.ch), 2019-11-07 11:17
%-------------------------------------------------------------------------

%% Setup
close all;
clear;
clc;

%% Variable
pcd = pcread("20191107T191549\1_ProcessedXYZ.pcd");
loc = pcd.Location;
img = loc(:,:,3);

sizeY = size(img,1);
sizeX = size(img,2);
enableMask = true;
seuil = 200;
b_size = 80;
box_b_size = 10;

%% Code
img = img(b_size:end-b_size,b_size:end-b_size);
bin = img < 1.94;
area = sum(bin);

stats = regionprops(bin, 'BoundingBox');
BBox = round(stats(1).BoundingBox);

box_img = img(BBox(2)+(1:BBox(4)),BBox(1)+(1:BBox(3)));
box_img = box_img(box_b_size:end-box_b_size,box_b_size:end-box_b_size);

[min_c,min_r] = ind2sub(size(box_img),find(box_img == min(box_img(:))));
[max_c,max_r] = ind2sub(size(box_img),find(box_img == max(box_img(:))));

min_r = min_r + box_b_size + BBox(1);
max_r = max_r + box_b_size + BBox(1);
min_c = min_c + box_b_size + BBox(2);
max_c = max_c + box_b_size + BBox(2);

BBox = BBox + [b_size b_size 0 0];
img = xmap(img,1000,0);
box_img = xmap(box_img,1000,0);


x_pos1 = loc(BBox(2),BBox(1),1);
x_pos2 = loc(BBox(2)+BBox(4),BBox(1)+BBox(3),1);
width = round((x_pos1-x_pos2) * 100,1);

y_pos1 = loc(BBox(2),BBox(1),2);
y_pos2 = loc(BBox(2)+BBox(4),BBox(1)+BBox(3),2);
height = round((y_pos1-y_pos2) * 100,1);

z_pos1 = loc(BBox(2)-10,BBox(1)-10,3);
z_pos2 = loc(BBox(2)+10,BBox(1)+10,3);
depth = round((z_pos1-z_pos2) * 100,1);

%% Display
% subplot(1,2,2);
% imshow(img',[]); view(90,90); hold on; axis equal; 
% plot(min_c,min_r,'.g','Markersize',20);
% plot(max_c,max_r,'.r','Markersize',20);

% subplot(1,2,1); 
imshow(loc(:,:,3),[]);colormap("gray");
rectangle('Position',BBox,'EdgeColor','b','LineWidth',1 );
title("size: " + num2str(width) + " x " + num2str(height) + " x " + num2str(depth) + "cm");

