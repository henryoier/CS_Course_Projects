#include <opencv/cv.h>   
#include <opencv/highgui.h>   
#include <math.h>   
#include <iostream>   

using namespace std;
using namespace cv;

int Otsu(Mat& src)
{
	int height = src.rows;
	int width = src.cols;

	//histogram    
	float histogram[256] = { 0 };
	for (int i = 0; i < src.rows; i++)
	for (int j = 0; j < src.cols; j++){
		histogram[src.at<uchar>(i, j)]++;
	}
	//normalize histogram    
	int size = height * width;
	for (int i = 0; i < 256; i++)
	{
		histogram[i] = histogram[i] / size;
	}

	//average pixel value    
	float avgValue = 0;
	for (int i = 0; i < 256; i++)
	{
		avgValue += i * histogram[i];  //����ͼ���ƽ���Ҷ�  
	}

	int threshold;
	float maxVariance = 0;
	float w = 0, u = 0;
	for (int i = 0; i < 256; i++)
	{
		w += histogram[i];  //���赱ǰ�Ҷ�iΪ��ֵ, 0~i �Ҷȵ�����(��������ֵ�ڴ˷�Χ�����ؽ���ǰ������) ��ռ����ͼ��ı���  
		u += i * histogram[i];  // �Ҷ�i ֮ǰ������(0~i)��ƽ���Ҷ�ֵ�� ǰ�����ص�ƽ���Ҷ�ֵ  

		float t = avgValue * w - u;
		float variance = t * t / (w * (1 - w));
		if (variance > maxVariance)
		{
			maxVariance = variance;
			threshold = i;
		}
	}

	return threshold;
}

int main()
{
	//Step1: Load image to src and Show source image   

	Mat source = imread("cell3.jpg", CV_LOAD_IMAGE_COLOR);
	imshow("Source image", source);

	//Step 2:Get gray graph of source image.   
	Mat gray;
	cvtColor(source, gray, CV_RGB2GRAY);
	imshow("Gray image", gray);

	//Step 3:Get background color   
	int thresholdn = Otsu(gray);
	Mat bin;
	threshold(gray, bin, thresholdn, 255, CV_THRESH_BINARY);

	for (int i = 0; i < bin.rows; i++)
	{
		for (int j = 1; j < 3; j++){
			bin.at<uchar>(i, j - 1) = 255;
			bin.at<uchar>(i, bin.cols - j) = 255;
		}
	}

	for (int i = 0; i < bin.cols; i++)
	{
		for (int j = 1; j < 3; j++){
			bin.at<uchar>(j - 1, i) = 255;
			bin.at<uchar>(bin.rows - j, i) = 255;
		}
	}
	
	imshow("binary", bin);

	//the pram. for findContours,  
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	Mat cont = Mat::zeros(bin.size(), CV_8UC1);
	Mat ellp = Mat::zeros(bin.size(), CV_8UC1);
	findContours(bin, contours, hierarchy,
		CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));


	//for (vector <vector<Point>>::iterator iter = contours.begin(); iter != contours.end(); iter++)
	
	bool *hash = new bool[contours.size()];
	memset(hash, true, sizeof(hash));
	int counter = contours.size();

	for (int i = 0; i < contours.size(); i++)
	if ((hierarchy[i][3] == -1) || (hierarchy[i][3] != 0)){
		hash[i] = false;
		counter --;
	}

	int *area = new int[contours.size()];
	int totalarea = 0;

	for (int i = 0; i < contours.size(); i++){
		if (hash[i]){
			area[i] = contourArea(contours[i]);
			totalarea += area[i];
		}
	}

	int average = totalarea / counter;

	int minarea = cont.rows*cont.cols, maxarea = 0, mini, maxi;
	for (int i = 0; i < contours.size(); i++){
		if (hash[i])
			if (area[i]<average * 0.3){
				hash[i] = false;
				counter--;
			}
			else{
				if (area[i]<minarea){
					minarea = area[i];
					mini = i;
				}
				if (area[i]>maxarea){
					maxarea = area[i];
					maxi = i;
				}
			}
	}

	totalarea = 0;
	cout << "��ͼ��һ����" << counter << "��ϸ��" << endl;
	//drawContours(cont, contours, 0, 255, 1, 8, hierarchy, 0, Point());
	for (int i = 0; i < contours.size();i++){
		int count = contours[i].size();
		if (count < 6)
			continue;
		if (hash[i]){
			totalarea += area[i];
			CvPoint center;
			CvSize size;
			CvBox2D32f* box;
			CvPoint* PointArray;
			CvPoint2D32f* PointArray2D32f;

			PointArray = (CvPoint*)malloc(count*sizeof(CvPoint));
			PointArray2D32f = (CvPoint2D32f*)malloc(count*sizeof(CvPoint2D32f));

			// Alloc memory for ellipse data.   
			box = (CvBox2D32f*)malloc(sizeof(CvBox2D32f));


			// Convert CvPoint set to CvBox2D32f set.   
			for (int j = 0; j<count;j++){
				PointArray2D32f[j].x = (float)contours[i][j].x;
				PointArray2D32f[j].y = (float)contours[i][j].y;
			}

			// Fits ellipse to current contour.   
			cvFitEllipse(PointArray2D32f, count, box);

			// Convert ellipse data from float to integer representation.   

			center.x = cvRound(box->center.x);
			center.y = cvRound(box->center.y);
			size.width = cvRound(box->size.width*0.5);
			size.height = cvRound(box->size.height*0.5);

			drawContours(cont, contours, i, 255);
			ellipse(ellp, center, size, box->angle, 0, 360, 255, 1, CV_AA, 0);


			if (i == mini)
			cout << "��Сϸ�����Ϊ" << area[i] << ',' << "�ܳ���" << count << ','
				<< "������X+��ɣ�" << 180 - box->angle << "�Ƚ�," << "����" << '(' << center.x << ',' << center.y << ");"<<endl;
			if (i == maxi)
				cout << "���ϸ�����Ϊ" << area[i] << ',' << "�ܳ���" << count << ','
				<< "������X+��ɣ�" << 180 - box->angle << "�Ƚ�," << "����" << '(' << center.x << ',' << center.y << ");" << endl;
			// Free memory.             
			free(PointArray);
			free(PointArray2D32f);
			free(box);
		}
	}

	imshow("Contours", cont);
	imshow("Ellipse", ellp);
	cout << "ƽ�����:" << totalarea/counter << endl;
	waitKey(-1);
	return 0;
}