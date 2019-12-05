img = dlmread('dragon.csv','',1,0);
grayImg = mat2gray(img);
figure(1)
imshow(grayImg)
