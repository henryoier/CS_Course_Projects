function img = hack_pca(filename)
% Input: filename -- input image file name/path
% Output: img -- image without rotation

img_r = double(imread(filename));

% YOUR CODE HERE
% get pixel coordinates
[rows, cols]=size(img_r);
data=zeros(0, 2);
for rowI=1:rows
	for colI=1:cols
		if(img_r(rowI, colI)~=255)
			data=[data; rowI, colI];
		end
	end
end

[eigVecs, eigVals]=PCA(data, 2);	% get two lines by PCA

% get new coordinates
newCoords=data*eigVecs;
newCoords=int8(newCoords);
minVal=min(newCoords);
[n, p]=size(newCoords);
for entryI=1:n
	newCoords(entryI, :)=newCoords(entryI, :)-minVal+1;
end

% create new img
maxVal=max(newCoords);
img_r=uint8(img_r);
img=zeros(0, 0);
img=uint8(img);
for entryI=1:n
	img(maxVal(2)-newCoords(entryI,2)+1, newCoords(entryI,1))=img_r(data(entryI, 1), data(entryI, 2));
end

% we do a simple linear interpolation to remove the noise
[rows, cols]=size(img);
for rowI=2:rows-1
	for colI=2:cols-1
		if(img(rowI, colI)==0)
			img(rowI, colI)=uint8((uint16(img(rowI+1, colI))+uint16(img(rowI-1, colI))+uint16(img(rowI, colI+1))+uint16(img(rowI, colI-1))+uint16(img(rowI+1, colI+1))+uint16(img(rowI-1, colI+1))+uint16(img(rowI+1, colI-1))+uint16(img(rowI-1, colI-1)))/8);
		end
	end
end


end
