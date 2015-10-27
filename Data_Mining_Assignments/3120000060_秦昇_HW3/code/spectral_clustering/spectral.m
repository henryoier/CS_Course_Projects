function idx = spectral(W, k)
%SPECTRUAL spectral clustering
%   Input:
%     W: Adjacency matrix, N-by-N matrix
%     k: number of clusters
%   Output:
%     idx: data point cluster labels, n-by-1 vector.

% YOUR CODE HERE
D=diag(sum(W,2));
L=D-W;
[Q, V] = eigs(L, k, 'SA');
idx = kmeans(Q, k);
end
