#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<windows.h>
#include<stdlib.h>

using namespace cv;

int main(int argc, char *argv[])
{
	//����Ƶ�ļ�����ʵ���ǽ���һ��VideoCapture�ṹ  
	VideoCapture capture(argv[1]); 
	    
	//���֡�ʣ��Դ˽�������ļ���֡��
	double rate = capture.get(CV_CAP_PROP_FPS); 
	VideoWriter writer(argv[3], CV_FOURCC('M', 'J', 'P', 'G'), 2*rate, Size(640, 360),0);
	
	//ʵʱ��ʾʱÿ��֡ʱ���ʱ����
	double delay = 1000 / rate;
	
	Mat frame;
	int threshold = atoi(argv[2]);

	//��ʾÿһ֡�Ĵ���  
	namedWindow("Video");
	bool change = false;
	while (capture.isOpened()){
		capture >> frame;
		Mat grey;
		Mat word = cvLoadImage("word.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		cvtColor(frame, grey, CV_BGR2GRAY);

		for (int i = 0; i < grey.rows; i++)
		for (int j = 0; j < grey.cols; j++){
			if (grey.at<uchar>(i, j) > threshold)
				grey.at<uchar>(i, j) = 255;
			else
				grey.at<uchar>(i, j) = 0;
			if (word.at<uchar>(i, j) >127)
			if (change)
				grey.at<uchar>(i, j) = 255;
			else
				grey.at<uchar>(i, j) = 0;
		}
		imshow("Video", grey);
		writer << grey;
		char c = waitKey(1);
		if (c == 's')break;
		change = !change;
	}
	//�ر���Ƶ�ļ�  
	capture.release();
	writer.release();
	waitKey(0);
	return 0;
}