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
	// �����ͷ���һ����һ�����ͼ�����:
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
//ʹ��CSV�ļ�ȥ��ͼ��ͱ�ǩ����Ҫʹ��stringstream��getline����
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
	// �õ���һ����Ƭ�ĸ߶�. �������ͼ��
	// ���ε�����ԭʼ��Сʱ��Ҫ
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
	// ���漸�д�����һ��������ģ����������ʶ��

	Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
	model->train(images, labels);
	int right = 0;
	// ����Բ���ͼ�����Ԥ�⣬predictedLabel��Ԥ���ǩ���
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
		// ��������λ�ȡ������ģ�͵�����ֵ�����ӣ�ʹ����getMat����:
		Mat eigenvalues = model->getMat("eigenvalues");
		// ͬ�����Ի�ȡ��������:
		Mat W = model->getMat("eigenvectors");
		// �õ�ѵ��ͼ��ľ�ֵ����
		Mat mean = model->getMat("mean");

		// ��ʵ���Ǳ���������:
		for (int i = 0; i < min(10, W.cols); i++) {
			string msg = format("Eigenvalue #%d = %.5f", i, eigenvalues.at<double>(i));
			cout << msg << endl;
		}
		
		waitKey();
	}
	// ������ǲ��Ǵ�ŵ��ļ��У�����ʾ��������ʹ�����ݶ��ȴ���������:
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

		//��ʾ���Ǳ���, ���16 Fisherfaces:
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
	// ������ǲ��Ǵ�ŵ��ļ��У�����ʾ��������ʹ�����ݶ��ȴ���������:
	cout << "Accuracy = " << (float)right / 40 << endl;
}

int main(int argc, const char*argv[]) {

	//��ȡ���CSV�ļ�·��.
	string fn_csv = "at.csv";

	// 2�����������ͼ�����ݺͶ�Ӧ�ı�ǩ
	vector<Mat> images;
	vector<int> labels;
	// ��ȡ����. ����ļ����Ϸ��ͻ����
	// ������ļ����Ѿ�����.
	try {
		read_csv(fn_csv, images, labels, 10);
	}
	catch (cv::Exception& e) {
		cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
		// �ļ������⣬����ɶҲ�������ˣ��˳���
		exit(1);
	}
	// ���û�ж�ȡ���㹻ͼƬ������Ҳ���˳�.
	if (images.size() <= 1) {
		string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
		CV_Error(CV_StsError, error_message);
	}
	
	Eigen_Face(images, labels, "Eigenface",10);
	FisherFace(images, labels, "Eigenface", 10);
	return 0;
}