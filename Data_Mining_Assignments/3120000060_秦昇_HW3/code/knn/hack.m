function hack = hack(img_name)
%HACK Recognize a CAPTCHA image
%   Inputs:
%       img_name: filename of image
%   Outputs:
%       digits: 1x5 matrix, 5 digits in the input CAPTCHA image.

load('hack_data', 'trainX', 'trainY');
% YOUR CODE HERE
testX=extract_image(img_name);
testX=double(testX);
hack=knn(testX,trainX,trainY,2);
end
