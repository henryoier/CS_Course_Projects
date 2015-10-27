#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<windows.h>
#include<stdlib.h>

using namespace cv;

int main(int argc, char *argv[])
{
	//打开视频文件：其实就是建立一个VideoCapture结构  
	VideoCapture capture(argv[1]); 
	    
	//获得帧率，以此建立输出文件的帧率
	double rate = capture.get(CV_CAP_PROP_FPS); 
	VideoWriter writer(argv[3], CV_FOURCC('M', 'J', 'P', 'G'), 2*rate, Size(640, 360),0);
	
	//实时显示时每两帧时间的时间间隔
	double delay = 1000 / rate;
	
	Mat frame;
	int threshold = atoi(argv[2]);

	//显示每一帧的窗口  
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
	//关闭视频文件  
	capture.release();
	writer.release();
	waitKey(0);
	return 0;
}