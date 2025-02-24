#include "imgCreator.h"

void ImageCreator::createBlurredImg(const cv::Mat& image, cv::Mat& blurredImage, const int& blur)
{
	cv::GaussianBlur(image, blurredImage, cv::Size(blur, blur), 0);
}

void ImageCreator::createDataImg(const cv::Mat& blurredImage, cv::Mat& dataImage, cv::Mat& labels, cv::Mat& centers, const int& k)
{
	cv::TermCriteria criteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 10, 1.0);
	int attemps = 10;

	dataImage = blurredImage.reshape(1, blurredImage.total());
	dataImage.convertTo(dataImage, CV_32F);
	cv::kmeans(dataImage, k, labels, criteria, attemps, cv::KMEANS_PP_CENTERS, centers);
}

void ImageCreator::createSegmentedImg(cv::Mat& segmentedImage, const cv::Mat& image)
{
	segmentedImage = image.clone();
}

void ImageCreator::createContourImg(cv::Mat& contourImage, const cv::Mat& image)
{
	contourImage = cv::Mat::ones(image.size(), image.type());
	contourImage.setTo(cv::Scalar(255, 255, 255));
}
