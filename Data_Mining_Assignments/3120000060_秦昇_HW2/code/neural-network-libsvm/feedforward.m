function p = feedforward(Theta1, Theta2, X)
%PREDICT Predict the label of an input given a trained neural network
%
%   Input:  Theta1 -- weights between input-hidden layers, 401x25 matrix
%           Theta2 -- weights between hidden-output layers, 26x10 matrix
%                X -- test set, 400xP matrix, P is size of testing set
%
%   Output: p -- predicted labels, 1xP row vector

% Note:
% The matrix X contains the examples in columns.
% The matrices Theta1 and Theta2 contain the parameters for each unit in
% column. Specifically, the first column of Theta1 corresponds to the first
% hidden unit in the second layer.

% YOUR CODE HERE
[vdim, P]=size(X);

x=[ones(1,P); X];
mid=[ones(1,P); Theta1'*x];

for rowI=1:26
	for colI=1:P
		mid(rowI, colI)=sigmoid(mid(rowI, colI));
	end
end
result=Theta2'*mid;

% find label with max discriminant function value
p=ones(1, P);
for sampleI=1:P
	for discI=2:10
		if(result(p(:, sampleI), sampleI)<result(discI, sampleI))
			p(:, sampleI)=discI;
		end
	end
end		

end
