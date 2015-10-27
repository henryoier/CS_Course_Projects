% You can use this skeleton or write your own.
% You are __STRONGLY__ suggest to run this script section-by-section using Ctrl+Enter.
% See http://www.mathworks.cn/cn/help/matlab/matlab_prog/run-sections-of-programs.html for more details.

%% Part1: Preceptron
nRep = 1000  % number of replicates
nTrain = 100  % number of training data
nTest = 1000 % number of testing data
nError = 0;  % sum of testing errors in nRep of replicates
iterSum = 0; % sum of iteration times in nRep of replicates

for i = 1:nRep
    % create both training and testing data:
    [X, y, w_f] = mkdata(nTrain+nTest);
    % train
    [w_g, iter] = perceptron(X(:,1:nTrain), y(:,1:nTrain));
    % count testing errors:
    x=[ones(1, nTest); X(:,(nTrain+1):(nTrain+nTest))];
    result=w_g'*x;
    for sampleI=1:nTest
      if(result(:,sampleI)*y(:,nTrain+sampleI)<=0)
          nError=nError+1;
      end
    end
    % Sum up number of iterations:
    iterSum=iterSum+iter;
end
%compute testing error:
testErrorRateMean=nError/nRep/nTest
%comupte mean iteration times:
iterMean=iterSum/nRep

%fprintf('E_train is %f, E_test is %f.\n', E_train, E_test);
%fprintf('Average number of iterations is %d.\n', avgIter);
% plot data and learned and actual classification plane in the last nRep:
plotdata(X, y, w_f, w_g, 'Pecertron');


%% Part2: Preceptron: Non-linearly separable case
nTrain = 100; % number of training data
[X, y, w_f] = mkdata(nTrain, 'noisy');
[w_g, iter] = perceptron(X, y);


%% Part3: Linear Regression
nRep = 1000 % number of replicates
nTrain = 100 % number of training data
nTest = 1000 % number of testing data
trainError = 0;
testError = 0;

for i = 1:nRep
    [X, y, w_f] = mkdata(nTrain+nTest);
    w_g = linear_regression(X(:, 1:nTrain), y(:, 1:nTrain));
    % Compute training, testing error
    result=w_g'*[ones(1,nTrain+nTest); X];
    for sampleI=1:nTrain
        if(result(:,sampleI)*y(:,sampleI)<=0)
            trainError=trainError+1;
        end
    end
    for sampleI=(nTrain+1):(nTrain+nTest)
        if(result(:,sampleI)*y(:,sampleI)<=0)
            testError=testError+1;
        end
    end
end
trainError=trainError/nRep/nTrain
testError=testError/nRep/nTest

%fprintf('E_train is %f, E_test is %f.\n', E_train, E_test);
plotdata(X, y, w_f, w_g, 'Linear Regression');


%% Part4: Linear Regression (noisy)
nRep = 1000 % number of replicates
nTrain = 100 % number of training data
nTest = 1000 % number of testing data
trainError = 0;
testError = 0;

for i = 1:nRep
    [X, y, w_f] = mkdata(nTrain+nTest, 'noisy');
    w_g = linear_regression(X(:, 1:nTrain), y(:, 1:nTrain));
    % Compute training, testing error
    result=w_g'*[ones(1,nTrain+nTest); X];
    for sampleI=1:nTrain
        if(result(:,sampleI)*y(:,sampleI)<=0)
            trainError=trainError+1;
        end
    end
    for sampleI=(nTrain+1):(nTrain+nTest)
        if(result(:,sampleI)*y(:,sampleI)<=0)
            testError=testError+1;
        end
    end
end
trainError=trainError/nRep/nTrain
testError=testError/nRep/nTest

%fprintf('E_train is %f, E_test is %f.\n', E_train, E_test);
plotdata(X, y, w_f, w_g, 'Linear Regression: noisy');

 
%% Part5: Linear Regression: poly_fit
load('poly_train', 'X', 'y');
load('poly_test', 'X_test', 'y_test');
[P, nTrain] = size(X) % number of training data
[P, nTest] = size(X_test) % number of testing data
trainError = 0;
testError = 0;

