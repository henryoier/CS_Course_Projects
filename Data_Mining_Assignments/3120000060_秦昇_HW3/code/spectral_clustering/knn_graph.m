function W = knn_graph(X, k, threshold)
%KNN_GRAPH Construct W using KNN graph
%   Input: X - data point features, n-by-p maxtirx.
%          k - number of nn.
%          threshold - distance threshold.

% YOUR CODE HERE
distances=EuDist2(X, X);
[value, index]=sort(distances, 2);
[n, p]=size(X);
W=zeros(n,n);
for dI=1:n
	for nbI=1:k
		if(value(dI,nbI)<=threshold)
			W(dI, index(dI,nbI))=1;
			W(index(dI,nbI), dI)=1;
		end
	end
	W(dI,dI)=0;
end

end
