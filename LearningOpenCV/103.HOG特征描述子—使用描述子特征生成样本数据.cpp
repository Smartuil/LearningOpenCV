#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace cv::ml;
using namespace std;

string positive_dir = "D:/images/train_data/elec_watch/positive/";
string negative_dir = "D:/images/train_data/elec_watch/negative/";
void get_hog_descripor(Mat &image, vector<float> &desc);
void generate_dataset(Mat &trainData, Mat &labels);

int main(int argc, char** argv) {
	Mat trainData = Mat::zeros(Size(3780, 26), CV_32FC1);
	Mat labels = Mat::zeros(Size(1, 26), CV_32SC1);
	generate_dataset(trainData, labels);
	waitKey(0);
	return 0;
}

void get_hog_descripor(Mat &image, vector<float> &desc) {
	HOGDescriptor hog;
	int h = image.rows;
	int w = image.cols;
	float rate = 64.0 / w;
	Mat img, gray;
	resize(image, img, Size(64, int(rate*h)));
	cvtColor(img, gray, COLOR_BGR2GRAY);
	Mat result = Mat::zeros(Size(64, 128), CV_8UC1);
	result = Scalar(127);
	Rect roi;
	roi.x = 0;
	roi.width = 64;
	roi.y = (128 - gray.rows) / 2;
	roi.height = gray.rows;
	gray.copyTo(result(roi));
	hog.compute(result, desc, Size(8, 8), Size(0, 0));
}

void generate_dataset(Mat &trainData, Mat &labels) {
	vector<string> images;
	glob(positive_dir, images);
	int pos_num = images.size();
	for (int i = 0; i < images.size(); i++) {
		Mat image = imread(images[i].c_str());
		vector<float> fv;
		imshow("image", image);
		waitKey(0);
		get_hog_descripor(image, fv);
		printf("image path : %s, feature data length: %d \n", images[i].c_str(), fv.size());
		for (int j = 0; j < fv.size(); j++) {
			trainData.at<float>(i, j) = fv[j];
		}
		labels.at<int>(i, 0) = 1;
	}

	images.clear();
	glob(negative_dir, images);
	for (int i = 0; i < images.size(); i++) {
		Mat image = imread(images[i].c_str());
		vector<float> fv;
		imshow("image", image);
		waitKey(0);
		get_hog_descripor(image, fv);
		printf("image path : %s, feature data length: %d \n", images[i].c_str(), fv.size());
		for (int j = 0; j < fv.size(); j++) {
			trainData.at<float>(i + pos_num, j) = fv[j];
		}
		labels.at<int>(i + pos_num, 0) = -1;
	}
}