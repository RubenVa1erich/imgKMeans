// imgKMeans.cpp: определяет точку входа для приложения.
//
#pragma once

#include <chrono>

#include "imgKMeans.h"

ImageColoring::ImageColoring(const std::string file)
{
	k = 5;
	gaussianBlurSize = 15;

	image = cv::imread(file);
	if(image.empty()) {
		std::cerr << "image is empty! return error" << std::endl;
		return;
	}

	ImageCreator::createBlurredImg(image, blurredImage, gaussianBlurSize);
	ImageCreator::createDataImg(blurredImage, dataImage, labels, centers, k);
	ImageCreator::createSegmentedImg(segmentedImage, image);
	ImageCreator::createContourImg(contourImage, image);

	WindowsManager::createWindows(this, k, gaussianBlurSize);
	WindowsManager::showWindows(image, blurredImage, segmentedImage, contourImage);
};


void ImageColoring::onTrackbarStatic(int value, void* ptrObjImageColoring)
{
	auto start = std::chrono::high_resolution_clock::now();

	ImageColoring* self = static_cast<ImageColoring*>(ptrObjImageColoring);
	self->updateImages(self->getKPos(), self->getBlurPos()); // Обновление изображений
	WindowsManager::showWindows(self->getImage(), self->getBlurredImage(), self->getSegmentedImage(), self->getContourImage()); // Отображение изображений

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "func time: " << duration.count() << " sec" << std::endl;
}

int ImageColoring::getKPos() const
{
	return k;
}

int ImageColoring::getBlurPos()
{
	if( !(gaussianBlurSize % 2) ) {
		++gaussianBlurSize;
		cv::setTrackbarPos("GaussianBlur", "Segmented Image", gaussianBlurSize);
	}
	return gaussianBlurSize;
}

cv::Mat ImageColoring::getImage() const
{
	return image;
}

cv::Mat ImageColoring::getBlurredImage() const
{
	return blurredImage;
}

cv::Mat ImageColoring::getSegmentedImage() const
{
	return segmentedImage;
}

cv::Mat ImageColoring::getContourImage() const
{
	return contourImage;
}


void ImageColoring::updateImages(const int trackbarKPos, const int trackbarBlurPos)
{
	ImageCreator::createBlurredImg(image, blurredImage, trackbarBlurPos);
	ImageCreator::createDataImg(blurredImage, dataImage, labels, centers, trackbarKPos);
	ImageCreator::createContourImg(contourImage, image);

	for(int i = 0; i < image.rows; i++) {
		for(int j = 0; j < image.cols; j++) {
			int clusterIdx = labels.at<int>(i * image.cols + j, 0);
			cv::Vec3f color = centers.at<cv::Vec3f>(clusterIdx, 0);
			segmentedImage.at<cv::Vec3b>(i, j) = cv::Vec3b(color[0], color[1], color[2]);
		}
	}

	for(int k = 0; k < trackbarKPos; k++) {
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
}

