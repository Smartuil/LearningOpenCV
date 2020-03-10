#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
CascadeClassifier faceDetector;
CascadeClassifier faceSmileDetector;
String haar_data_file = "D:/opencv/opencv/build/etc/haarcascades/haarcascade_frontalface_alt_tree.xml";
String haar_smile_data_file = "D:/opencv/opencv/build/etc/haarcascades/haarcascade_smile.xml";
int main(int artc, char** argv) {
	Mat frame, gray;
	vector<Rect> faces;
	vector<Rect> faces2;
	VideoCapture capture(0);
	faceDetector.load(haar_data_file);
	faceSmileDetector.load(haar_smile_data_file);
	namedWindow("frame", WINDOW_AUTOSIZE);
	while (true) {
		capture.read(frame);
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		equalizeHist(gray, gray);
		faceDetector.detectMultiScale(gray, faces, 1.2, 1, 0, Size(30, 30), Size(400, 400));
		for (size_t t = 0; t < faces.size(); t++) {
			rectangle(frame, faces[t], Scalar(0, 0, 255), 2, 8, 0);
		}
		
		faceSmileDetector.detectMultiScale(gray, faces2, 1.7, 3, 0, Size(15, 15), Size(400, 400));
		for (size_t t = 0; t < faces2.size(); t++) {
			rectangle(frame, faces2[t], Scalar(0, 255, 255), 2, 8, 0);
		}

		char c = waitKey(10);
		if (c == 27) {
			break;
		}
		imshow("frame", frame);
	}

	waitKey(0);
	return 0;
}