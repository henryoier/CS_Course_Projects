function p = posterior(x)
%POSTERIOR Two Class Posterior Using Bayes Formula
%
%   INPUT:  x, features of different class, C-By-N vector
%           C is the number of classes, N is the number of different feature
%
%   OUTPUT: p,  posterior of each class given by each feature, C-By-N matrix
%

[C, N] = size(x);
l = likelihood(x);
total = sum(sum(x));
% Your code HERE
p = zeros(C,N);
px = zeros(1,N);
prior = zeros(2,1);
px = x(1,:)+x(2,:);
px = px./total;
px
prior = [sum(x(1,:)),sum(x(2,:))]./total;
p(1,:) = (l(1,:)./px(1,:))*prior(1);
p(2,:) = (l(2,:)./px(1,:))*prior(2);
end
