img = imread('sample0.jpg');
fea = double(reshape(img, size(img, 1)*size(img, 2), 3));
% YOUR (TWO LINE) CODE HERE
[n, p]=size(fea)
[idx, ctrs, iter_ctrs]=kmeans(fea, 8);
for i=1:n
    fea(i,:)=ctrs(idx(i),:);
end
imshow(uint8(reshape(fea, size(img))));
