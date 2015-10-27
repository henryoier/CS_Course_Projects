load('ORL_data', 'fea_Train', 'gnd_Train', 'fea_Test', 'gnd_Test');

% YOUR CODE HERE

% 1. Feature preprocessing

%% 2. Run PCA
[eigVecs, eigVals]=PCA(fea_Train, 64);

%% 3. Visualize eigenface
 show_face(eigVecs');

%% 4. Project data on to low dimensional space
trainLow=fea_Train*eigVecs;
testLow=fea_Test*eigVecs;

%% 5. Run KNN in low dimensional space
% result=knn(testLow', trainLow', gnd_Train', 1)
% errorRate=0;
% [p, n]=size(result);
% for i=1:n
%     if(result(i)~=gnd_Test(i))
%         errorRate=errorRate+1;
%     end
% end
% errorRate=errorRate/n

%% 6. Recover face images form low dimensional space, visualize them
recovered=eigVecs*trainLow';
recovered=recovered';
show_face([fea_Train(1:20,:);recovered(1:20,:)])