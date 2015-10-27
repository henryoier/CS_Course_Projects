function y = knn(X, X_train, y_train, K)
%KNN k-Nearest Neighbors Algorithm.
%
%   INPUT:  X:         testing sample features, P-by-N_test matrix.
%           X_train:   training sample features, P-by-N matrix.
%           y_train:   training sample labels, 1-by-N row vector.
%           K:         the k in k-Nearest Neighbors
%
%   OUTPUT: y    : predicted labels, 1-by-N_test row vector.
%

% YOUR CODE HERE
distances=EuDist2(X', X_train');
[value, index]=sort(distances, 2);
[P, N_test]=size(X);
count=zeros(10, N_test);
for testI=1:N_test
	if(K~=1)
		for trainI=1:K
			label=y_train(:,index(testI, trainI));
			count(label+1, testI)=count(label+1, testI)+1;
		end
	else
		y(:, testI)=y_train(:, index(testI, 1));
	end
end	
if(K~=1)
	[C, I]=max(count);
	for i=1:N_test
		y(:, i)=I(:, i)-1;
	end
end

end

