#pragma once

#include "opencv2/opencv.hpp"

class ImageCreator
{
public:
	static void createBlurredImg(const cv::Mat& image, cv::Mat& blurredImage, const int& blur);
	static void createDataImg(const cv::Mat& blurredImage, cv::Mat& dataImage, cv::Mat& labels, cv::Mat& centers, const int& k);
	static void createSegmentedImg(cv::Mat& segmentedImage, const cv::Mat& image);
	static void createContourImg(cv::Mat& contourImage, const cv::Mat& image);
};