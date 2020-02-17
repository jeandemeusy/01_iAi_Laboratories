% convex_hull.m--
%
% Syntax:
%
% e.g.,

% Developed in Matlab 9.7.0.1190202 (R2019b) on PCWIN64.
% JDU - Jean Demeusy (jean.demeusy@heig-vd.ch), 2019-11-14 08:34
%-------------------------------------------------------------------------

function [L_hull,L_ens] = convex_hull(L_ens)
dist_to_origin = L_ens(:,1).^2 + L_ens(:,2).^2;
[~,index_p0] = min(dist_to_origin);

p0 = L_ens(index_p0,:);
L_ens(index_p0,:) = [];

data(:,1) = atan2(L_ens(:,2)-p0(2),L_ens(:,1)-p0(1));
data(:,2) = (L_ens(:,2)-p0(2)).^2 + (L_ens(:,1)-p0(1)).^2;

[~,sortIdx] = sortrows(data,[1 2], {'descend' 'ascend'} );
L_ens = L_ens(sortIdx,:);

L_hull(1,:) = p0;
L_hull(2,:) = L_ens(1,:);
treated = 2;

while treated < length(L_ens) + 1
    pi = L_hull(end-1,:);
    pj = L_hull(end,:);
    pk = L_ens(treated,:);
    
    a = cross([pj - pi, 0],[pk - pj, 0]);
    if (a(3) < 0)
        L_hull(end+1,:) = pk;
        treated = treated + 1;
    elseif (a(3) > 0)
        L_hull(end,:) = [];
    else
        L_hull(end,:) = pk;
        treated = treated + 1;
    end
end

L_ens(2:end+1,:) = L_ens(:,:);
L_ens(1,:) = p0;
L_hull(end+1,:) = p0;
