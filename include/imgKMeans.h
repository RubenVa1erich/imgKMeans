// imgKMeans.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <iostream>
#include <memory>

#include "imgCreator.h"
#include "windowsManager.h"

class ImageColoring
{
private:
	cv::Mat labels, centers, image, blurredImage, dataImage, segmentedImage, contourImage;
	
	int k;						// for kmeans
	int gaussianBlurSize;		// for blur

public:
	ImageColoring(const std::string file);

	int getKPos() const;
	int getBlurPos();

	cv::Mat getImage() const;
	cv::Mat getBlurredImage() const;
	cv::Mat getSegmentedImage() const;
	cv::Mat getContourImage() const;


	static void onTrackbarStatic(int value, void* userdata);

	void updateImages(const int trackbarKPos, const int trackbarBlurPos);
};