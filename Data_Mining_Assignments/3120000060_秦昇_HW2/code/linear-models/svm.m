function [w, num] = svm(X, y)
%SVM Support vector machine.
%
%   INPUT:  X: training sample features, P-by-N matrix.
%           y: training sample labels, 1-by-N row vector.
%
%   OUTPUT: w:    learned perceptron parameters, (P+1)-by-1 column vector.
%           num:  number of support vectors
%

% YOUR CODE HERE
[P, N]=size(X);
H=eye(P+1);
f=zeros(P+1, 1);
A=[ones(N,1), X'];
for i=1:N
	A(i,:)=-y(:,i)*A(i,:);
end
B=-ones(N,1);
w=quadprog(H,f,A,B);
result=A*w;
num=size(find(abs(result)<=1+1e-8),1);
end
