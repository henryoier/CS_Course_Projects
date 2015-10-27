function [w, iter] = perceptron(X, y)
%PERCEPTRON Perceptron Learning Algorithm.
%
%   INPUT:  X: training sample features, P-by-N matrix.
%           y: training sample labels, 1-by-N row vector.
%
%   OUTPUT: w:    learned perceptron parameters, (P+1)-by-1 column vector.
%           iter: number of iterations
%

% YOUR CODE HERE
lRate=0.05;	%learning rate
[P, N]=size(X);
w=randn(P, 1);
bias=randn(1, 1);
iter=0;
while(1)
	result=w'*X;
	wrong=0;
	for sampleI=1:N
		if((result(:,sampleI)+bias)*y(:,sampleI)<=0)
			w=w+lRate*y(:,sampleI)*X(:,sampleI);
			bias=bias+lRate*y(:,sampleI);
			wrong=wrong+1;
		end
	end
	if(wrong==0)
		break;
	else
		iter=iter+1;
	end
end
w=[bias; w];

end
