// imgKMeans.cpp: определяет точку входа для приложения.
//

#include "imgKMeans.h"

cv::Mat data, labels, centers, image, segmentedImage, contourImage;
int k = 5;
int attemps = 5;
cv::TermCriteria criteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 10, 1.0);


void onTrackbar(int pos, void* ptr)
{
	contourImage = image.clone();
	//contourImage.copySize(image);
	//contourImage.convertTo(contourImage, image.type());

	cv::kmeans(data, pos, labels, criteria, attemps, cv::KMEANS_PP_CENTERS, centers);
	for(int i = 0; i < image.rows; i++) {
		for(int j = 0; j < image.cols; j++) {
			int clusterIdx = labels.at<int>(i * image.cols + j, 0);
			cv::Vec3f color = centers.at<cv::Vec3f>(clusterIdx, 0);
			segmentedImage.at<cv::Vec3b>(i, j) = cv::Vec3b(color[0], color[1], color[2]);
		}
	}

	for(int k = 0; k < pos; k++) {
		cv::Mat mask = cv::Mat::zeros(segmentedImage.size(), CV_8UC1);
		for(int i = 0; i < segmentedImage.rows; i++) {
			for(int j = 0; j < segmentedImage.cols; j++) {
				if(labels.at<int>(i * segmentedImage.cols + j, 0) == k) {
					mask.at<uchar>(i, j) = 255;
				}
			}
		}

		std::vector<std::vector<cv::Point>> contours;
		cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
		cv::drawContours(contourImage, contours, -1, cv::Scalar(0, 0, 0), 1);
	}

	cv::imshow("Original Image", image);
	cv::imshow("Segmented Image", segmentedImage);
	cv::imshow("Contour Image", contourImage);
}

int main()
{
	image = cv::imread("testImage.jpg");
	if(image.empty()) {
		std::cerr << "image is empty! return error" << std::endl;
		return - 1;
	}

	data = image.reshape(1, image.total());
	data.convertTo(data, CV_32F);

	cv::kmeans(data, k, labels, criteria, attemps, cv::KMEANS_PP_CENTERS, centers);
	

	segmentedImage = image.clone();

	cv::namedWindow("Original Image", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Segmented Image", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Contour Image", cv::WINDOW_AUTOSIZE);

	cv::createTrackbar("K", "Segmented Image", &k, 20, &onTrackbar, nullptr);
	cv::setTrackbarMin("K", "Segmented Image", 2);

	cv::waitKey(0);

	return 0;
}
