#include "windowsManager.h"



void WindowsManager::createWindows(ImageColoring* imgColoring, int& k, int& gaussianBlurSize)
{
	cv::namedWindow("Original Image", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Blurred Image", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Segmented Image", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Contour Image", cv::WINDOW_AUTOSIZE);

	cv::createTrackbar("GaussianBlur", "Segmented Image", &gaussianBlurSize, 299);
	cv::setTrackbarMin("GaussianBlur", "Segmented Image", 1);

	cv::createTrackbar("K", "Segmented Image", &k, 20, &ImageColoring::onTrackbarStatic, imgColoring);
	cv::setTrackbarMin("K", "Segmented Image", 2);
}

void WindowsManager::showWindows(const cv::Mat& image, const cv::Mat& blurredImage, const cv::Mat& segmentedImage, const cv::Mat& contourImage)
{
	cv::imshow("Original Image", image);
	cv::imshow("Blurred Image", blurredImage);
	cv::imshow("Segmented Image", segmentedImage);
	cv::imshow("Contour Image", contourImage);
}