w_g = linear_regression(X, y);
% Compute training, testing error
trainResult=w_g'*[ones(1,nTrain); X];
testResult=w_g'*[ones(1,nTest); X_test];
for sampleI=1:nTrain
    if(trainResult(:,sampleI)*y(:,sampleI)<=0)
        trainError=trainError+1;
    end
end
for sampleI=1:nTest
     if(testResult(:,sampleI)*y_test(:,sampleI)<=0)
        testError=testError+1;
    end
end
trainError=trainError/nTrain
testError=testError/nTest

%fprintf('E_train is %f, E_test is %f.\n', E_train, E_test);
plotdata(X, y, w_f, w_g, 'Linear Regression: poly_fit without transform');

%% Part5_2: poly_fit with transform
load('poly_train', 'X', 'y');
load('poly_test', 'X_test', 'y_test');
[P, nTrain] = size(X) % number of training data
[P, nTest] = size(X_test) % number of testing data

trainAdd = zeros(3, nTrain);
for sampleI=1:nTrain
    trainAdd(1,sampleI)=X(1,sampleI)*X(2,sampleI);
    trainAdd(2,sampleI)=X(1,sampleI)*X(1,sampleI);
    trainAdd(3,sampleI)=X(2,sampleI)*X(2,sampleI);
end
X_chart=X;
X=[X;trainAdd];

testAdd = zeros(3, nTest);
for sampleI=1:nTest
    testAdd(1,sampleI)=X_test(1,sampleI)*X_test(2,sampleI);
    testAdd(2,sampleI)=X_test(1,sampleI)*X_test(1,sampleI);
    testAdd(3,sampleI)=X_test(2,sampleI)*X_test(2,sampleI);
end
X_test=[X_test;testAdd];
    
trainError = 0;
testError = 0;

w_g = linear_regression(X, y);
% Compute training, testing error
trainResult=w_g'*[ones(1,nTrain); X];
testResult=w_g'*[ones(1,nTest); X_test];
for sampleI=1:nTrain
    if(trainResult(:,sampleI)*y(:,sampleI)<=0)
        trainError=trainError+1;
    end
end
for sampleI=1:nTest
     if(testResult(:,sampleI)*y_test(:,sampleI)<=0)
        testError=testError+1;
    end
end
trainError=trainError/nTrain
testError=testError/nTest

%fprintf('E_train is %f, E_test is %f.\n', E_train, E_test);


% %% Part6: Logistic Regression
% nRep = 100; % number of replicates
% nTrain = 100; % number of training data
% 
% for i = 1:nRep
%     [X, y, w_f] = mkdata(nTrain);
%     w_g = logistic(X, y);
%     % Compute training, testing error
% end
% 
% %fprintf('E_train is %f, E_test is %f.\n', E_train, E_test);
% plotdata(X, y, w_f, w_g, 'Logistic Regression');


% %% Part7: Logistic Regression: noisy
% nRep = 100; % number of replicates
% nTrain = 100; % number of training data
% nTest = 10000; % number of training data
% 
% for i = 1:nRep
%     [X, y, w_f] = mkdata(nTrain, 'noisy');
%     w_g = logistic(X, y);
%     % Compute training, testing error
% end
% 
% %fprintf('E_train is %f, E_test is %f.\n', E_train, E_test);
% plotdata(X, y, w_f, w_g, 'Logistic Regression: noisy');


%% Part8: SVM
nRep = 100 % number of replicates
nTrain = 100 % number of training data
nTest = 1000 % number of testing data
trainError = 0;
testError = 0;
numMean = 0;

for i = 1:nRep
    [X, y, w_f] = mkdata(nTrain+nTest);
    [w_g, num] = svm(X(:, 1:nTrain), y(:, 1:nTrain));
    % Compute training, testing error
    result=w_g'*[ones(1,nTrain+nTest); X];
    for sampleI=1:nTrain
        if(result(:,sampleI)*y(:,sampleI)<=0)
            trainError=trainError+1;
        end
    end
    for sampleI=(nTrain+1):(nTrain+nTest)
        if(result(:,sampleI)*y(:,sampleI)<=0)
            testError=testError+1;
        end
    end
    numMean=numMean+num;
end
numMean=numMean/nRep
trainError=trainError/nRep/nTrain
testError=testError/nRep/nTest

%fprintf('E_train is %f, E_test is %f.\n', E_train, E_test);
plotdata(X, y, w_f, w_g, 'SVM');
