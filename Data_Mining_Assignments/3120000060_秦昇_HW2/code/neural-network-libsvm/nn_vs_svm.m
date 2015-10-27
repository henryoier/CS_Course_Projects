load('digit_data', 'X', 'y');
load('weights', 'Theta1', 'Theta2');

p = feedforward(Theta1, Theta2, X);
fprintf('Error rate for NN is %f.\n', length(find(p ~= y))/length(p));

train_X = X(:, 1:2500);
train_y = y(1:2500);
test_X = X(:, 2501:end);
test_y = y(2501:end);

% YOUR CODE HERE
% Trainning and testing using one-vs-all with LIBLINEAR

% train 10 binary classifiers:
for classI=1:10
	for sampleI=1:2500
		if(train_y(sampleI)==classI)
			train_y_bin(sampleI)=1;
		else
			train_y_bin(sampleI)=0;
		end
	end
	model(classI)=train(train_y_bin', sparse(train_X)');
end

% predict and calculate test error rate:
prob_estimates=zeros(2500, 10);
predicted_label=zeros(2500, 1);
for classI=1:10
    [predicted_label, accuracy, prob_estimates(:,classI)]=predict(test_y', sparse(test_X)', model(classI));
end

nError=0;
for pointI=1:2500
    maxLabel=1;
    for classI=2:10
        if(prob_estimates(pointI, classI)>prob_estimates(pointI, maxLabel))
            maxLabel=classI;
        end
    end
    if(test_y(:,pointI)~=maxLabel)
        nError=nError+1;
    end
end
errorRate=nError/2500