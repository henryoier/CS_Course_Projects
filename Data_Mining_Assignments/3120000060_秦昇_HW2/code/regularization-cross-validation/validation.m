%% Ridge Regression
load('digit_train', 'X', 'y');

% Do feature normalization
[P, N]=size(X);
u=mean(X,2);
for i=1:N
	X(:,i)=X(:,i)-u;
end
sigma=sqrt(diag(cov(X')));
trainX=ones(1,N);

[P_test, N_test]=size(X_test);
u_test=mean(X_test,2);
for i=1:N_test
	X_test(:,i)=X_test(:,i)-u_test;
end
sigma_test=sqrt(diag(cov(X_test')));
testX=ones(1,N_test);

for i=1:P
    if(sigma(i,:)==0)
        continue; %eliminate rows that are all 0s
    end
    %X(i,:)=X(i,:)/sigma(i,:);
    trainX=[trainX; X(i,:)/sigma(i,:)];
    testX=[testX; X_test(i,:)/sigma_test(i,:)];
end
X=trainX(2:end,:);
X_test=testX(2:end,:);

% Do LOOCV
lambdas = [1e-3, 1e-2, 1e-1, 0, 1, 1e1, 1e2, 1e3];
valiError = zeros(size(lambdas));
lambda = 1;

for i = 1:length(lambdas)
   for j = 1:size(X, 2)
       X_train = [X(:,1:(j-1)), X(:,(j+1):N)]; y_train = [y(:,1:(j-1)), y(:,(j+1):N)]; % take point j out of X
       w = ridge(X_train, y_train, lambdas(i));
       valiError(:,i) = valiError(:,i) + (w'*[1; X(:,j)]-y(:,j))^2
   end
   % Update lambda according validation error
   if(valiError(:,lambda)>valiError(:,i))
       lambda=i;
   end
end
lambda=lambdas(:,lambda)


% chosen lambda:
w = ridge(X, y, lambda);
wTw_chosen=w'*w


% Compute training error
trainError=0;
result=w'*[ones(1,N); X];
for i=1:N
    if(result(:,i)*y(:,i)<=0)
        trainError=trainError+1;
    end
end
trainErrorRate=trainError/N

load('digit_test', 'X_test', 'y_test');

% Compute test error
testError=0;
result=w'*[ones(1,N_test); X_test];
for i=1:N_test
    if(result(:,i)*y_test(:,i)<=0)
        testError=testError+1;
    end
end
testErrorRate=testError/N_test


% lambda=0:
w = ridge(X, y, 0);
wTw0=w'*w


% Compute training error
trainError=0;
result=w'*[ones(1,N); X];
for i=1:N
    if(result(:,i)*y(:,i)<=0)
        trainError=trainError+1;
    end
end
trainErrorRate0=trainError/N


% Compute test error
testError=0;
result=w'*[ones(1,N_test); X_test];
for i=1:N_test
    if(result(:,i)*y_test(:,i)<=0)
        testError=testError+1;
    end
end
testErrorRate0=testError/N_test

%% Logistic

%% SVM with slack variable
