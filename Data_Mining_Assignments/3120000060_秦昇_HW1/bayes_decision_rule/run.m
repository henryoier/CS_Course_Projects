% You can use this skeleton or write your own.
% You are __STRONGLY__ suggest to run this script section-by-section using Ctrl+Enter.
% See http://www.mathworks.cn/cn/help/matlab/matlab_prog/run-sections-of-programs.html for more details.

%% Load data
load('data');
all_x = cat(2, x1_train, x1_test, x2_train, x2_test);
range = [min(all_x), max(all_x)];
train_x = get_x_distribution(x1_train, x2_train, range);
test_x = get_x_distribution(x1_test, x2_test, range);

%% Part1 likelihood: 
l = likelihood(train_x);

bar(range(1):range(2), l');
xlabel('x');
ylabel('P(x|\omega)');
axis([range(1) - 1, range(2) + 1, 0, 0.5]);

% Your code HERE
% Compute the number of all the misclassified x using maximum likelihood decision rule
[C, N] = size(l);
mis = 0;
for n=1:N
    if l(1,n)>l(2,n)
        mis = mis + test_x(2,n);
    else
        mis = mis + test_x(1,n);
    end
end
total = sum(sum(test_x));
mis = mis/total;
mis

%% Part2 posterior:
p = posterior(train_x);

bar(range(1):range(2), p');
xlabel('x');
ylabel('P(\omega|x)');
axis([range(1) - 1, range(2) + 1, 0, 1.2]);

% Your code HERE
% Compute the number of all the misclassified x using optimal bayes decision rule
[C, N] = size(p);
mis = 0;
for n=1:N
    if p(1,n)>p(2,n)
        mis = mis + test_x(2,n);
        mis
    else
        mis = mis + test_x(1,n);
        mis
    end
end
mis = mis/total;
mis
%% Part3 risk:
risk = [0, 1; 2, 0];
% Your code HERE
% Compute conditinal risk over all the x using optimal bayes decision rules and risk weights
riskn = 0;
[C, N] = size(p);
for n=1:N
    if p(1,n)>p(2,n)
        riskn = riskn + test_x(2,n);
    else
        riskn = riskn + test_x(1,n)*2;
    end
end
riskn