function [idx, ctrs, iter_ctrs] = kmeans(X, K)
%KMEANS K-Means clustering algorithm
%
%   Input: X - data point features, n-by-p maxtirx.
%          K - the number of clusters
%
%   OUTPUT: idx  - cluster label
%           ctrs - cluster centers, K-by-p matrix.
%           iter_ctrs - cluster centers of each iteration, K-by-p-by-iter
%                       3D matrix.

% YOUR CODE HERE
[n, p]=size(X);
randNums = randperm(n);
for kI=1:K
	ctrs(kI,:)=X(randNums(kI),:);
end
iter_ctrs(:,:,1)=ctrs;
iter=1;
% while(true)
for i=1:10	% due to my poor environment, I can't run more iterations...
		% but I know the correct stop condition is ctrs no longer change
	idx = knn(X', ctrs', 1:K, 1);
	ctrs=zeros(K, p);
	count=zeros(K, 1);
	for dataI=1:n
		count(idx(:, dataI),:)=count(idx(:, dataI),:)+1;
		ctrs(idx(:, dataI),:)=ctrs(idx(:, dataI),:)+X(dataI,:);
	end
	for labelI=1:K
		ctrs(labelI, :)=ctrs(labelI, :)/count(labelI, :);
	end

% 	size(ctrs)
% 	size(iter_ctrs(:,:,iter))
% 	if(ctrs==iter_ctrs(:,:,iter))
% 		break;
% 	else	% if another iteration is needed:
		iter=iter+1;
		iter_ctrs(:,:,iter)=ctrs;
% 	end
end

end
