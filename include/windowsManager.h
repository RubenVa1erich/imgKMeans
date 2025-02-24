#pragma once

#include "opencv2/highgui.hpp"
#include "imgKMeans.h"

class WindowsManager
{
public:
	static void createWindows(ImageColoring* imgColoring, int& k, int& gaussianBlurSize);
	static void showWindows(const cv::Mat& image, const cv::Mat& blurredImage, const cv::Mat& segmentedImage, const cv::Mat& contourImage);
};