#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace std;

static Mat norm_0_255(InputArray _src) {
	Mat src = _src.getMat();
	// 创建和返回一个归一化后的图像矩阵:
	Mat dst;
	switch (src.channels()) {
	case1:
		cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
		break;
	case3:
		cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
		break;
	default:
		src.copyTo(dst);
		break;
	}
	return dst;
}
//使用CSV文件去读图像和标签，主要使用stringstream和getline方法
static void read_csv(const string& filename, vector<Mat>& images, 
	                  vector<int>& labels, int num, char separator = ';') {
	std::ifstream file(filename.c_str(), ifstream::in);
	if (!file) {
		string error_message = "No valid input file was given, please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line, path, classlabel;
	int count = -1;
	while (getline(file, line)) {
		count++;
		if (count % 10 < num){
			stringstream liness(line);
			getline(liness, path, separator);
			getline(liness, classlabel);
			if (!path.empty() && !classlabel.empty()) {
				images.push_back(imread(path, 0));
				labels.push_back(atoi(classlabel.c_str()));
			}
		}
	}
}

void Eigen_Face(vector<Mat> images, vector<int> labels,string output_folder, int num){
	// 得到第一张照片的高度. 在下面对图像
	// 变形到他们原始大小时需要
	cout << "Eigenface!" << endl;
	int height = images[0].rows;

	vector<Mat> testSample;
	vector<int> testLabel;
	for (int i = num - 1; i < num*40; i += num){
		testSample.push_back(images[i]);
		testLabel.push_back(labels[i]);
	}
	for (int i = num * 40 - 1; i > 0; i -= num){
		images.erase(images.begin() + i);
		labels.erase(labels.begin() + i);
	}
	// 下面几行创建了一个特征脸模型用于人脸识别，

	Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
	model->train(images, labels);
	int right = 0;
	// 下面对测试图像进行预测，predictedLabel是预测标签结果
	for (int i = 0; i < testSample.size(); i++){
		int predictedLabel = model->predict(testSample[i]);
		string result_message = format("Predicted class %d = %d / Actual class%d = %d.",i, predictedLabel, i,testLabel[i]);
		Mat img(testSample[i]);
		if (predictedLabel == testLabel[i]){
			right++;
			char no[5];
			_itoa(i, no, 10);
			string n(no);
			string output = "Right!No." + n;
			putText(img, output, Point(10, 10), CV_FONT_HERSHEY_COMPLEX,
				0.4, Scalar(255, 255, 255));
		}
		imshow("test", img);
		cout << result_message << endl;
		// 这里是如何获取特征脸模型的特征值的例子，使用了getMat方法:
		Mat eigenvalues = model->getMat("eigenvalues");
		// 同样可以获取特征向量:
		Mat W = model->getMat("eigenvectors");
		// 得到训练图像的均值向量
		Mat mean = model->getMat("mean");

		// 现实还是保存特征脸:
		for (int i = 0; i < min(10, W.cols); i++) {
			string msg = format("Eigenvalue #%d = %.5f", i, eigenvalues.at<double>(i));
			cout << msg << endl;
		}
		
		waitKey();
	}
	// 如果我们不是存放到文件中，就显示他，这里使用了暂定等待键盘输入:
	cout << "Accuracy = " << (float)right / 40 << endl;
}

void FisherFace(vector<Mat> images, vector<int> labels, string output_folder, int num)
{
	cout << "Fisherface!" << endl;
	int height = images[0].rows;

	vector<Mat> testSample;
	vector<int> testLabel;
	for (int i = num - 1; i < num * 40; i += num){
		testSample.push_back(images[i]);
		testLabel.push_back(labels[i]);
	}
	for (int i = num * 40 - 1; i > 0; i -= num){
		images.erase(images.begin() + i);
		labels.erase(labels.begin() + i);
	}

	Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
	model->train(images, labels);

	int right = 0;
	for (int i = 0; i < testSample.size(); i++){
		int predictedLabel = model->predict(testSample[i]);
		string result_message = format("Predicted class %d = %d / Actual class%d = %d.", i, predictedLabel, i, testLabel[i]);
		Mat img(testSample[i]);
		if (predictedLabel == testLabel[i]){
			right++;
			char no[5];
			_itoa(i, no, 10);
			string n(no);
			string output = "Right!No." + n;
			putText(img, output, Point(10, 10), CV_FONT_HERSHEY_COMPLEX, 
				      0.4, Scalar(255, 255, 255));
		}
		imshow("test", img);
		cout << result_message << endl;

		Mat eigenvalues = model->getMat("eigenvalues");
		Mat W = model->getMat("eigenvectors");
		Mat mean = model->getMat("mean");

		//显示还是保存, 最多16 Fisherfaces:
		/*for (int i = 0; i < min(16, W.cols); i++) {
			string msg = format("Eigenvalue #%d = %.5f", i, eigenvalues.at<double>(i));
			cout << msg << endl;
		}*/
		/*
		for (int num_component = 0; num_component < min(16, W.cols); num_component++) {
		Mat ev = W.col(num_component);
		Mat projection = subspaceProject(ev, mean, images[0].reshape(1, 1));
		Mat reconstruction = subspaceReconstruct(ev, mean, projection);
		reconstruction = norm_0_255(reconstruction.reshape(1, images[0].rows));

		imwrite(format("%s/fisherface_reconstruction_%d.png", output_folder.c_str(), num_component), reconstruction);
		}*/
		waitKey();
	}
	// 如果我们不是存放到文件中，就显示他，这里使用了暂定等待键盘输入:
	cout << "Accuracy = " << (float)right / 40 << endl;
}

int main(int argc, const char*argv[]) {

	//读取你的CSV文件路径.
	string fn_csv = "at.csv";

	// 2个容器来存放图像数据和对应的标签
	vector<Mat> images;
	vector<int> labels;
	// 读取数据. 如果文件不合法就会出错
	// 输入的文件名已经有了.
	try {
		read_csv(fn_csv, images, labels, 10);
	}
	catch (cv::Exception& e) {
		cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
		// 文件有问题，我们啥也做不了了，退出了
		exit(1);
	}
	// 如果没有读取到足够图片，我们也得退出.
	if (images.size() <= 1) {
		string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
		CV_Error(CV_StsError, error_message);
	}
	
	Eigen_Face(images, labels, "Eigenface",10);
	FisherFace(images, labels, "Eigenface", 10);
	return 0;
}