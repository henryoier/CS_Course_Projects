% label
trainY=[ %training
    4,0,0,5,7,
    3,3,5,4,4,
    4,6,1,3,5,
    1,3,5,8,4,
    6,5,8,7,7,
    
    0,5,3,1,6,
    2,1,3,2,5,
    2,6,4,1,6,
    6,2,3,2,7,
    6,5,1,4,1,
    
    5,4,8,1,8,
    2,1,2,5,7,
    1,0,2,4,6,
    0,7,3,5,5,
    5,8,8,7,1,
    
    3,7,0,8,3,
    8,8,6,1,8,
    1,4,6,1,7,
    5,0,5,3,8,
    6,8,0,7,5
];
testY=[ %testing
    4,2,2,6,0,
    8,7,3,1,3,
    4,0,2,2,2,
    3,6,6,7,4,
    2,4,4,5,1,
    
    4,4,5,3,4,
    0,5,2,6,8,
    3,5,4,7,5,
    0,7,6,4,6,
    7,7,0,3,4,
    
    0,3,2,7,1,
    3,8,2,0,0,
    2,1,3,7,2,
    7,5,0,3,2,
    5,7,3,1,7,
    
    5,1,8,2,7,
    4,3,8,7,7,
    8,4,6,3,1,
    2,8,0,1,1,
    3,2,3,6,0
];
trainY=reshape(trainY',1,100);
testY=reshape(testY',1,100);

% get training data
trainX=zeros(140,0);
for trainI=1:20
    filePath=['train_photo/#', num2str(trainI), '.bmp'];
    trainX=[trainX, extract_image(filePath)];
end
trainX=double(trainX);

% save training data
save('hack_data.mat', 'trainX', 'trainY'); 

% test and calculate test error
% load test data and test
result=zeros(1,0);
for testI=1:20
    filePath=['train_photo/#', num2str(testI+41), '.bmp'];
    result=[result, hack(filePath)];
end

% calculate error rate
error=0;
for i=1:100
    if(result(i)~=testY(i))
        error=error+1;
    end
end
errorRate=error/100








