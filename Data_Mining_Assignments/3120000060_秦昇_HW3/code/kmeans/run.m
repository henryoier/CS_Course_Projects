%% Part1: Kmeans for points
load('kmeans_data.mat','X');
SD=zeros(1,1000);
[n, p]=size(X);
for testI=1:1000
    [idx(:,:,testI), ctrs(:,:,testI), iter_ctrs(:,:,:,testI)]=kmeans(X, 2);
    distances=EuDist2(X, ctrs(:,:,testI));
    for dataI=1:n
        SD(:, testI)=SD(:, testI)+distances(dataI,idx(:,dataI, testI));
    end
end
%[C, maxTest]=max(SD);
[C, minTest]=min(SD);
minSD=SD(:,minTest)
kmeans_plot(X, idx(:,:,minTest), ctrs(:,:,minTest), iter_ctrs(:,:,:,minTest));
%maxSD=SD(:,maxTest)
%kmeans_plot(X, idx(:,:,maxTest), ctrs(:,:,maxTest), iter_ctrs(:,:,:,maxTest));

%% Part2: Kmeans for digit
load('digit_data.mat', 'X');
kVal = 50;
[idx, ctrs, iter_ctrs]=kmeans(X, kVal);
show_digit(ctrs);

    