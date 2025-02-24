#include "imgKMeans.h"

int main()
{
	std::cout << cv::getBuildInformation() << std::endl;

	auto imgColoring = std::make_unique<ImageColoring>("testImage.jpg");

	cv::waitKey(0);

	return 0;
}